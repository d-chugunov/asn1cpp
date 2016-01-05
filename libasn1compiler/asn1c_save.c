#include "asn1c_internal.h"
#include "asn1c_compat.h"
#include "asn1c_fdeps.h"
#include "asn1c_lang.h"
#include "asn1c_misc.h"
#include "asn1c_save.h"
#include "asn1c_out.h"
#include "../libasn1fix/asn1fix_export.h"

#ifndef HAVE_SYMLINK
#define symlink(a,b) (errno=ENOSYS, -1)
#endif

#define	HINCLUDE(s)						\
	((arg->flags & A1C_INCLUDES_QUOTED)			\
		? fprintf(fp_h, "#include \"%s\"\n", s)		\
		: fprintf(fp_h, "#include <%s>\n", s))		\

static int asn1c_dump_streams(arg_t *arg, asn1c_fdeps_t *, int, char **);
static int asn1c_print_streams(arg_t *arg);
static int asn1c_save_streams(arg_t *arg, asn1c_fdeps_t *, int, char **);
static int asn1c_copy_over(arg_t *arg, char *path);
static int identical_files(const char *fname1, const char *fname2);
static int need_to_generate_pdu_collection(arg_t *arg);
static int generate_pdu_collection_file(arg_t *arg);
static int generate_preamble(arg_t *, FILE *, int optc, char **argv);
static int include_type_to_pdu_collection(arg_t *arg);
static void pdu_collection_print_unused_types(arg_t *arg);
static const char *generate_pdu_C_definition(void);

static const char* single_unit_filename = "asn";
static FILE *single_unit_fp_c, *single_unit_fp_h;

typedef struct TopSortGraphNode_s {
  asn1p_module_t* module;
  asn1p_expr_t* expr;
  size_t* edges;
  size_t edgesCount;
  size_t edgesAlloced;
} TopSortGraphNode;

static size_t
top_sort_find_vertex(arg_t *arg, TopSortGraphNode** vertices, size_t* verticesCount,
        size_t* verticesAlloced, asn1p_module_t* module, asn1p_expr_t* expr)
{
  if (*verticesCount) {
    TopSortGraphNode* verticesArr = *vertices;
    size_t i;
    for (i = 0; i < *verticesCount; ++i) {
      if (0 == strcmp(verticesArr[i].module->ModuleName, module->ModuleName) &&
              0 == strcmp(verticesArr[i].expr->Identifier, expr->Identifier))
      {
        return i;
      }
    }
  }
  //vertex was not found => create new
  
  if (*verticesCount == *verticesAlloced) {
    //should do realloc
    *verticesAlloced = *verticesAlloced ? (*verticesAlloced) << 1 : 1;
    *vertices = realloc(*vertices, *verticesAlloced * sizeof(**vertices));
    if (!*vertices) {
      fprintf(stderr, "Unable to realloc memory for top sort graph.\n");
      exit(1);
    }
  }
  TopSortGraphNode* newNode = (*vertices) + *verticesCount;
  memset(newNode, 0, sizeof(*newNode));
  newNode->module = module;
  newNode->expr = expr;
//  fprintf(stderr, "Adding vertex %s:%s with index %zu\n", module->ModuleName, expr->Identifier, *verticesCount);
  ++(*verticesCount);
  return (*verticesCount) - 1;
}

static void
top_sort_add_edge(TopSortGraphNode* node, size_t edgeTo, TopSortGraphNode* nodes) {
  size_t i;
  for (i = 0; i < node->edgesCount; ++i) {
    if (node->edges[i] == edgeTo)
      return;
  }
  if (node->edgesCount == node->edgesAlloced) {
    node->edgesAlloced = node->edgesAlloced ? (node->edgesAlloced) << 1 : 1;
    node->edges = realloc(node->edges, node->edgesAlloced * sizeof(*node->edges));
    if (!node->edges) {
      fprintf(stderr, "Unable to realloc memory for edges of top sort graph.\n");
      exit(1);
    }
  }
  node->edges[node->edgesCount] = edgeTo;
//  fprintf(stderr, "Adding vertex between vertex %s:%s and vertex %s:%s\n", node->module->ModuleName, node->expr->Identifier, nodes[edgeTo].module->ModuleName, nodes[edgeTo].expr->Identifier);
  ++node->edgesCount;
}

static int
is_module_member(asn1p_t* asn, asn1p_expr_t* expr) {
  asn1p_expr_t* moduleExpr;
  asn1p_module_t *mod;
  TQ_FOR(mod, &(asn->modules), mod_next) {
		TQ_FOR(moduleExpr, &(mod->members), next) {
      if (moduleExpr == expr) {
        return 1;
      }
		}
	}
  return 0;
}

static void
top_sort_dfs(TopSortGraphNode* nodes, size_t nodeIndex, uint8_t* used,
        size_t* resultList, size_t* currentIndexInList)
{
  used[nodeIndex] = 1;
  size_t i;
  TopSortGraphNode* node = nodes + nodeIndex;
  for (i = 0; i < node->edgesCount; ++i) {
    size_t to = node->edges[i];
    if (!used[to]) {
      top_sort_dfs(nodes, to, used, resultList, currentIndexInList);
    }
  }
  resultList[*currentIndexInList] = nodeIndex;
  ++(*currentIndexInList);
}

static void
top_sort(TopSortGraphNode* nodes, size_t nodesCount, size_t* resultList) {
  size_t currentIndexInList = 0;
  uint8_t* used = calloc(nodesCount, sizeof(uint8_t));
  int i;
  for (i = 0; i < nodesCount; ++i) {
    if (!used[i]) {
      top_sort_dfs(nodes, i, used, resultList, &currentIndexInList);
    }
  }
  free(used);
  for (i = 0; i < nodesCount / 2; ++i) {
    size_t t = resultList[i];
    resultList[i] = resultList[nodesCount - 1 - i];
    resultList[nodesCount - 1 - i] = t;
  }
}

#define IS_SINGLE_UNIT(arg) (arg->flags & A1C_SINGLE_UNIT)

int
asn1c_save_compiled_output(arg_t *arg, const char *datadir,
		int argc, int optc, char **argv) {
	asn1c_fdeps_t *deps = 0;
	asn1c_fdeps_t *dlist;
	asn1p_module_t *mod;
	FILE *mkf;	/* Makefile.am.sample */
	int i;

	deps = asn1c_read_file_dependencies(arg, datadir);
	if(!deps && datadir) {
		WARNING("Cannot read file-dependencies information "
			"from %s\n", datadir);
	}
  
  if (IS_SINGLE_UNIT(arg)) {
    TopSortGraphNode* topSortGraphNodes = 0;
    size_t topSortGraphNodesCount = 0, topSortGraphNodesAlloced = 0;

    TQ_FOR(mod, &(arg->asn->modules), mod_next) {
      TQ_FOR(arg->expr, &(mod->members), next) {
        if(asn1_lang_map[arg->expr->meta_type][arg->expr->expr_type].type_cb) {
          //find index of current vertex
          size_t currentVertex = top_sort_find_vertex(arg, &topSortGraphNodes, &topSortGraphNodesCount,
                  &topSortGraphNodesAlloced, mod, arg->expr);
          //create edge for reference
          if (arg->expr->meta_type == AMT_TYPEREF) {
            asn1p_expr_t* ref_expr = asn1f_lookup_symbol_ex(arg->asn, arg->expr, arg->expr->reference);
            if (!ref_expr) {
              fprintf(stderr, "Cannot find terminal type by reference %s:%s.\n", arg->expr->module->ModuleName, arg->expr->Identifier);
            } else {
              size_t refVertex = top_sort_find_vertex(arg, &topSortGraphNodes, &topSortGraphNodesCount,
                      &topSortGraphNodesAlloced, ref_expr->module, ref_expr);
              top_sort_add_edge(&topSortGraphNodes[refVertex], currentVertex, topSortGraphNodes);
            }
          }
          //create edges for all members
          asn1p_expr_t *memb;
          TQ_FOR(memb, &(arg->expr->members), next) {
            if((!(memb->expr_type & ASN_CONSTR_MASK) && memb->expr_type > ASN_CONSTR_MASK)
              || memb->meta_type == AMT_TYPEREF)
            {
              asn1p_expr_t* expr = memb;
              //find index of member vertex
              if (expr->meta_type == AMT_TYPEREF) {
                asn1p_expr_t* ref_expr = asn1f_lookup_symbol_ex(arg->asn, expr, expr->reference);
                if (!ref_expr) {
                  fprintf(stderr, "Cannot find terminal type by reference %s:%s.\n", expr->module->ModuleName, expr->Identifier);
                } else {
                  expr = ref_expr;
                }
              }
              if (!is_module_member(arg->asn, expr))
                continue;
              size_t memberVertex = top_sort_find_vertex(arg, &topSortGraphNodes, &topSortGraphNodesCount,
                  &topSortGraphNodesAlloced, expr->module, expr);
              //make edge between member vertex and current vertex
              top_sort_add_edge(&topSortGraphNodes[memberVertex], currentVertex, topSortGraphNodes);
            }
          }
        }
      }
    }

    size_t* topSortResult = calloc(topSortGraphNodesCount, sizeof(size_t));

    top_sort(topSortGraphNodes, topSortGraphNodesCount, topSortResult);

  //  for (i = 0; i < topSortGraphNodesCount; ++i) {
  //    printf("%zu ", topSortResult[i]);
  //  }
  //  printf("\n");
  //  
  //  exit(0);
    
    char *single_unit_tmpname_c, *single_unit_tmpname_h;
    char *name_buf;
    const char *c_retained = "";
    const char *h_retained = "";
    
    FILE *fp_h;
    
    single_unit_fp_c = asn1c_open_file(single_unit_filename, ".cpp", &single_unit_tmpname_c);
    fp_h = single_unit_fp_h = asn1c_open_file(single_unit_filename, ".hpp", &single_unit_tmpname_h);
    
    if(single_unit_fp_c == NULL || single_unit_fp_h == NULL) {
      if(single_unit_fp_c) { unlink(single_unit_tmpname_c); free(single_unit_tmpname_c); fclose(single_unit_fp_c); }
      if(single_unit_fp_h) { unlink(single_unit_tmpname_h); free(single_unit_tmpname_h); fclose(single_unit_fp_h); }
      return -1;
    }

    arg->expr = 0;
    generate_preamble(arg, single_unit_fp_c, optc, argv);
    generate_preamble(arg, single_unit_fp_h, optc, argv);
    
#define IDENTIFIER_FOR_IFDEF()                                                \
    do {                                                                      \
      fprintf(fp_h, "_%s_HPP_", single_unit_filename);                        \
    } while (0)
    
    fprintf(single_unit_fp_h, "#ifndef\t");
    IDENTIFIER_FOR_IFDEF();
    fprintf(single_unit_fp_h, "\n");
    fprintf(single_unit_fp_h, "#define\t");
    IDENTIFIER_FOR_IFDEF();
    fprintf(single_unit_fp_h, "\n\n");
    
    HINCLUDE("AsnAbstractType.hpp");
    fprintf(single_unit_fp_c, "#include \"%s.hpp\"\n\n", single_unit_filename);
    
    //including external dependencies
    {
      char** addedDepencies = NULL;
      size_t addedDepenciesCount = 0, addedDepenciesAlloced = 0;
      int wasIncludingExternalDependenciesMsgPrinted = 0;
      for (i = 0; i < topSortGraphNodesCount; ++i) {
        asn1p_expr_t *expr = arg->expr = topSortGraphNodes[topSortResult[i]].expr;
        if(asn1_lang_map[arg->expr->meta_type][arg->expr->expr_type].type_cb) {
          compiler_streams_t *cs = expr->data;
          if (!cs)
            continue;
          static const int idx = OT_INCLUDES;
          out_chunk_t *ot;
          TQ_FOR(ot, &(cs->destination[idx].chunks), next) {
            int isNewDependency = 1;
            size_t i;
            for (i = 0; i < addedDepenciesCount; ++i) {
              if (0 == strncmp(addedDepencies[i], ot->buf, ot->len)) {
                isNewDependency = 0;
                break;
              }
            }
            if (isNewDependency) {
              if (!wasIncludingExternalDependenciesMsgPrinted) {
                fprintf(single_unit_fp_h, "\n/* Including external dependencies */\n");
                wasIncludingExternalDependenciesMsgPrinted = 1;
              }
              fwrite(ot->buf, ot->len, 1, single_unit_fp_h);
              if (addedDepenciesCount == addedDepenciesAlloced) {
                addedDepenciesAlloced = addedDepenciesAlloced ? addedDepenciesAlloced << 1 : 1;
                addedDepencies = realloc(addedDepencies, addedDepenciesAlloced * sizeof(addedDepencies[0]));
              }
              addedDepencies[addedDepenciesCount] = strndup(ot->buf, ot->len);
              ++addedDepenciesCount;
            }
          }
        }
      }
      size_t i;
      for (i = 0; i < addedDepenciesCount; ++i) {
        free(addedDepencies[i]);
      }
      free(addedDepencies);
    }
    
    //generate code for types according with respect of top sort results
    for (i = 0; i < topSortGraphNodesCount; ++i) {
      arg->expr = topSortGraphNodes[topSortResult[i]].expr;
      if(asn1_lang_map[arg->expr->meta_type][arg->expr->expr_type].type_cb) {
        if(asn1c_dump_streams(arg, deps, optc, argv)) {
          unlink(single_unit_tmpname_c);
          unlink(single_unit_tmpname_h);
          free(single_unit_tmpname_c);
          free(single_unit_tmpname_h);
          fclose(single_unit_fp_c);
          fclose(single_unit_fp_h);
          return -1;
        }
      }
    }
    
    fprintf(single_unit_fp_h, "\n#endif\t/* ");
    IDENTIFIER_FOR_IFDEF();
    fprintf(single_unit_fp_h, " */\n");
    
#undef IDENTIFIER_FOR_IFDEF
    
    fclose(single_unit_fp_c);
    fclose(single_unit_fp_h);
    
    name_buf = alloca(strlen(single_unit_filename) + 5);
    
    sprintf(name_buf, "%s.cpp", single_unit_filename);
    if(identical_files(name_buf, single_unit_tmpname_c)) {
      c_retained = " (contents unchanged)";
      unlink(single_unit_tmpname_c);
    } else {
      if(rename(single_unit_tmpname_c, name_buf)) {
        unlink(single_unit_tmpname_c);
        perror(single_unit_tmpname_c);
        free(single_unit_tmpname_c);
        free(single_unit_tmpname_h);
        return -1;
      }
    }

    sprintf(name_buf, "%s.hpp", single_unit_filename);
    if(identical_files(name_buf, single_unit_tmpname_h)) {
      h_retained = " (contents unchanged)";
      unlink(single_unit_tmpname_h);
    } else {
      if(rename(single_unit_tmpname_h, name_buf)) {
        unlink(single_unit_tmpname_h);
        perror(single_unit_tmpname_h);
        free(single_unit_tmpname_c);
        free(single_unit_tmpname_h);
        return -1;
      }
    }
    
    free(single_unit_tmpname_c);
    free(single_unit_tmpname_h);
    
    fprintf(stderr, "Compiled %s.cpp%s\n", single_unit_filename, c_retained);
    fprintf(stderr, "Compiled %s.hpp%s\n", single_unit_filename, h_retained);
    
  } else {
    TQ_FOR(mod, &(arg->asn->modules), mod_next) {
      TQ_FOR(arg->expr, &(mod->members), next) {
        if(asn1_lang_map[arg->expr->meta_type]
          [arg->expr->expr_type].type_cb) {
          if(asn1c_dump_streams(arg, deps, optc, argv))
            return -1;
        }
      }
    }
  }

	/*
	 * Dump out the Makefile template and the rest of the support code.
	 */
	if((arg->flags & A1C_PRINT_COMPILED)
	|| (arg->flags & A1C_OMIT_SUPPORT_CODE)) {
		return 0;	/* Finished */
	}

	mkf = asn1c_open_file("Makefile.am", ".sample", 0);
	if(mkf == NULL) {
		perror("Makefile.am.sample");
		return -1;
	}

	fprintf(mkf, "ASN_MODULE_SOURCES=");
  if (IS_SINGLE_UNIT(arg)) {
    fprintf(mkf, "%s.cpp", single_unit_filename);
  } else {
    TQ_FOR(mod, &(arg->asn->modules), mod_next) {
      TQ_FOR(arg->expr, &(mod->members), next) {
        if(asn1_lang_map[arg->expr->meta_type]
          [arg->expr->expr_type].type_cb) {
          fprintf(mkf, "\t\\\n\t%s.cpp",
          arg->expr->Identifier);
        }
      }
    }
  }
	fprintf(mkf, "\n\nASN_MODULE_HEADERS=");
  if (IS_SINGLE_UNIT(arg)) {
    fprintf(mkf, "%s.hpp", single_unit_filename);
  } else {
    TQ_FOR(mod, &(arg->asn->modules), mod_next) {
      TQ_FOR(arg->expr, &(mod->members), next) {
        if(asn1_lang_map[arg->expr->meta_type]
          [arg->expr->expr_type].type_cb) {
          fprintf(mkf, "\t\\\n\t%s.hpp",
          arg->expr->Identifier);
        }
      }
    }
  }
	fprintf(mkf, "\n\n");

	/*
	 * Move necessary skeleton files and add them to Makefile.am.sample.
	 */
	dlist = asn1c_deps_makelist(deps);
	if(dlist) {
		char buf[8129];
		char *dir_end;
		size_t dlen = strlen(datadir);

		assert(dlen < (sizeof(buf) / 2 - 2));
		memcpy(buf, datadir, dlen);
		dir_end = buf + dlen;
		*dir_end++ = '/';

		for(i = 0; i < dlist->el_count; i++) {
			char *what_class;	/* MODULE or CONVERTER */
			char *what_kind;	/* HEADERS or SOURCES */
			char *fname = dlist->elements[i]->filename;
			char *dotH;

			assert(strlen(fname) < (sizeof(buf) / 2));
			strcpy(dir_end, fname);

			if(asn1c_copy_over(arg, buf) == -1) {
				fprintf(mkf, ">>>ABORTED<<<");
				fclose(mkf);
				return -1;
			}

			/* MODULE data versus CONVERTER data */
			switch(dlist->elements[i]->usage) {
			case FDEP_CONVERTER: what_class = "CONVERTER"; break;
			default: what_class= "MODULE"; break;
			}

			/* HEADERS versus SOURCES */
			dotH = strrchr(fname, 'h');
			if(dotH && fname<dotH && dotH[-1] == '.' && dotH[1] && dotH[2] && !dotH[3])
				what_kind = "HEADERS";
			else
				what_kind = "SOURCES";
			fprintf(mkf, "ASN_%s_%s+=%s\n",
				what_class, what_kind, fname);
		}
	}

	if(need_to_generate_pdu_collection(arg)) {
		fprintf(mkf, "ASN_CONVERTER_SOURCES+=pdu_collection.cpp\n");
		if(generate_pdu_collection_file(arg))
			return -1;
	}

	fprintf(mkf, "\n\n"
		"lib_LTLIBRARIES=libsomething.la\n"
		"libsomething_la_SOURCES="
			"$(ASN_MODULE_SOURCES) $(ASN_MODULE_HEADERS)\n"
		"\n"
		"# This file may be used as an input for make(3)\n"
		"# Remove the lines below to convert it into a pure .am file\n"
		"TARGET = progname\n"
    "CXXFLAGS +=%s%s -std=c++11 -I.\n"
		"OBJS=${ASN_MODULE_SOURCES:.cpp=.o}"
      " ${ASN_CONVERTER_SOURCES:.cpp=.o}\n"
		"\nall: $(TARGET)\n"
		"\n$(TARGET): ${OBJS}"
		"\n\t$(CXX) $(CXXFLAGS) -o $(TARGET) ${OBJS} $(LDFLAGS) $(LIBS)\n"
		"\n.SUFFIXES:"
		"\n.SUFFIXES: .cpp .o\n"
    "\n.cpp.o:"
		"\n\t$(CXX) $(CXXFLAGS) -o $@ -c $<\n"
		"\nclean:"
		"\n\trm -f $(TARGET)"
		"\n\trm -f $(OBJS)\n"
		"\nregen: regenerate-from-asn1-source\n"
		"\nregenerate-from-asn1-source:\n\t"
    , (arg->flags & A1C_PDU_TYPE)
			? generate_pdu_C_definition() : ""
		, need_to_generate_pdu_collection(arg)
			? " -DASN_PDU_COLLECTION" : ""
	);

	for(i = 0; i < argc; i++)
		fprintf(mkf, "%s%s", i ? " " : "", argv[i]);
	fprintf(mkf, "\n\n");

	fclose(mkf);
	fprintf(stderr, "Generated Makefile.am.sample\n");

	return 0;
}

/*
 * Dump the streams.
 */
static int
asn1c_dump_streams(arg_t *arg, asn1c_fdeps_t *deps, int optc, char **argv)  {
	if(arg->flags & A1C_PRINT_COMPILED) {
		return asn1c_print_streams(arg);
	} else {
		return asn1c_save_streams(arg, deps, optc, argv);
	}
}

static int
asn1c_print_streams(arg_t *arg)  {
	compiler_streams_t *cs = arg->expr->data;
	asn1p_expr_t *expr = arg->expr;
	int i;

	for(i = 1; i < OT_MAX; i++) {
		out_chunk_t *ot;
		if(TQ_FIRST(&cs->destination[i].chunks) == NULL)
			continue;

		printf("\n/*** <<< %s [%s] >>> ***/\n\n",
			_compiler_stream2str[i],
			expr->Identifier);

		TQ_FOR(ot, &(cs->destination[i].chunks), next) {
			fwrite(ot->buf, ot->len, 1, stdout);
		}
	}

	return 0;
}

static int
asn1c_save_streams(arg_t *arg, asn1c_fdeps_t *deps, int optc, char **argv) {
	asn1p_expr_t *expr = arg->expr;
	compiler_streams_t *cs = expr->data;
	out_chunk_t *ot;
	FILE *fp_c, *fp_h;
	char *tmpname_c = 0, *tmpname_h = 0;
	char *name_buf;
	const char *c_retained = "";
	const char *h_retained = "";

	if(cs == NULL) {
		fprintf(stderr, "Cannot compile %s at line %d\n",
			expr->Identifier, expr->_lineno);
		return -1;
	}
  if (!IS_SINGLE_UNIT(arg)) {
    fp_c = asn1c_open_file(expr->Identifier, ".cpp", &tmpname_c);
    fp_h = asn1c_open_file(expr->Identifier, ".hpp", &tmpname_h);
    
    if(fp_c == NULL || fp_h == NULL) {
      if(fp_c) { unlink(tmpname_c); free(tmpname_c); fclose(fp_c); }
      if(fp_h) { unlink(tmpname_h); free(tmpname_h); fclose(fp_h); }
      return -1;
    }
  } else {
    fp_c = single_unit_fp_c;
    fp_h = single_unit_fp_h;
  }
  
#define IDENTIFIER_FOR_IFDEF(expr)                                            \
  if (!(arg->flags & A1C_SHORT_IFDEF))                                        \
    fprintf(fp_h, "_%s", asn1c_make_namespace_name(arg, expr, 0));            \
  fprintf(fp_h, "_%s_HPP_", asn1c_make_identifier(0, expr, (char*)NULL));
          
  if (!IS_SINGLE_UNIT(arg)) {
    generate_preamble(arg, fp_c, optc, argv);
    generate_preamble(arg, fp_h, optc, argv);
    fprintf(fp_h, "#ifndef\t");
    IDENTIFIER_FOR_IFDEF(expr);
    fprintf(fp_h, "\n");
    fprintf(fp_h, "#define\t");
    IDENTIFIER_FOR_IFDEF(expr);
    fprintf(fp_h, "\n\n");
  }

	//fprintf(fp_h, "\n");
	//HINCLUDE("asn_application.hpp");
  //HINCLUDE("AsnAbstractType.hpp");

#define	SAVE_STREAM(fp, idx, msg, actdep)	do {			\
	if(TQ_FIRST(&(cs->destination[idx].chunks)) && *msg)		\
		fprintf(fp, "\n/* %s */\n", msg);			\
	TQ_FOR(ot, &(cs->destination[idx].chunks), next) {		\
		if(actdep) asn1c_activate_dependency(deps, 0, ot->buf);	\
		fwrite(ot->buf, ot->len, 1, fp);			\
	}								\
} while(0)
  
  if (!IS_SINGLE_UNIT(arg)) {
    SAVE_STREAM(fp_h, OT_INCLUDES,	"Including external dependencies", 1);
  }

	//fprintf(fp_h, "\n#ifdef __cplusplus\nextern \"C\" {\n#endif\n");

  SAVE_STREAM(fp_h, OT_FWD_DECLS,	"Forward declarations", 0);
  fprintf(fp_h, "\n");
  
  if (!(arg->flags & A1C_NO_NAMESPACE)) {
    fprintf(fp_h, "namespace %s {\n", asn1c_make_namespace_name(arg, expr, 0));  
  }
	SAVE_STREAM(fp_h, OT_DEPS,	"Dependencies", 0);
	SAVE_STREAM(fp_h, OT_TYPE_DECLS, expr->Identifier, 0);
	SAVE_STREAM(fp_h, OT_FUNC_DECLS,"Implementation", 0);
	//fprintf(fp_h, "\n#ifdef __cplusplus\n}\n#endif\n");
  if (!(arg->flags & A1C_NO_NAMESPACE)) 
    fprintf(fp_h, "} //End of namespace %s\n", asn1c_make_namespace_name(arg, expr, 0));

	if(!(arg->flags & A1C_NO_INCLUDE_DEPS))
	SAVE_STREAM(fp_h, OT_POST_INCLUDE, "Referred external types", 1);

  if (!IS_SINGLE_UNIT(arg)) {
    fprintf(fp_h, "\n#endif\t/* ");
    IDENTIFIER_FOR_IFDEF(expr);
    fprintf(fp_h, " */\n");
  }
  
#undef IDENTIFIER_FOR_IFDEF

	//HINCLUDE("asn_internal.hpp");
  if (!IS_SINGLE_UNIT(arg)) {
    fprintf(fp_c, "#include \"%s.hpp\"\n\n", expr->Identifier);
  }
	if(arg->flags & A1C_NO_INCLUDE_DEPS)
		SAVE_STREAM(fp_c, OT_POST_INCLUDE, "", 1);
  if (!(arg->flags & A1C_NO_NAMESPACE)) {
    fprintf(fp_c, "namespace %s {\n", asn1c_make_namespace_name(arg, expr, 0));  
  }
	TQ_FOR(ot, &(cs->destination[OT_CTABLES].chunks), next)
		fwrite(ot->buf, ot->len, 1, fp_c);
	TQ_FOR(ot, &(cs->destination[OT_CODE].chunks), next)
		fwrite(ot->buf, ot->len, 1, fp_c);
	TQ_FOR(ot, &(cs->destination[OT_CTDEFS].chunks), next)
		fwrite(ot->buf, ot->len, 1, fp_c);
	TQ_FOR(ot, &(cs->destination[OT_STAT_DEFS].chunks), next)
		fwrite(ot->buf, ot->len, 1, fp_c);
  if (!(arg->flags & A1C_NO_NAMESPACE)) 
    fprintf(fp_c, "} //End of namespace %s\n", asn1c_make_namespace_name(arg, expr, 0));

	assert(OT_MAX == 11);	/* Protection from reckless changes */

  if (!IS_SINGLE_UNIT(arg)) {
    fclose(fp_c);
  	fclose(fp_h);
    
    name_buf = alloca(strlen(expr->Identifier) + 5);
    
    sprintf(name_buf, "%s.cpp", expr->Identifier);
    if(identical_files(name_buf, tmpname_c)) {
      c_retained = " (contents unchanged)";
      unlink(tmpname_c);
    } else {
      if(rename(tmpname_c, name_buf)) {
        unlink(tmpname_c);
        perror(tmpname_c);
        free(tmpname_c);
        free(tmpname_h);
        return -1;
      }
    }

    sprintf(name_buf, "%s.hpp", expr->Identifier);
    if(identical_files(name_buf, tmpname_h)) {
      h_retained = " (contents unchanged)";
      unlink(tmpname_h);
    } else {
      if(rename(tmpname_h, name_buf)) {
        unlink(tmpname_h);
        perror(tmpname_h);
        free(tmpname_c);
        free(tmpname_h);
        return -1;
      }
    }
    
    fprintf(stderr, "Compiled %s.cpp%s\n", expr->Identifier, c_retained);
    fprintf(stderr, "Compiled %s.hpp%s\n", expr->Identifier, h_retained);
    
    free(tmpname_c);
    free(tmpname_h);
  } else {
    fprintf(stderr, "Compiled %s\n", expr->Identifier);
  }

	return 0;
}

void asn1c_set_single_unit(const char* filename) {
  if ('=' == filename[0]) {
    single_unit_filename = filename + 1;
  }
}

#define ASN1C_VERSION "0.9.24"

static int
generate_preamble(arg_t *arg, FILE *fp, int optc, char **argv) {
	fprintf(fp,
	"/*\n"
	" * Generated by asn1cpp-" VERSION " which is based on asn1c-" ASN1C_VERSION " (http://lionet.info/asn1c)\n");
  if (arg->expr) {
    fprintf(fp, " * From ASN.1 module \"%s\"\n"
      " * \tfound in \"%s\"\n",
        arg->expr->module->ModuleName,
        arg->expr->module->source_file_name);
  } else {
    asn1p_module_t* module;
    fprintf(fp, " * From ASN.1 modules:\n");
    TQ_FOR(module, &(arg->asn->modules), mod_next) {
      if (module->_tags != MT_STANDARD_MODULE) {
        fprintf(fp, " * \t%s found in \"%s\"\n", module->ModuleName, module->source_file_name);
      }
    }
  }
	if(optc >= 1) {
		int i;
		fprintf(fp, " * \t`asn1cpp ");
		for(i = 1; i <= optc; i++)
			fprintf(fp, "%s%s", i>1?" ":"", argv[i]);
		fprintf(fp, "`\n");
	}
	fprintf(fp, " */\n\n");
	return 0;
}

static int
identical_files(const char *fname1, const char *fname2) {
	char buf[2][4096];
	FILE *fp1, *fp2;
	size_t olen, nlen;
	int retval = 1;	/* Files are identical */

#ifndef	_WIN32
	struct stat sb;

	if(lstat(fname1, &sb) || !S_ISREG(sb.st_mode)
	|| lstat(fname2, &sb) || !S_ISREG(sb.st_mode)) {
		return 0;	/* Files are not identical */
	}
#endif

	fp1 = fopen(fname1, "r");
	if(!fp1) { return 0; }
	fp2 = fopen(fname2, "r");
	if(!fp2) { fclose(fp1); return 0; }

	while((olen = fread(buf[0], 1, sizeof(buf[0]), fp1))) {
		nlen = fread(buf[1], 1, olen, fp2);
		if(nlen != olen || memcmp(buf[0], buf[1], nlen)) {
			retval = 0;
			break;
		}
	}
	nlen = fread(buf[1], 1, 1, fp2);
	if(nlen) retval = 0;

	fclose(fp1);
	fclose(fp2);
	return retval;
}

/*
 * Copy file for real.
 */
static int
real_copy(const char *src, const char *dst) {
	unsigned char buf[4096];
	char *tmpname;
	FILE *fpsrc, *fpdst;
	size_t len;
	int retval = 0;

	if(identical_files(src, dst))
		return retval;	/* Success, no need to copy for real. */

	fpsrc = fopen(src, "r");
	if(!fpsrc) { errno = EIO; return -1; }
	fpdst = asn1c_open_file(dst, "", &tmpname);
	if(!fpdst) { fclose(fpsrc); errno = EIO; return -1; }

	while(!feof(fpsrc)) {
		len = fread(buf, 1, sizeof(buf), fpsrc);
		if(fwrite(buf, 1, len, fpdst) != len) {
			perror(tmpname);
			errno = EIO;
			retval = -1;
			break;
		}
	}
	fclose(fpsrc);
	fclose(fpdst);

	/* Check if copied correctly, and rename into a permanent name */
	if(retval) {
		unlink(tmpname);
	} else if(rename(tmpname, dst)) {
		unlink(tmpname);
		perror(tmpname);
		retval = -1;
	}
	free(tmpname);
	return retval;
}

static int
asn1c_copy_over(arg_t *arg, char *path) {
	char *fname;
#ifdef	_WIN32
	int use_real_copy = 1;
#else
	int use_real_copy = !(arg->flags & A1C_LINK_SKELETONS);
#endif

	fname = a1c_basename(path);
	if(!fname
	|| (use_real_copy ? real_copy(path, fname) : symlink(path, fname))
	) {
		if(errno == EEXIST) {
			struct stat sb1, sb2;
			if(stat(path, &sb1) == 0
			&& stat(fname, &sb2) == 0
			&& sb1.st_dev == sb2.st_dev
			&& sb1.st_ino == sb2.st_ino) {
				/*
				 * Nothing to do.
				 */
				fprintf(stderr,
					"File %s is already here as %s\n",
					path, fname);
				return 1;
			} else {
				fprintf(stderr,
					"Retaining local %s (%s suggested)\n",
					fname, path);
				return 1;
			}
		} else if(errno == ENOENT) {
			/* Ignore this */
			return 0;
		} else {
			fprintf(stderr, "%s %s -> %s failed: %s\n",
				use_real_copy ? "Copy" : "Symlink",
				path, fname, strerror(errno));
			return -1;
		}
	}

	fprintf(stderr, "%s %s\t-> %s\n",
		use_real_copy ? "Copied" : "Symlinked", path, fname);

	return 1;
}

static int
generate_pdu_collection_file(arg_t *arg) {
	asn1p_module_t *mod;
	FILE *fp;

	fp = asn1c_open_file("pdu_collection", ".cpp", 0);
	if(fp == NULL) {
		perror("pdu_collection.cpp");
		return -1;
	}

	fprintf(fp,
		"/*\n"
		" * Generated by asn1cpp-" VERSION " which is based on asn1c-" ASN1C_VERSION " (http://lionet.info/asn1c)\n"
		" */\n\n");
	fprintf(fp, "struct asn_TYPE_descriptor_s;\t"
			"/* Forward declaration */\n\n");

	TQ_FOR(mod, &(arg->asn->modules), mod_next) {
		TQ_FOR(arg->expr, &(mod->members), next) {
			if(!include_type_to_pdu_collection(arg))
				continue;
      if (!(arg->flags & A1C_NO_NAMESPACE)) {
        fprintf(fp, "namespace %s { ", asn1c_make_namespace_name(arg, arg->expr, 0));
      }
      fprintf(fp, "extern struct asn_TYPE_descriptor_s "
        "asn_DEF_%s;",
        asn1c_make_identifier(0, arg->expr, (char*)NULL));
      if (!(arg->flags & A1C_NO_NAMESPACE)) {
        fprintf(fp, " }");
      }
      fprintf(fp, "\n");
		}
	}

	fprintf(fp, "\n\n");
	fprintf(fp, "struct asn_TYPE_descriptor_s *asn_pdu_collection[] = {\n");
	TQ_FOR(mod, &(arg->asn->modules), mod_next) {
		int mod_printed = 0;
		TQ_FOR(arg->expr, &(mod->members), next) {
			if(!include_type_to_pdu_collection(arg))
				continue;
			if(!mod_printed++)
			fprintf(fp, "\t/* From module %s in %s */\n",
				arg->expr->module->ModuleName,
				arg->expr->module->source_file_name);
      fprintf(fp, "\t&");
      if (!(arg->flags & A1C_NO_NAMESPACE)) {
        fprintf(fp, "%s::", asn1c_make_namespace_name(arg, arg->expr, 0));
      }
			fprintf(fp, "asn_DEF_%s,\t\n",
				asn1c_make_identifier(0, arg->expr, (char*)NULL));
		}
	}

	fprintf(fp, "\t0\n};\n\n");

	pdu_collection_print_unused_types(arg);

	fclose(fp);
	fprintf(stderr, "Generated pdu_collection.cpp\n");

	return 0;
}

#undef ASN1C_VERSION

static struct PDUType {
	char *typename;
	int used;
} *pduType;
static int pduTypes;

static const char *
generate_pdu_C_definition(void) {
	const char *src;
	char *def;
	char *dst;
	if(pduTypes == 0) return "";
	def = malloc(strlen(pduType[0].typename) + 20);
	strcpy(def, " -DPDU=");
	for(src = pduType[0].typename, dst = def + 7; *src; src++, dst++)
		if((*dst = *src) == '-')
			*dst = '_';
	*dst = 0;
	return def;
}

void
asn1c__add_pdu_type(const char *ctypename) {
	char *typename = strdup(ctypename);
	assert(typename && *typename);

	pduType = realloc(pduType, sizeof(pduType[0]) * (pduTypes + 1));
	assert(pduType);
	pduType[pduTypes].used = 0;
	pduType[pduTypes].typename = typename;
	pduTypes++;
}

static int
asn1c__pdu_type_lookup(const char *typename) {
	int i;
	for(i = 0; i < pduTypes; i++) {
		struct PDUType *pt = &pduType[i];
		if(strcmp(pt->typename, typename) == 0) {
			pt->used++;
			return 1;
		}
	}
	return 0;
}

static int
need_to_generate_pdu_collection(arg_t *arg) {
	if(arg->flags & (A1C_PDU_ALL|A1C_PDU_AUTO))
		return 1;
	if(arg->flags & A1C_PDU_TYPE)
		return (pduTypes >= 1) ? 1 : 0;
	return 0;
}

static void
pdu_collection_print_unused_types(arg_t *arg) {
	int i;
	for(i = 0; i < pduTypes; i++) {
		struct PDUType *pt = &pduType[i];
		if(!pt->used) {
			WARNING("Missing type specified in -pdu=%s",
				pt->typename);
		}
	}
}

static int
include_type_to_pdu_collection(arg_t *arg) {
	if(!asn1_lang_map[arg->expr->meta_type]
		[arg->expr->expr_type].type_cb)
		return 0;

	if((arg->flags & A1C_PDU_ALL)
	|| ((arg->flags & A1C_PDU_AUTO) && !arg->expr->_type_referenced)
	|| asn1c__pdu_type_lookup(arg->expr->Identifier)) {
		return 1;
	}

	return 0;
}
