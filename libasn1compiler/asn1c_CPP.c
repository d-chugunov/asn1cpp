/*
 * Don't look into this file. First, because it's a mess, and second, because
 * it's a brain of the compiler, and you don't wanna mess with brains do you? ;)
 */
#include "asn1c_internal.h"
#include "asn1c_CPP.h"
#include "asn1c_constraint.h"
#include "asn1c_out.h"
#include "asn1c_misc.h"
#include <asn1fix_crange.h>	/* constraint groker from libasn1fix */
#include <asn1fix_export.h>	/* other exportables from libasn1fix */

typedef struct tag2el_s {
	struct asn1p_type_tag_s el_tag;
	int el_no;
	int toff_first;
	int toff_last;
	asn1p_expr_t *from_expr;
} tag2el_t;

typedef enum fte {
	FTE_ALLTAGS,
	FTE_CANONICAL_XER,
} fte_e;
static int _fill_tag2el_map(arg_t *arg, tag2el_t **tag2el, int *count, int el_no, fte_e flags);
static int _add_tag2el_member(arg_t *arg, tag2el_t **tag2el, int *count, int el_no, fte_e flags);

enum onc_flags {
	ONC_noflags		= 0x00,
	ONC_avoid_keywords	= 0x01,
	ONC_force_compound_name	= 0x02,
  ONC_force_no_compound_name = 0x04
};
static int out_name_chain(arg_t *arg, enum onc_flags);
static int asn1c_lang_CPP_type_SEQUENCE_def(arg_t *arg);
static void emit_class_support_functions(arg_t *arg, const char* inheritFrom, void(*extra_copy_move)(arg_t*,int), void(*extra_implementation_functions)(arg_t*));
static void emit_class_support_functions_headers(arg_t* arg, const char* inheritFrom, void(*extra_function_def)(arg_t*));
static int asn1c_lang_CPP_type_SET_def(arg_t *arg);
static int asn1c_lang_CPP_type_CHOICE_def(arg_t *arg);
static int asn1c_lang_CPP_type_SEx_OF_def(arg_t *arg, int seq_of);
static int _print_tag(arg_t *arg, struct asn1p_type_tag_s *tag_p);
static int compute_extensions_start(asn1p_expr_t *expr);
static int expr_break_recursion(arg_t *arg, asn1p_expr_t *expr);
static int expr_as_xmlvaluelist(arg_t *arg, asn1p_expr_t *expr);
static int expr_elements_count(arg_t *arg, asn1p_expr_t *expr);
static int emit_single_member_PER_constraint(arg_t *arg, asn1cnst_range_t *range, int juscountvalues, char *type);
static int emit_member_PER_constraints(arg_t *arg, asn1p_expr_t *expr, const char *pfx);
static int emit_member_table(arg_t *arg, asn1p_expr_t *expr, int element_index);
static int emit_tag2member_map(arg_t *arg, tag2el_t *tag2el, int tag2el_count, const char *opt_modifier);
static int emit_include_dependencies(arg_t *arg);
static asn1p_expr_t *terminal_structable(arg_t *arg, asn1p_expr_t *expr);
static int expr_defined_recursively(arg_t *arg, asn1p_expr_t *expr);
static int asn1c_recurse(arg_t *arg, asn1p_expr_t *expr, int (*callback)(arg_t *arg, void *key), void *key);
static asn1p_expr_type_e expr_get_type(arg_t *arg, asn1p_expr_t *expr);
static int try_inline_default(arg_t *arg, asn1p_expr_t *expr, int out, int only_func_name);
static int *compute_canonical_members_order(arg_t *arg, int el_count);
static int safe_string(const uint8_t *buf, int size);
static void emit_ref_class(arg_t *arg);
static void emit_getPtrOnMember_header(arg_t* arg);
static void emit_getPtrOnMember_implementation(arg_t* arg);
static void asn1c_lang_CPP_type_SET_SEQUENCE_extra_function_definition(arg_t *arg);
static void asn1c_lang_CPP_type_SET_SEQUENCE_extra_function_implementation(arg_t *arg);
static void emit_constraint_for_type(arg_t* arg, asn1p_expr_t *expr);
static void emit_class_dependency(arg_t* arg, asn1p_expr_t *expr);

enum tvm_compat {
	_TVM_SAME	= 0,	/* tags and all_tags are same */
	_TVM_SUBSET	= 1,	/* tags are subset of all_tags */
	_TVM_DIFFERENT	= 2,	/* tags and all_tags are different */
};
static enum tvm_compat emit_tags_vectors(arg_t *arg, asn1p_expr_t *expr, int *tc, int *atc);

enum etd_spec {
	ETD_NO_SPECIFICS,
	ETD_HAS_SPECIFICS
};
static int emit_type_DEF(arg_t *arg, asn1p_expr_t *expr, enum tvm_compat tv_mode, int tags_count, int all_tags_count, int elements_count, enum etd_spec);

#define	C99_MODE	(!(arg->flags & A1C_NO_C99))
#define	HIDE_INNER_DEFS	(arg->embed)

#define	DEPENDENCIES	do {						\
	emit_include_dependencies(arg);					\
} while(0)

/* MKID_safe() without checking for reserved keywords */
#define	MKID(expr)	(asn1c_make_identifier(0, expr, (char*)0))
#define	MKID_safe(expr)	(asn1c_make_identifier(AMI_CHECK_RESERVED, expr, (char*)0))

#define IS_INDIRECT_CHOICE_TYPE(expr) (expr->parent_expr &&                 \
                      ASN_CONSTR_CHOICE == expr->parent_expr->expr_type &&  \
                      !(arg->flags & A1C_DIRECT_CHOICE))

#define IS_SINGLE_UNIT(arg) (arg->flags & A1C_SINGLE_UNIT)

int
asn1c_lang_CPP_type_REAL(arg_t *arg) {
	return asn1c_lang_CPP_type_SIMPLE_TYPE(arg);
}

struct value2enum {
	asn1c_integer_t	 value;
	const char	*name;
	int		 idx;
};
static int compar_enumMap_byName(const void *ap, const void *bp) {
	const struct value2enum *a = (const struct value2enum *)ap;
	const struct value2enum *b = (const struct value2enum *)bp;
	return strcmp(a->name, b->name);
}
static int compar_enumMap_byValue(const void *ap, const void *bp) {
	const struct value2enum *a = (const struct value2enum *)ap;
	const struct value2enum *b = (const struct value2enum *)bp;
	if(a->value < b->value)
		return -1;
	else if(a->value == b->value)
		return 0;
	return 1;
}

static int
check_string_size(char** strPtr, size_t length, size_t* size, size_t appendLength) {
  while (length + appendLength + 1 /* null terminated string */ > *size) {
    size_t oldSize = *size;
    *size = *size ? *size << 2 : 128;
    void* newPtr = realloc(*strPtr, *size);
    if (!newPtr) {
      free(*strPtr);
      *strPtr = 0;
      *size = 0;
      return 0;
    } else {
      *strPtr = newPtr;
      if (!oldSize)
        (*strPtr)[0] = '\0';
    }
  }
  return 1;
}

static int
strcat_safe(char** destStrPtr, size_t* length, size_t* size, const char* sourceStr) {
  size_t sourceStrLength = strlen(sourceStr);
  if (!check_string_size(destStrPtr, *length, size, sourceStrLength))
    return 0;
  strcat(*destStrPtr, sourceStr);
  *length += sourceStrLength;
  return 1;
}

#define IS_SECURE_POINTERS(arg) (!(arg->flags & A1C_INSECURE_POINTERS))
#define IS_PTR_CHOICE_GETTERS(arg) (arg->flags & A1C_PTR_CHOICE_GETTERS)

static void
out_pointer_head(arg_t *arg)
{
  if (IS_SECURE_POINTERS(arg))
    OUT("std::unique_ptr<");
}

static void
out_pointer_tail(arg_t *arg, asn1p_expr_t *expr)
{
  if(IS_SECURE_POINTERS(arg) && !IS_INDIRECT_CHOICE_TYPE(expr))
    OUT(">");
  else
    OUT("*");
}

/*
 * returns:
 *   -1 : error
 *    0 : nothing has been added to a string
 *    >0 : something was added to a string
 */
static int
make_name_chain_for_class_name(arg_t *arg, asn1p_expr_t *expr, 
          int wasAnnonymous, char** strPtr, size_t* strLength, size_t* strSize) 
{
  /*
   * This function is based on out_name_chain and out_full_class_name_helper
   */
  enum onc_flags onc_flags = ONC_avoid_keywords;
	char *id;
  int wasPrintSomething = 0;
 
#define IS_PRINT_SOMETHING (!wasAnnonymous)

	assert(expr->Identifier);

	if((arg->flags & A1C_COMPOUND_NAMES
	   || onc_flags & ONC_force_compound_name)
	&& ((expr->expr_type & ASN_CONSTR_MASK)
	   || expr->expr_type == ASN_BASIC_ENUMERATED
	   || ((expr->expr_type == ASN_BASIC_INTEGER
	   	|| expr->expr_type == ASN_BASIC_BIT_STRING)
		&& expr_elements_count(arg, expr))
	   )
	&& expr->parent_expr
	&& expr->parent_expr->Identifier) {
		arg_t tmparg = *arg;

		tmparg.expr = expr->parent_expr;
		if(0) tmparg.flags &= ~A1C_COMPOUND_NAMES;

		wasPrintSomething = make_name_chain_for_class_name(&tmparg, tmparg.expr, 
                            expr->_anonymous_type, strPtr, strLength, strSize);
    
    if (wasPrintSomething < 0)
      return -1;

    if (IS_PRINT_SOMETHING && wasPrintSomething && 
            !strcat_safe(strPtr, strLength, strSize, "__")) /* a separator between id components */
      return -1;

		/* Fall through */
	}

  if (IS_PRINT_SOMETHING) {
    if(onc_flags & ONC_avoid_keywords)
      id = MKID_safe(expr);
    else
      id = MKID(expr);
    if (!strcat_safe(strPtr, strLength, strSize, id)) 
        return -1;
    wasPrintSomething = 1;
  }

	return wasPrintSomething;
#undef IS_PRINT_SOMETHING
}

#define IS_GENERATE_DECLARATION (arg->gen_inner_class_declaration || !arg->embed)
#define WAS_CREATED_INNER_CLASS_FOR_THIS_FIELD(expr)  (expr->expr_type & ASN_CONSTR_MASK)
#define IS_NEED_GEN_DECLARATION(expr)                                          \
  (WAS_CREATED_INNER_CLASS_FOR_THIS_FIELD(expr) ||                             \
  expr->expr_type == ASN_BASIC_ENUMERATED ||                                   \
  ((expr->expr_type == ASN_BASIC_INTEGER ||                                    \
          expr->expr_type == ASN_BASIC_BIT_STRING) &&                          \
        expr_elements_count(arg, expr)))                             

/*
 * CAUTION: You will have to free return pointer
 */
static char*
make_class_name(arg_t *arg, asn1p_expr_t *expr) {
#define FAILED_TO_CREATE_CLASS_NAME \
  if (str) free(str);               \
  str = 0;                          \
  return str;
  
  
  char* str = 0;
  size_t length = 0;
  size_t size = 0;
  if (WAS_CREATED_INNER_CLASS_FOR_THIS_FIELD(expr)) {
    int i;
    for (i = 0; i < expr->_anonymous_type; ++i) {
      if (!strcat_safe(&str, &length, &size, "_")) {
        FAILED_TO_CREATE_CLASS_NAME
      }
    }
  }
  if (make_name_chain_for_class_name(arg, expr, 0, &str, &length, &size) < 0) {
    FAILED_TO_CREATE_CLASS_NAME
  }
  return str;
#undef FAILED_TO_CREATE_CLASS_NAME
}

/*
 * Use this macro together with FREE_CLASS_NAME
 */
#define MAKE_CLASS_NAME(func_name, expr)                                      \
  char* className = make_class_name(arg, expr);                               \
  if (!className) {                                                           \
    FATAL("Unable to allocate memory for className in %s", func_name);        \
    return;                                                                   \
  }

#define FREE_CLASS_NAME free(className); className = 0;

static void 
emit_namespace_name(arg_t *arg, asn1p_expr_t *parent_expr, asn1p_expr_t *expr) {
  if (expr->expr_type == A1TC_REFERENCE) {
    expr = asn1f_lookup_symbol_ex(arg->asn, expr, expr->reference);
    assert(expr != 0);
  }
  if (parent_expr && !(arg->flags & A1C_NO_NAMESPACE) && 
          strcmp(parent_expr->module->ModuleName, expr->module->ModuleName) != 0) 
  {
    OUT("%s::", asn1c_make_namespace_name(arg, expr, 0));
  }
}

/*
 * This function prints the name of class
 */
static inline void out_class_name(arg_t *arg, asn1p_expr_t *expr) {
  MAKE_CLASS_NAME("out_class_name", expr);
  emit_namespace_name(arg, expr->parent_expr, expr);
  OUT("%s", className);
  FREE_CLASS_NAME
}

#define OUT_ENUM_NAME(arg, expr)                  \
    OUT("enum ");                                 \
    if (arg->embed) {                             \
      out_class_name(arg, expr);                  \
    } else {                                      \
        out_name_chain(arg, ONC_avoid_keywords);  \
    }                                             \
    OUT("_enum");

#define OUT_ENUM_END(arg) \
  OUT("};\n");

int
asn1c_lang_CPP_type_common_INTEGER(arg_t *arg) {
	asn1p_expr_t *expr = arg->expr;
	asn1p_expr_t *v;
	int el_count = expr_elements_count(arg, expr);
	struct value2enum *v2e;
	int map_extensions = (expr->expr_type == ASN_BASIC_INTEGER);
	int eidx;

	v2e = alloca((el_count + 1) * sizeof(*v2e));

	/*
	 * For all ENUMERATED types and for those INTEGER types which
	 * have identifiers, print out an enumeration table.
	 */
	if((expr->expr_type == ASN_BASIC_ENUMERATED || el_count) && IS_GENERATE_DECLARATION) {
		eidx = 0;
		//REDIR(OT_DEPS);
		OUT_ENUM_NAME(arg, expr)
		OUT(" {\n");
		TQ_FOR(v, &(expr->members), next) {
			switch(v->expr_type) {
			case A1TC_UNIVERVAL:
				OUT("\t");
				out_name_chain(arg, ONC_force_no_compound_name);
				OUT("_%s", MKID(v));
				OUT("\t= %" PRIdASN "%s\n",
					v->value->value.v_integer,
					(eidx+1 < el_count) ? "," : "");
				v2e[eidx].name = v->Identifier;
				v2e[eidx].value = v->value->value.v_integer;
				eidx++;
				break;
			case A1TC_EXTENSIBLE:
				OUT("\t/*\n");
				OUT("\t * Enumeration is extensible\n");
				OUT("\t */\n");
				if(!map_extensions)
					map_extensions = eidx + 1;
				break;
			default:
				return -1;
			}
		}
		//OUT("} e_");
		//	out_name_chain(arg, ONC_noflags);
    OUT_ENUM_END(arg)
		assert(eidx == el_count);
	}

	/*
	 * For all ENUMERATED types print out a mapping table
	 * between identifiers and associated values.
	 * This is prohibited for INTEGER types by by X.693:8.3.4.
	 */
	if(expr->expr_type == ASN_BASIC_ENUMERATED && IS_GENERATE_DECLARATION) {

		/*
		 * Generate a enumerationName<->value map for XER codec.
		 */
		REDIR(OT_STAT_DEFS);

		OUT("static const asn_INTEGER_enum_map_t asn_MAP_%s_value2enum_%d[] = {\n",
			MKID(expr), expr->_type_unique_index);
		qsort(v2e, el_count, sizeof(v2e[0]), compar_enumMap_byValue);
		for(eidx = 0; eidx < el_count; eidx++) {
			v2e[eidx].idx = eidx;
			OUT("\t{ %" PRIdASN ",\t%ld,\t\"%s\" }%s\n",
				v2e[eidx].value,
				(long)strlen(v2e[eidx].name), v2e[eidx].name,
				(eidx + 1 < el_count) ? "," : "");
		}
		if(map_extensions)
			OUT("\t/* This list is extensible */\n");
		OUT("};\n");

		OUT("static const unsigned int asn_MAP_%s_enum2value_%d[] = {\n",
			MKID(expr), expr->_type_unique_index);
		qsort(v2e, el_count, sizeof(v2e[0]), compar_enumMap_byName);
		for(eidx = 0; eidx < el_count; eidx++) {
			OUT("\t%d%s\t/* %s(%" PRIdASN ") */\n",
				v2e[eidx].idx,
				(eidx + 1 < el_count) ? "," : "",
				v2e[eidx].name, v2e[eidx].value);
		}
		if(map_extensions)
			OUT("\t/* This list is extensible */\n");
		OUT("};\n");

		OUT("static const asn_INTEGER_specifics_t asn_SPC_%s_specs_%d = {\n",
			MKID(expr), expr->_type_unique_index);
		INDENT(+1);
		OUT("asn_MAP_%s_value2enum_%d,\t"
			"/* \"tag\" => N; sorted by tag */\n",
			MKID(expr),
			expr->_type_unique_index);
		OUT("asn_MAP_%s_enum2value_%d,\t"
			"/* N => \"tag\"; sorted by N */\n",
			MKID(expr),
			expr->_type_unique_index);
		OUT("%d,\t/* Number of elements in the maps */\n",
			el_count);
		if(map_extensions) {
			OUT("%d,\t/* Extensions before this member */\n",
				map_extensions);
		} else {
			OUT("0,\t/* Enumeration is not extensible */\n");
		}
		if(expr->expr_type == ASN_BASIC_ENUMERATED)
			OUT("1,\t/* Strict enumeration */\n");
		else
			OUT("0,\n");
		OUT("0,\t/* Native long size */\n");
		OUT("0\n");
		INDENT(-1);
		OUT("};\n");
	}
  
  if((expr->expr_type == ASN_BASIC_ENUMERATED || el_count) &&  
                                        arg->gen_inner_class_declaration) 
  {
    //If this condition is true it means that we are just generating definition of 
    //enum. At that point we have already done it, therefore we have to just return
    REDIR(OT_TYPE_DECLS);
    return 0;
  }

	if(expr->expr_type == ASN_BASIC_INTEGER
	&& asn1c_type_fits_long(arg, expr) == FL_FITS_UNSIGN) {
		REDIR(OT_STAT_DEFS);
		OUT("static const asn_INTEGER_specifics_t asn_SPC_%s_specs_%d = {\n",
			MKID(expr), expr->_type_unique_index);
		INDENT(+1);
		OUT("0,\t");
		OUT("0,\t");
		OUT("0,\t");
		OUT("0,\t");
		OUT("0,\n");
		OUT("0,\t/* Native long size */\n");
		OUT("1\t/* Unsigned representation */\n");
		INDENT(-1);
		OUT("};\n");
	}

	return asn1c_lang_CPP_type_SIMPLE_TYPE(arg);
}

int
asn1c_lang_CPP_type_BIT_STRING(arg_t *arg) {
	asn1p_expr_t *expr = arg->expr;
	asn1p_expr_t *v;
	int el_count = expr_elements_count(arg, expr);

	if(el_count && IS_GENERATE_DECLARATION) {
		int eidx = 0;
		//REDIR(OT_DEPS);
		OUT_ENUM_NAME(arg, expr)
		OUT(" {\n");
		TQ_FOR(v, &(expr->members), next) {
			if(v->expr_type != A1TC_UNIVERVAL) {
				OUT("/* Unexpected BIT STRING element: %s */\n",
				v->Identifier);
				continue;
			}
			eidx++;
			OUT("\t");
			out_name_chain(arg, ONC_noflags);
			OUT("_%s", MKID(v));
			OUT("\t= %" PRIdASN "%s\n",
				v->value->value.v_integer,
				(eidx < el_count) ? "," : "");
		}
//		OUT("} e_");
//			out_name_chain(arg, ONC_noflags);
		OUT_ENUM_END(arg)
    
		assert(eidx == el_count);
	}
  
  if (arg->gen_inner_class_declaration) {
    //it's the case of enum generation. Since we have to quit
    return 0;
  }

	return asn1c_lang_CPP_type_SIMPLE_TYPE(arg);
}

//inline void out_class_field_name(arg_t *arg, asn1p_expr_t *expr) {
//  OUT ("%s", MKID_safe(expr));
//  if (WAS_CREATED_INNER_CLASS_FOR_THIS_FIELD(expr))
//    OUT("_");
//}

static int
out_full_class_name_helper(arg_t *arg, int wasAnnonymous) {
  /*
   * This function is based on out_name_chain
   * See also make_name_chain_for_class_name function
   */
  const static enum onc_flags onc_flags = ONC_avoid_keywords | ONC_force_compound_name;
	asn1p_expr_t *expr = arg->expr;
  int wasPrintSomething = 0;
  
#define IS_PRINT_SOMETHING (!wasAnnonymous)
  

	assert(expr->Identifier);

	if((arg->flags & A1C_COMPOUND_NAMES
	   || onc_flags & ONC_force_compound_name)
	&& ((expr->expr_type & ASN_CONSTR_MASK)
	   || expr->expr_type == ASN_BASIC_ENUMERATED
	   || ((expr->expr_type == ASN_BASIC_INTEGER
	   	|| expr->expr_type == ASN_BASIC_BIT_STRING)
		&& expr_elements_count(arg, expr))
	   )
	&& expr->parent_expr
	&& expr->parent_expr->Identifier) {
		arg_t tmparg = *arg;

		tmparg.expr = expr->parent_expr;
		if(0) tmparg.flags &= ~A1C_COMPOUND_NAMES;

		wasPrintSomething = out_full_class_name_helper(&tmparg, expr->_anonymous_type);

    if (IS_PRINT_SOMETHING && wasPrintSomething)
      OUT("::");	/* a separator between id components */

		/* Fall through */
	}

  if (IS_PRINT_SOMETHING) {
    out_class_name(arg, expr);
    wasPrintSomething = 1;
  }

	return wasPrintSomething;
  
#undef IS_PRINT_SOMETHING
}

static int
out_full_class_name(arg_t *arg) {
  return out_full_class_name_helper(arg, 0);
}

#define IS_USED_UNION_WITH_CHOICE(expr) \
    (ASN_CONSTR_CHOICE == expr->expr_type && !(arg->flags & A1C_DIRECT_CHOICE))

#define IS_CLASS_FIELD(expr) expr->expr_type != A1TC_EXTENSIBLE

#define IS_PTR_MEMBER(expr) expr->marker.flags & EM_INDIRECT

#define IS_PTR_FIELD_WITH_DEFAULT_METHOD(v) \
  IS_CLASS_FIELD(v) && IS_PTR_MEMBER(v) && try_inline_default(arg, v, 0, 2)

#define ZERO_OUT_PTR_FIELD(arg, expr)                                     \
  do {                                                                    \
  if (IS_PTR_MEMBER(expr) && !IS_SECURE_POINTERS(arg) &&                  \
      !IS_INDIRECT_CHOICE_TYPE(expr))                                     \
    OUT(" = 0");                                                          \
  } while(0)

#define HAS_MEMBERS(arg, expr) (expr_elements_count(arg, expr))

static int GenerateClass(arg_t* arg, const char* inheritFrom, 
                         int(*def_func)(arg_t*), void(*extra_type_def)(arg_t*), 
                         void(*extra_field_def)(arg_t*),
                         void(*extra_function_def)(arg_t*)) 
{
  asn1p_expr_t *expr = arg->expr;
	asn1p_expr_t *v;
	int comp_mode = 0;	/* {root,ext=1,root,root,...} */
  DEPENDENCIES;
  if (IS_GENERATE_DECLARATION) {
    OUT("class ");
    out_class_name(arg, expr);
    OUT(" : public %s", inheritFrom);
    OUT(" {\n");
    OUT("public:\n");
    if (extra_type_def)
      INDENTED(extra_type_def(arg));
    TQ_FOR(v, &(expr->members), next) {
      if (IS_NEED_GEN_DECLARATION(v))
        EMBED_CLASS_DECLARATION(v);
    }
    
    if (IS_USED_UNION_WITH_CHOICE(expr)) {
      OUT("private: //fields of class ");
      out_full_class_name(arg);
      OUT("\n");
      INDENT(+1);
      OUT("union {\n");
    } else {
      OUT("public: //fields of class ");
      out_full_class_name(arg);
      OUT("\n");
    }
    TQ_FOR(v, &(expr->members), next) {
      if (expr->expr_type != ASN_CONSTR_CHOICE) {
        //it should be executed in case of CHOICE type
        if(v->expr_type == A1TC_EXTENSIBLE)
          if(comp_mode < 3) comp_mode++;
        if(comp_mode == 1)
          v->marker.flags |= EM_OMITABLE | EM_INDIRECT;
        try_inline_default(arg, v, 1, 0);
      }
      if (IS_USED_UNION_WITH_CHOICE(expr))
        v->marker.flags |= EM_INDIRECT;
      EMBED(v);
    }
    if (IS_USED_UNION_WITH_CHOICE(expr)) {
      OUT("} _choice");
      if (HAS_MEMBERS(arg, expr))
        OUT(" = {nullptr}");
      OUT(";\n");
      INDENT(-1);
    }
    if (extra_field_def) {
      if (!IS_USED_UNION_WITH_CHOICE(expr))
        OUT("private:\n");
      INDENTED(extra_field_def(arg));
    }
    emit_class_support_functions_headers(arg, inheritFrom, extra_function_def);
    
    OUT("}; //End of class ");
    out_class_name(arg, expr);
    OUT("\n");
    return def_func(arg);
  } else {
    if(arg->embed) {
      if (expr->marker.flags & EM_INDIRECT) {
        if(!expr->_anonymous_type && !IS_INDIRECT_CHOICE_TYPE(expr))
          out_pointer_head(arg); //prints "std::unique_ptr<" or nothing
      }
      OUT("class ");
      out_class_name(arg, expr);
      if(!expr->_anonymous_type) {
        if (expr->marker.flags & EM_INDIRECT) {
          out_pointer_tail(arg, expr); //prints ">" or "*"
        }
        OUT(" %s", MKID_safe(expr));
        ZERO_OUT_PTR_FIELD(arg, expr);
        if((expr->marker.flags & EM_OPTIONAL) == EM_OPTIONAL)
          OUT("\t/* OPTIONAL */");
      }
    }
    return 0;
  }
}

static int will_have_default_method_for_ptr_field(arg_t *arg) {
  asn1p_expr_t *expr = arg->expr;
  asn1p_expr_t *v;
  TQ_FOR(v, &(expr->members), next) {
    if (IS_PTR_FIELD_WITH_DEFAULT_METHOD(v)) {
      return 1;
    }
  }
  return 0;
}

static void asn1c_lang_CPP_type_SET_SEQUENCE_DEFAULT_extra_function_definition(arg_t *arg) {
  if (will_have_default_method_for_ptr_field(arg)) {
    OUT("/*\n");
    OUT(" * Sets empty DEFAULT components to their default values. Empty components are null pointer components, they have no value.\n");
    OUT(" * Returns true if there were no errors during the operation. Else it returns false.\n");
    OUT(" */\n");
    OUT("bool SetEmptyToDefault();\n");
  }
}

static void asn1c_lang_CPP_type_SET_SEQUENCE_DEFAULT_extra_function_implementation(arg_t *arg) {
  if (will_have_default_method_for_ptr_field(arg)) {
    OUT("bool ");
    out_full_class_name(arg);
    OUT("::SetEmptyToDefault() {\n");
    INDENT(+1);
    OUT("bool noErr = true;\n");
    asn1p_expr_t *expr = arg->expr;
    asn1p_expr_t *v;
    TQ_FOR(v, &(expr->members), next) {
      if (IS_PTR_FIELD_WITH_DEFAULT_METHOD(v)) {
        char* identifierBig = 0;
        {
          char* identifier = MKID_safe(v);
          identifierBig = malloc(strlen(identifier) + 1);
          if (!identifierBig) {
            FATAL("Unable to allocate memory for identifierBig in asn1c_lang_CPP_type_SET_SEQUENCE_DEFAULT_extra_function_implementation");
            return;
          }
          strcpy(identifierBig, identifier);
          if (identifierBig && strlen(identifierBig))
            identifierBig[0] = toupper(identifierBig[0]);
        }

        OUT("if (!%s)\n", MKID_safe(v));
        INDENTED(OUT("noErr &= Set%sDefault();\n", identifierBig));

        free(identifierBig);
      }
    }
    OUT("return noErr;\n");
    INDENT(-1);
    OUT("}\n");
    OUT("\n");
  }
}

#undef IS_PTR_FIELD_WITH_DEFAULT_METHOD

int
asn1c_lang_CPP_type_SEQUENCE(arg_t *arg) {
  return GenerateClass(arg, "constr_SEQUENCE", 
                       asn1c_lang_CPP_type_SEQUENCE_def, 0, 0, 
          asn1c_lang_CPP_type_SET_SEQUENCE_extra_function_definition);
}

static int
asn1c_lang_CPP_type_SEQUENCE_def(arg_t *arg) {
	asn1p_expr_t *expr = arg->expr;
	asn1p_expr_t *v;
	int elements;	/* Number of elements */
	int ext_start = -2;
	int ext_stop = -2;
	tag2el_t *tag2el = NULL;
	int tag2el_count = 0;
	int tags_count;
	int all_tags_count;
	enum tvm_compat tv_mode;
	int roms_count;		/* Root optional members */
	int aoms_count;		/* Additions optional members */

	/*
	 * Fetch every inner tag from the tag to elements map.
	 */
	if(_fill_tag2el_map(arg, &tag2el, &tag2el_count, -1, FTE_ALLTAGS)) {
		if(tag2el) free(tag2el);
		return -1;
	}

	GEN_INCLUDE_STD("constr_SEQUENCE");
	if(!arg->embed)
		GEN_DECLARE(expr);	/* asn_DEF_xxx */

	REDIR(OT_STAT_DEFS);

	/*
	 * Print out the table according to which parsing is performed.
	 */
  int countOfElements = expr_elements_count(arg, expr);
	if(countOfElements) {
		int comp_mode = 0;	/* {root,ext=1,root,root,...} */

		OUT("static asn_TYPE_member_t asn_MBR_%s_%d[] = {\n",
			MKID(expr), expr->_type_unique_index);

		elements = 0;
		roms_count = 0;
		aoms_count = 0;
		INDENTED(TQ_FOR(v, &(expr->members), next) {
			if(v->expr_type == A1TC_EXTENSIBLE) {
				if((++comp_mode) == 1)
					ext_start = elements - 1;
				else
					ext_stop = elements - 1;
				continue;
			}
			if(v->marker.flags & EM_OMITABLE)
			    comp_mode == 1 ? ++aoms_count : ++roms_count;
			emit_member_table(arg, v, elements);
			elements++;
		});
		OUT("};\n");

		if((roms_count + aoms_count) && (arg->flags & A1C_GEN_PER)) {
			int elm = 0;
			int comma = 0;
			comp_mode = 0;
			OUT("static const int asn_MAP_%s_oms_%d[] = {",
				MKID(expr),
				expr->_type_unique_index);
			TQ_FOR(v, &(expr->members), next) {
				if(v->expr_type == A1TC_EXTENSIBLE) {
					++comp_mode;
					continue;
				}
				if((v->marker.flags & EM_OMITABLE)
				&& comp_mode != 1) {
					if(!comma) comma++;
					else OUT(",");
					OUT(" %d", elm);
				}
				++elm;
			}
			elm = 0;
			comp_mode = 0;
			TQ_FOR(v, &(expr->members), next) {
				if(v->expr_type == A1TC_EXTENSIBLE) {
					++comp_mode;
					continue;
				}
				if((v->marker.flags & EM_OMITABLE)
				&& comp_mode == 1) {
					if(!comma) comma++;
					else OUT(",");
					OUT(" %d", elm);
				}
				++elm;
			}
			OUT(" };\n");
			if(roms_count > 65536)
				FATAL("Too many optional elements in %s "
					"at line %d!",
					arg->expr->Identifier,
					arg->expr->_lineno);
		} else {
			roms_count = 0;
			aoms_count = 0;
		}
	} else {
		elements = 0;
		roms_count = 0;
		aoms_count = 0;
	}

	/*
	 * Print out asn_DEF_<type>_[all_]tags[] vectors.
	 */
	tv_mode = emit_tags_vectors(arg, expr, &tags_count, &all_tags_count);

	/*
	 * Tags to elements map.
	 */
	emit_tag2member_map(arg, tag2el, tag2el_count, 0);

	OUT("static asn_SEQUENCE_specifics_t asn_SPC_%s_specs_%d = {\n",
		MKID(expr), expr->_type_unique_index);
	INDENT(+1);
  //OUT("0,\n");
	//OUT("sizeof(");
	//	out_name_chain(arg, ONC_avoid_keywords); OUT("),\n");
	//OUT("offsetof(");
	//	out_name_chain(arg, ONC_avoid_keywords); OUT(", _asn_ctx),\n");
    //OUT("0,\n");

	if(tag2el_count) {
		OUT("asn_MAP_%s_tag2el_%d,\n",
			MKID(expr),
			expr->_type_unique_index);
		OUT("%d,\t/* Count of tags in the map */\n", tag2el_count);
	} else {
		OUT("0,\t/* No top level tags */\n");
		OUT("0,\t/* No tags in the map */\n");
	}
  ++arg->ignore_code;
	if(roms_count + aoms_count) {
		OUT("asn_MAP_%s_oms_%d,\t/* Optional members */\n",
			MKID(expr), expr->_type_unique_index);
		OUT("%d, %d,\t/* Root/Additions */\n", roms_count, aoms_count);
	} else {
		OUT("0, 0, 0,\t/* Optional elements (not needed) */\n");
	}
  --arg->ignore_code;
	OUT("%d,\t/* Start extensions */\n",
			ext_start<0 ? -1 : ext_start);
	OUT("%d\t/* Stop extensions */\n",
  (ext_stop<ext_start || !countOfElements)?elements+1:(ext_stop<0?-1:ext_stop));
      //NOTE: commented code is the original variant but it doesn't work 
      //when SEQUENCE consists only of extension marker
			//(ext_stop<ext_start)?elements+1:(ext_stop<0?-1:ext_stop));
	INDENT(-1);
	OUT("};\n");

	/*
	 * Emit asn_DEF_xxx table.
	 */
	emit_type_DEF(arg, expr, tv_mode, tags_count, all_tags_count, elements,
			ETD_HAS_SPECIFICS);
  
  /*
   * Emit functions of the class
   */
  emit_class_support_functions(arg, "constr_SEQUENCE", 0, 
      asn1c_lang_CPP_type_SET_SEQUENCE_extra_function_implementation);
  

	REDIR(OT_TYPE_DECLS);

	return 0;
} /* _SEQUENCE_def() */

static void emit_field_getters_and_setters_headers(arg_t* arg); 

#define IS_SET_TYPE(expr) expr->expr_type == ASN_CONSTR_SET

static size_t GetMemberCount(asn1p_expr_t *expr) {
  asn1p_expr_t *v;
  size_t mcount = 0;
  TQ_FOR(v, &(expr->members), next) {
		if(v->expr_type == A1TC_EXTENSIBLE) continue;
		mcount++;
	}
  return mcount;
}

static void emit_class_support_functions_headers(arg_t* arg, 
                   const char* inheritFrom, void(*extra_function_def)(arg_t*)) 
{
  MAKE_CLASS_NAME("emit_class_support_functions_headers", arg->expr)
  OUT("public:\n");
  INDENTED(
    OUT("%s() : ", className);
    if (IS_SET_TYPE(arg->expr)) {
      OUT("constr_SET( (((%lu)+(8*sizeof(unsigned int))-1)/(8*sizeof(unsigned int))) )", GetMemberCount(arg->expr));
    } else {
      OUT("%s()", inheritFrom);
    }
    OUT(" { }\n");
    OUT("virtual ~%s() noexcept", className);
    if (IS_SECURE_POINTERS(arg) || IS_USED_UNION_WITH_CHOICE(arg->expr)) {
      OUT(" { ");
      if (IS_USED_UNION_WITH_CHOICE(arg->expr))
        OUT("_freeData(); ");
      OUT("} \n");
    } else {
      OUT(";\n");
    }
    OUT("%s(const %s& other) : ", className, className);
    if (IS_SET_TYPE(arg->expr)) {
      OUT("constr_SET(other._presenceMap.size())");
    } else {
      OUT("%s()", inheritFrom);
    }
    OUT(" {\n");
    INDENTED(
      OUT("*this = other;\n");
    );
    OUT("}\n");
    OUT("%s(%s&& other) noexcept : ", className, className, inheritFrom);
    if (IS_SET_TYPE(arg->expr)) {
      OUT("constr_SET(other._presenceMap.size())");
    } else {
      OUT("%s()", inheritFrom);
    }
    OUT(" {\n");
    INDENTED(
      OUT("*this = std::move(other);\n");
    );
    OUT("}\n");
    OUT("%s& operator =(const %s& other);\n", className, className);
    OUT("%s& operator =(%s&& other) noexcept;\n", className, className);
    OUT("void Clear() override {\n");
    INDENTED(
      OUT("*this = %s();\n", className);
      OUT("%s::Clear();\n", inheritFrom);
    );
    OUT("}\n");
    emit_field_getters_and_setters_headers(arg);
    if (extra_function_def)
      extra_function_def(arg);
  );
  OUT("private:\n");
  INDENTED(
    OUT("asn_TYPE_descriptor_t* _getDefaultTypeDescriptorPtr() const override;\n");
  );
  FREE_CLASS_NAME
}

static void emit_constructor_name_for_field(arg_t* arg, asn1p_expr_t *v) {
  if (WAS_CREATED_INNER_CLASS_FOR_THIS_FIELD(v)) {
    if (v->expr_type & ASN_CONSTR_MASK)
      OUT("class ");
    out_class_name(arg, v);
  } else {
    emit_namespace_name(arg, arg->expr, v);
    OUT("%s", asn1c_type_name(arg, v, TNF_CTYPE));
  }
}

static void emit_full_constructor_name_for_field(arg_t* arg, asn1p_expr_t *v) {
  if (WAS_CREATED_INNER_CLASS_FOR_THIS_FIELD(v)) {
    if (v->expr_type & ASN_CONSTR_MASK)
      OUT("class ");
    arg_t temp_arg = *arg;
    temp_arg.expr = v;
    out_full_class_name(&temp_arg);
  } else {
    emit_namespace_name(arg, arg->expr, v);
    OUT("%s", asn1c_type_name(arg, v, TNF_CTYPE));
  }
}

#define EMIT_TYPE_OF_FIELD                                                  \
  if (IS_PTR_MEMBER(v) && !IS_INDIRECT_CHOICE_TYPE(v))                      \
    out_pointer_head(arg);                                                  \
  emit_constructor_name_for_field(arg, v);                                  \
  if (IS_PTR_MEMBER(v))                                                     \
    out_pointer_tail(arg, v);

#define EMIT_FULL_TYPE_OF_FIELD                                             \
  if (IS_PTR_MEMBER(v) && !IS_INDIRECT_CHOICE_TYPE(v))                      \
    out_pointer_head(arg);                                                  \
  emit_full_constructor_name_for_field(arg, v);                             \
  if (IS_PTR_MEMBER(v))                                                     \
    out_pointer_tail(arg, v);

#define EMIT_CHOICE_PR_ENUM_NAME(expr) out_class_name(arg, expr); OUT("_PR")
#define EMIT_CHOICE_PR_ENUM_MEMBER_NAME(v) OUT("PR_%s", MKID(v))
#define EMIT_CHOICE_PR_NOTHING_MEMBER_NAME OUT("PR_NOTHING")

static void 
emit_field_getters_and_setters_headers(arg_t* arg) {
  asn1p_expr_t *expr = arg->expr;
  asn1p_expr_t *v;
  TQ_FOR(v, &(expr->members), next) {
    if (IS_CLASS_FIELD(v)) {
      char* identifierBig = 0;
      {
        char* identifier = MKID_safe(v);
        identifierBig = malloc(strlen(identifier) + 1);
        if (!identifierBig) {
          FATAL("Unable to allocate memory for identifierBig in emit_field_getters");
          return;
        }
        strcpy(identifierBig, identifier);
        if (identifierBig && strlen(identifierBig))
          identifierBig[0] = toupper(identifierBig[0]);
      }
      //getters and setters for CHOICE with indirect components
      if (IS_USED_UNION_WITH_CHOICE(expr)) {
        int indirect_flag = v->marker.flags & EM_INDIRECT;
        if (!IS_PTR_CHOICE_GETTERS(arg))
          v->marker.flags &= ~EM_INDIRECT;
        //const get
        OUT("const ");
        EMIT_TYPE_OF_FIELD
        if (!IS_PTR_CHOICE_GETTERS(arg))
          OUT("&");
        OUT(" %s() const {", MKID_safe(v));
        if (IS_PTR_CHOICE_GETTERS(arg)) {
          OUT(" return ");
          EMIT_CHOICE_PR_ENUM_NAME(expr);
          OUT("::");
          EMIT_CHOICE_PR_ENUM_MEMBER_NAME(v);
          OUT(" == this->_present ? this->_choice.%s : nullptr; ", MKID_safe(v));
        } else {
          OUT("\n");
          INDENT(+1);
            OUT("if (");
            EMIT_CHOICE_PR_ENUM_NAME(expr);
            OUT("::");
            EMIT_CHOICE_PR_ENUM_MEMBER_NAME(v);
            OUT(" == this->_present)\n");
            INDENTED(OUT("return *this->_choice.%s;\n", MKID_safe(v)));
            OUT("throw std::runtime_error(\"pointer %s is null\");\n", MKID_safe(v));
          INDENT(-1);
        }
        OUT("}\n");
        //get
        EMIT_TYPE_OF_FIELD
        if (!IS_PTR_CHOICE_GETTERS(arg))
          OUT("&");
        OUT(" %s() {", MKID_safe(v));
        if (IS_PTR_CHOICE_GETTERS(arg)) {
          OUT(" return ");
          EMIT_CHOICE_PR_ENUM_NAME(expr);
          OUT("::");
          EMIT_CHOICE_PR_ENUM_MEMBER_NAME(v);
          OUT(" == this->_present ? this->_choice.%s : nullptr; ", MKID_safe(v));
        } else {
          OUT("\n");
          INDENT(+1);
            OUT("if (");
            EMIT_CHOICE_PR_ENUM_NAME(expr);
            OUT("::");
            EMIT_CHOICE_PR_ENUM_MEMBER_NAME(v);
            OUT(" == this->_present)\n");
            INDENTED(OUT("return *this->_choice.%s;\n", MKID_safe(v)));
            OUT("throw std::runtime_error(\"pointer %s is null\");\n", MKID_safe(v));
          INDENT(-1);
        }
        OUT("}\n");
        if (!IS_PTR_CHOICE_GETTERS(arg))
          v->marker.flags |= indirect_flag;
        //set
        EMIT_TYPE_OF_FIELD
        OUT(" %s(", MKID_safe(v));
        EMIT_TYPE_OF_FIELD
        OUT(" value);\n");
      }
      //extra methods for DEFAULT components of SET and SEQUENCE types
      if ((expr->expr_type == ASN_CONSTR_SET || 
                  expr->expr_type == ASN_CONSTR_SEQUENCE) && 
          v->marker.default_value && try_inline_default(arg, v, 0, 2)) 
      {
          OUT("bool Set%sDefault();\n", identifierBig);
      }
      free(identifierBig);
    }
  }
}

static void emit_default_methods_for_SET_and_SEQUENCE(arg_t* arg, asn1p_expr_t *v, 
                                    const char* identifierBig, enum tnfmt tnfmt) 
{
  OUT("bool ");
  out_full_class_name(arg);
  OUT("::Set%sDefault() {\n", identifierBig);
  INDENTED(
    if (IS_PTR_MEMBER(v)) {
      OUT("bool _wasNull = true;\n");
      OUT("if (this->%s)\n", MKID_safe(v));
      INDENTED(OUT("_wasNull = false;\n"));
      OUT("else\n");
      INDENTED(
        if (IS_SECURE_POINTERS(arg)) {
          OUT("this->%s.reset(new ", MKID_safe(v));
          emit_constructor_name_for_field(arg, v);
          OUT("());\n");
        } else {
          OUT("this->%s = new ", MKID_safe(v));
          emit_constructor_name_for_field(arg, v);
          OUT("();\n");
        }
      );
      OUT("void* _ptr = this->%s", MKID_safe(v));
      if (IS_SECURE_POINTERS(arg))
        OUT(".get()");
      OUT(";\n");
      OUT("if (");
      if (!try_inline_default(arg, v, 0, 1)) {
        WARNING("Unsupported DEFAULT for type of component \"%s\" of %s", v->Identifier, arg->expr->Identifier);
        OUT("0 /* WARNING: unsupported DEFAULT for this type */ )\n");
        INDENTED(OUT("return false;\n"));
        OUT("return false;\n");
      } else { 
        OUT("(1, &_ptr)", MKID_safe(v));
        OUT(") {\n");
        INDENTED(
          OUT("if (_wasNull)");
          if (IS_SECURE_POINTERS(arg)) {
            OUT("\n");
            INDENTED(OUT("this->%s.reset();\n", MKID_safe(v)));
          } else {
            OUT(" {\n");
            INDENT(+1);
              OUT("delete this->%s;\n", MKID_safe(v));
              OUT("this->%s = 0;\n", MKID_safe(v));
            INDENT(-1);
            OUT("}\n");
          }
          OUT("return false;\n");
        );
        OUT("} else {\n");
        INDENTED(
          OUT("return true;\n");
        );
        OUT("}\n");
      }
    } else {
      OUT("void* _ptr = &this->%s;\n", MKID_safe(v));
      OUT("if (");
      if (!try_inline_default(arg, v, 0, 1)) {
        WARNING("Unsupported DEFAULT for type of component \"%s\" of %s", v->Identifier, arg->expr->Identifier);
        OUT("0 /* WARNING: unsupported DEFAULT for this type */ ");
        INDENTED(OUT("return false;\n"));
        OUT("return false;\n");
      } else {
        OUT("(1, &_ptr)");
        OUT(") {\n");
        INDENTED(OUT("return false;\n"););
        OUT("} else {\n");
        INDENTED(
          OUT("return true;\n");
        );
        OUT("}\n");
      }
    }
  );
  OUT("}\n");
  OUT("\n");
}

static void 
emit_field_getters_and_setters_implementation(arg_t* arg) {
  asn1p_expr_t *expr = arg->expr;
  asn1p_expr_t *v;
  enum tnfmt tnfmt = TNF_CTYPE;
  TQ_FOR(v, &(expr->members), next) {
    if (IS_CLASS_FIELD(v)) {
      char* identifierBig = 0;
      {
        char* identifier = MKID_safe(v);
        identifierBig = malloc(strlen(identifier) + 1);
        if (!identifierBig) {
          FATAL("Unable to allocate memory for identifierBig in emit_field_getters");
          return;
        }
        strcpy(identifierBig, identifier);
        if (identifierBig && strlen(identifierBig))
          identifierBig[0] = toupper(identifierBig[0]);
      }
      //getters and setters for CHOICE with indirect components
      if (IS_USED_UNION_WITH_CHOICE(expr)) {
        //set
        EMIT_FULL_TYPE_OF_FIELD
        OUT(" ");
        out_full_class_name(arg);
        OUT("::%s(", MKID_safe(v));
        EMIT_TYPE_OF_FIELD
        OUT(" value) {\n");
        INDENT(+1);
        OUT("_freeData();\n");
        OUT("if (value) {\n");
        INDENTED(
          OUT("this->_choice.%s = value;\n", MKID_safe(v));
          OUT("this->_present = ");
          EMIT_CHOICE_PR_ENUM_NAME(expr);
          OUT("::");
          EMIT_CHOICE_PR_ENUM_MEMBER_NAME(v);
          OUT(";\n");
        );
        OUT("}\n");
        OUT("return value;\n");
        INDENT(-1);
        OUT("}\n");
        OUT("\n");
      }
      //extra methods for DEFAULT components of SET and SEQUENCE types
      if ((expr->expr_type == ASN_CONSTR_SET || 
                  expr->expr_type == ASN_CONSTR_SEQUENCE) && 
          v->marker.default_value && try_inline_default(arg, v, 0, 2)) 
      {
         emit_default_methods_for_SET_and_SEQUENCE(arg, v, identifierBig, tnfmt);
      }
      free(identifierBig);
    }
  }
}

#undef EMIT_TYPE_OF_FIELD

#define EMIT_IMPLEMENTATION_OF_CLASS_COMMENT                                  \
  OUT("/*\n");                                                                \
  OUT(" * Implementation of class ");                                         \
  out_full_class_name(arg);                                                   \
  OUT("\n");                                                                  \
  OUT(" */\n");                                                               \
  OUT("\n");

#define EMIT_END_OF_IMPLEMENTATION_OF_CLASS_COMMENT                           \
  OUT("/*\n");                                                                \
  OUT(" * End of implementation of class ");                                  \
  out_full_class_name(arg);                                                   \
  OUT("\n");                                                                  \
  OUT(" */\n");                                                               \
  OUT("\n");

static void emit_Desctructor(arg_t *arg, const char* className);
static void emit_getDefaultTypeDescriptorPtr(arg_t *arg, const char* className);
static void emit_Copy(arg_t* arg, const char* className, const char* inheritFrom, void(*extra_copy_move)(arg_t*,int));
static void emit_Copy_for_indirect_choice(arg_t* arg, const char* className, const char* inheritFrom, void(*extra_copy_move)(arg_t*,int));
static void emit_Move(arg_t* arg, const char* className, const char* inheritFrom, void(*extra_copy_move)(arg_t*,int));
static void emit_Move_for_indirect_choice(arg_t* arg, const char* className, const char* inheritFrom, void(*extra_copy_move)(arg_t*,int));

static void 
emit_class_support_functions(arg_t *arg, const char* inheritFrom, void(*extra_copy_move)(arg_t*,int), 
                             void(*extra_implementation_functions)(arg_t*)) 
{
  MAKE_CLASS_NAME("emit_class_support_functions", arg->expr)
  
  EMIT_IMPLEMENTATION_OF_CLASS_COMMENT
          
  emit_Desctructor(arg, className);
  if (IS_USED_UNION_WITH_CHOICE(arg->expr)) {
    emit_Copy_for_indirect_choice(arg, className, inheritFrom, extra_copy_move);
    emit_Move_for_indirect_choice(arg, className, inheritFrom, extra_copy_move);
  } else {
    emit_Copy(arg, className, inheritFrom, extra_copy_move);
    emit_Move(arg, className, inheritFrom, extra_copy_move);
  }
  emit_getDefaultTypeDescriptorPtr(arg, className);
  emit_field_getters_and_setters_implementation(arg);
  if (extra_implementation_functions)
    extra_implementation_functions(arg);
  
  EMIT_END_OF_IMPLEMENTATION_OF_CLASS_COMMENT
  
  FREE_CLASS_NAME
}

static void out_asn_DEF(arg_t* arg, int isEmbed, int isPointer) {
  if (isPointer)
    OUT("&");
  OUT("asn_DEF_%s", MKID(arg->expr));
  if(isEmbed) 
    OUT("_%d", arg->expr->_type_unique_index);  
}

static void
emit_Desctructor(arg_t *arg, const char* className) {
  if (!IS_SECURE_POINTERS(arg) && !IS_USED_UNION_WITH_CHOICE(arg->expr)) {
    asn1p_expr_t *expr = arg->expr;
    asn1p_expr_t *v;
    out_full_class_name(arg);
    OUT("::~%s() noexcept {\n", className);
    INDENT(+1);
      TQ_FOR(v, &(expr->members), next) {
          if (IS_CLASS_FIELD(v)) {
              if (IS_PTR_MEMBER(v)) {
                OUT("delete this->%s;\n", MKID_safe(v));
              }
          }
        }
    INDENT(-1);
    OUT("}\n");
    OUT("\n");
  }
}

static void
emit_getDefaultTypeDescriptorPtr(arg_t *arg, const char* className) {
  OUT("asn_TYPE_descriptor_t* ");
  out_full_class_name(arg);
  OUT("::_getDefaultTypeDescriptorPtr() const {\n");
  INDENT(+1);
    OUT("return ");
    out_asn_DEF(arg, arg->embed, 1);
    OUT(";\n");
  INDENT(-1);
  OUT("}\n");
  OUT("\n");
}

static void
emit_Copy(arg_t* arg, const char* className, const char* inheritFrom, void(*extra_copy_move)(arg_t*,int))
{
  asn1p_expr_t *expr = arg->expr;
  asn1p_expr_t *v;
  emit_full_constructor_name_for_field(arg, expr);
  OUT("& ");
  out_full_class_name(arg);
  OUT("::operator =(const %s& other) {\n", className);
  INDENT(+1);
    TQ_FOR(v, &(expr->members), next) {
        if (IS_CLASS_FIELD(v)) {
            if (IS_PTR_MEMBER(v)) {
              OUT("if (other.%s) {\n", MKID_safe(v));
              INDENT(+1);
                OUT("if (this->%s)\n", MKID_safe(v));
                INDENTED(OUT("*this->%s = *other.%s;\n", MKID_safe(v), MKID_safe(v)););
                OUT("else\n");
                INDENT(+1);
                  if (IS_SECURE_POINTERS(arg)) {
                    OUT("this->%s.reset(new ", MKID_safe(v));
                    emit_constructor_name_for_field(arg, v);
                    OUT("(*other.%s));\n", MKID_safe(v));
                  } else {
                    OUT("this->%s = new ", MKID_safe(v));
                    emit_constructor_name_for_field(arg, v);
                    OUT("(*other.%s);\n", MKID_safe(v));
                  }
                INDENT(-1);
              INDENT(-1);
              OUT("} else");
              if (IS_SECURE_POINTERS(arg)) {
                OUT("\n");
                INDENTED(
                  OUT("this->%s.reset();\n", MKID_safe(v));
                );
              } else {
                OUT(" {\n");
                INDENT(+1);
                  OUT("delete this->%s;\n", MKID_safe(v));
                  OUT("this->%s = 0;\n", MKID_safe(v));
                INDENT(-1);
                OUT("}\n");
              }
            } else {
              OUT("this->%s = other.%s;\n", MKID_safe(v), MKID_safe(v));
            }
        }
      }
    if (extra_copy_move)
      extra_copy_move(arg, 0);
    OUT("%s::operator =(other);\n", inheritFrom);
    OUT("return *this;\n");
  INDENT(-1);
  OUT("}\n");
  OUT("\n");
}

static void
emit_Copy_for_indirect_choice(arg_t* arg, const char* className, const char* inheritFrom, void(*extra_copy_move)(arg_t*,int))
{
  asn1p_expr_t *expr = arg->expr;
  asn1p_expr_t *v;
  emit_full_constructor_name_for_field(arg, expr);
  OUT("& ");
  out_full_class_name(arg);
  OUT("::operator =(const %s& other) {\n", className);
  INDENT(+1);
    OUT("_freeData();\n");
    OUT("switch (other._present) {\n");
    OUT("case ");
    EMIT_CHOICE_PR_ENUM_NAME(expr);
    OUT("::");
    EMIT_CHOICE_PR_NOTHING_MEMBER_NAME;
    OUT(":\n");
    INDENTED(OUT("break;\n"););
    TQ_FOR(v, &(expr->members), next) {
        if (IS_CLASS_FIELD(v)) {
          OUT("case ");
          EMIT_CHOICE_PR_ENUM_NAME(expr);
          OUT("::");
          EMIT_CHOICE_PR_ENUM_MEMBER_NAME(v);
          OUT(":\n");
          INDENT(+1);
            //checking for null pointer is not needed because getters and 
            //setters ensure that if _present is specified, then 
            //the component will be present.
            OUT("this->_choice.%s = new ", MKID_safe(v));
            emit_constructor_name_for_field(arg, v);
            OUT("(*other._choice.%s);\n", MKID_safe(v));
            OUT("break;\n");
          INDENT(-1);
        }
      }
    OUT("default:\n");
    INDENTED(
      OUT("/* This shouldn't be executed */\n");
      OUT("break;\n");
    );
    OUT("} //End of switch\n");
    if (extra_copy_move)
      extra_copy_move(arg, 0);
    OUT("%s::operator =(other);\n", inheritFrom);
    OUT("return *this;\n");
  INDENT(-1);
  OUT("}\n");
  OUT("\n");
}

static void
emit_Move(arg_t* arg, const char* className, const char* inheritFrom, void(*extra_copy_move)(arg_t*,int))
{
  asn1p_expr_t *expr = arg->expr;
  asn1p_expr_t *v;
  emit_full_constructor_name_for_field(arg, expr);
  OUT("& ");
  out_full_class_name(arg);
  OUT("::operator =(%s&& other) noexcept {\n", className);
  INDENT(+1);
    TQ_FOR(v, &(expr->members), next) {
        if (IS_CLASS_FIELD(v)) {
          if (IS_PTR_MEMBER(v) && !IS_SECURE_POINTERS(arg)) {
            OUT("delete this->%s;\n", MKID_safe(v));
            OUT("this->%s = other.%s;\n", MKID_safe(v), MKID_safe(v));
            OUT("other.%s = 0;\n", MKID_safe(v));
          } else {
            OUT("this->%s = std::move(other.%s);\n", MKID_safe(v), MKID_safe(v));
          }
        }
      }
    if (extra_copy_move)
      extra_copy_move(arg, 1);
    OUT("%s::operator =(std::move(other));\n", inheritFrom);
    OUT("return *this;\n");
  INDENT(-1);
  OUT("}\n");
  OUT("\n");
}

static void
emit_Move_for_indirect_choice(arg_t* arg, const char* className, const char* inheritFrom, void(*extra_copy_move)(arg_t*,int))
{
  asn1p_expr_t *expr = arg->expr;
  asn1p_expr_t *v;
  emit_full_constructor_name_for_field(arg, expr);
  OUT("& ");
  out_full_class_name(arg);
  OUT("::operator =(%s&& other) noexcept {\n", className);
  INDENT(+1);
    OUT("_freeData();\n");
    TQ_FOR(v, &(expr->members), next) {
        if (IS_CLASS_FIELD(v)) {
          OUT("this->_choice = other._choice;\n");
          OUT("other._choice = {nullptr};\n");
          break;
        }
      }
    if (extra_copy_move)
      extra_copy_move(arg, 1);
    OUT("%s::operator =(std::move(other));\n", inheritFrom);
    OUT("return *this;\n");
  INDENT(-1);
  OUT("}\n");
  OUT("\n");
}

static void out_full_class_name_for_SEx_OF(arg_t* arg, const char* className) {
  out_full_class_name(arg);
//  if (out_full_class_name(arg))
//    OUT("::");
//  OUT("%s", className);
}

static void out_value_type_of_SEx_OF(arg_t* arg, int arg_for_value_type, arg_t* tmp) 
{
  if (!arg_for_value_type) {
    asn1p_expr_t *memb = TQ_FIRST(&arg->expr->members);
    emit_namespace_name(arg, arg->expr, memb);
    OUT("%s", asn1c_type_name(arg, memb,
        (memb->marker.flags & EM_UNRECURSE)
            ? TNF_RSAFE : TNF_CTYPE));
  } else {
    if (tmp->expr->expr_type & ASN_CONSTR_MASK) {
      out_class_name(tmp, tmp->expr);
    } else {
      emit_namespace_name(arg, arg->expr, tmp->expr);
      enum tnfmt tnfmt = TNF_CTYPE;
      OUT("%s", asn1c_type_name(tmp, tmp->expr, tnfmt));
    }
  }
}

static void
emit_SET_OF_erase_header(arg_t* arg) {
  OUT("/*\n");
  OUT(" * Delete the element from the set by its index (base 0).\n");
  OUT(" * This is a constant-time operation. The order of elements before the\n");
  OUT(" * deleted ones is guaranteed, the order of elements after the deleted\n");
  OUT(" * one is NOT guaranteed.\n");
  OUT(" */\n");
  OUT("void Erase(size_t index);\n");
}

static void
emit_SET_OF_erase_implementation(arg_t* arg, const char* className) {
  OUT("/*\n");
  OUT(" * Delete the element from the set by its index (base 0).\n");
  OUT(" * This is a constant-time operation. The order of elements before the\n");
  OUT(" * deleted ones is guaranteed, the order of elements after the deleted\n");
  OUT(" * one is NOT guaranteed.\n");
  OUT(" */\n");
  OUT("void ");
  out_full_class_name_for_SEx_OF(arg, className);
  OUT("::Erase(size_t index) {\n");
  INDENTED(
    OUT("if (index >= this->size())\n");
    INDENTED(OUT("return;\n"););
    OUT("if (index != this->size() - 1)\n");
    INDENTED(OUT("(*this)[index] = std::move((*this)[this->size() - 1]);\n"););
    OUT("this->pop_back();\n");
  );
  OUT("}\n");
  OUT("\n");
}

static void
emit_SEQUENCE_OF_erase_header(arg_t* arg) {
  OUT("/*\n");
  OUT(" * Delete the element from the set by its index (base 0).\n");
  OUT(" * This is NOT a constant-time operation.\n");
  OUT(" * The order of elements is preserved.\n");
  OUT(" */\n");
  OUT("void Erase(size_t index) {\n");
  INDENTED(
    OUT("if (index < this->size())\n");
    INDENTED(OUT("this->erase(this->begin() + index);\n"));
  );
  OUT("}\n");
}

#define ENABLE_STRDUP_IDENTIFIER 1

static void out_value_type_for_SEx_OF_class(arg_t* arg, int arg_for_value_type, arg_t* tmp) {
  OUT("std::vector<");
  out_value_type_of_SEx_OF(arg, arg_for_value_type, tmp);
  OUT(">");
}

static void
emit_SEx_OF_class(arg_t* arg, int arg_for_value_type, asn1p_expr_t *memb) {
  arg_t tmp;
  asn1p_expr_t tmp_memb;
  asn1p_expr_t *expr = arg->expr;
  int isEmbed = arg->embed;
  
  if (arg_for_value_type) {
    arg->embed++;
      tmp = *arg;
      tmp.expr = &tmp_memb;
      tmp_memb = *memb;
      tmp_memb.marker.flags &= ~EM_INDIRECT;
      tmp_memb._anonymous_type = expr->_anonymous_type + 1;
      tmp_memb.parent_expr = expr;
      if(tmp_memb.Identifier == 0) {
        tmp_memb.Identifier = "Member";
        if(ENABLE_STRDUP_IDENTIFIER)
        tmp_memb.Identifier = strdup(
          asn1c_make_identifier(0,
            expr, (char*)0, (char*)0));
        assert(tmp_memb.Identifier);
      }
      tmp.gen_inner_class_declaration = 1;
      tmp.default_cb(&tmp);
      if (!(INDENT_LEVEL))
        OUT("\n");
      tmp.gen_inner_class_declaration = 0;

    assert(arg->target->target == OT_TYPE_DECLS);
  }
  
  MAKE_CLASS_NAME("emit_class_support_functions_headers", arg->expr)
  OUT("class %s : public constr_SET_OF, public ", className);


  OUT("std::vector<");
  if (arg_for_value_type) {
    INDENT(+1);
    tmp.default_cb(&tmp);
    INDENT(-1);
    assert(arg->target->target == OT_TYPE_DECLS);
  } else {
    out_value_type_of_SEx_OF(arg, 0, &tmp);
  }
  if (arg_for_value_type)
    arg->embed--;
  asn1c_lang_CPP_type_SEx_OF_def(arg,
                          (arg->expr->expr_type == ASN_CONSTR_SEQUENCE_OF));
  if (arg_for_value_type)
    arg->embed++;

  OUT(">");
  
  OUT(" {\n");
  OUT("public:\n");
  INDENT(+1);
    OUT("%s() : constr_SET_OF(), ", className);
    out_value_type_for_SEx_OF_class(arg, arg_for_value_type, &tmp);
    OUT("() { }\n");
    OUT("virtual ~%s() noexcept { }\n", className);
    OUT("%s(const %s& other) : constr_SET_OF(other), ", className, className);
    out_value_type_for_SEx_OF_class(arg, arg_for_value_type, &tmp);
    OUT("(other) { }\n");
    OUT("%s(%s&& other) noexcept : constr_SET_OF(std::move(other)), ", className, className);
    out_value_type_for_SEx_OF_class(arg, arg_for_value_type, &tmp);
    OUT("(std::move(other)) {\n");
    INDENTED(
      OUT("other._Init();\n");
    );
    OUT("}\n");
    OUT("%s& operator =(const %s& other) {\n", className, className);
    INDENTED(
      out_value_type_for_SEx_OF_class(arg, arg_for_value_type, &tmp);
      OUT("::operator =(other);\n");
      OUT("constr_SET_OF::operator =(other);\n");
      OUT("return *this;\n");
    );
    OUT("}\n");
    OUT("%s& operator =(%s&& other) noexcept {\n", className, className);
    INDENTED(
      out_value_type_for_SEx_OF_class(arg, arg_for_value_type, &tmp);
      OUT("::operator =(std::move(other));\n");
      OUT("other._Init();\n");
      OUT("constr_SET_OF::operator =(std::move(other));\n");
      OUT("return *this;\n");
    );
    OUT("}\n");
    OUT("%s& operator =(const ", className);
    out_value_type_for_SEx_OF_class(arg, arg_for_value_type, &tmp);
    OUT("& newValue) {\n");
    INDENTED(
      out_value_type_for_SEx_OF_class(arg, arg_for_value_type, &tmp);
      OUT("::operator =(newValue);\n");
      OUT("return *this;\n");
    );
    OUT("}\n");
    OUT("%s& operator =(", className);
    out_value_type_for_SEx_OF_class(arg, arg_for_value_type, &tmp);
    OUT("&& newValue) {\n");
    INDENTED(
      out_value_type_for_SEx_OF_class(arg, arg_for_value_type, &tmp);
      OUT("::operator =(std::move(newValue));\n");
      OUT("return *this;\n");
    );
    OUT("}\n");
    OUT("void Clear() override { _Init(); constr_SET_OF::Clear(); }\n");
    if (arg->expr->expr_type == ASN_CONSTR_SEQUENCE_OF)
      emit_SEQUENCE_OF_erase_header(arg);
    else
      emit_SET_OF_erase_header(arg);
  INDENT(-1);
  OUT("private:\n");
  INDENTED(
    OUT("asn_TYPE_descriptor_t* _getDefaultTypeDescriptorPtr() const override;\n");
    OUT("void _Init() {\n");
    INDENTED(
      OUT("this->clear();\n");
    );
    OUT("}\n");
    OUT("AsnAbstractType* _emplaceBack();\n");
    OUT("size_t _size() const { return this->size(); }\n");
    OUT("AsnAbstractType* _getPtrOnMember(int itemIndex)  override;\n");
    OUT("const AsnAbstractType* _getPtrOnMember(int itemIndex) const override;\n");
  );
  OUT("}; //End of class %s\n", className);
  
  REDIR(OT_STAT_DEFS);
  
  EMIT_IMPLEMENTATION_OF_CLASS_COMMENT
          
  OUT("asn_TYPE_descriptor_t* ");
  out_full_class_name_for_SEx_OF(arg, className);
  OUT("::_getDefaultTypeDescriptorPtr() const {\n");
  INDENTED(
    OUT("return ");
    out_asn_DEF(arg, isEmbed, 1);
    OUT(";\n");
  );
  OUT("}\n");
  OUT("\n");          
  
  OUT("AsnAbstractType* ");
  out_full_class_name_for_SEx_OF(arg, className);
  OUT("::_emplaceBack() {\n");
    INDENTED(
      OUT("this->emplace_back();\n");
      OUT("return static_cast<AsnAbstractType*>(&this->back());\n");
    );
  OUT("}\n");
  OUT("\n");
  
  OUT("AsnAbstractType* ");
  out_full_class_name_for_SEx_OF(arg, className);
  OUT("::_getPtrOnMember(int itemIndex) {\n");
  INDENTED(OUT(" return &((*this)[itemIndex]);\n"););
  OUT("}\n");
  OUT("\n");
  
  OUT("const AsnAbstractType* ");
  out_full_class_name_for_SEx_OF(arg, className);
  OUT("::_getPtrOnMember(int itemIndex) const {\n");
  INDENTED(OUT(" return &((*this)[itemIndex]);\n"););
  OUT("}\n");
  OUT("\n");
  
  if (arg->expr->expr_type == ASN_CONSTR_SET_OF)
    emit_SET_OF_erase_implementation(arg, className);
  
  EMIT_END_OF_IMPLEMENTATION_OF_CLASS_COMMENT
  
  REDIR(OT_TYPE_DECLS);
  
  if (arg_for_value_type) {
    if(tmp_memb.Identifier != memb->Identifier)
        if(ENABLE_STRDUP_IDENTIFIER) free(tmp_memb.Identifier);
    arg->embed--;
  }
  
  FREE_CLASS_NAME
}

static void asn1c_lang_CPP_type_SET_extra_type_definition(arg_t *arg) {
  (void)arg;
//  asn1p_expr_t *expr = arg->expr;
//	asn1p_expr_t *v;
//	long mcount;
//	char *id = "NOTHING";
//  
//	OUT("/*\n");
//	OUT(" * Method of determining the components presence\n");
//	OUT(" */\n");
//	mcount = 0;
//	OUT("enum ");
//  out_class_name(arg, expr);
//  OUT("_PR {\n");
//	TQ_FOR(v, &(expr->members), next) {
//		if(v->expr_type == A1TC_EXTENSIBLE) continue;
//		INDENTED(
//			OUT("PR_");
//			id = MKID(v);
//			OUT("%s,\t/* Member %s is present */\n",
//				id, id)
//		);
//		mcount++;
//	}
//  INDENTED(OUT("PR__MAX = PR_%s,\n", id));
//	OUT("};\n"); 
}

static void asn1c_lang_CPP_type_SET_SEQUENCE_extra_function_definition(arg_t *arg) {
  MAKE_CLASS_NAME("asn1c_lang_CPP_type_SET_SEQUENCE_extra_function_definition", arg->expr);
  OUT("bool operator ==(const %s& other) const;\n", className);
  OUT("bool operator !=(const %s& other) const {\n", className);
  INDENTED(OUT("return !(this->operator == (other));\n"););
  OUT("}\n");
  asn1c_lang_CPP_type_SET_SEQUENCE_DEFAULT_extra_function_definition(arg);
  INDENT(-1);
  OUT("private:\n");
  INDENT(+1);
  emit_getPtrOnMember_header(arg);
  FREE_CLASS_NAME;
}

static void asn1c_lang_CPP_type_SET_SEQUENCE_operator_equal_implementation(arg_t* arg) {
  asn1p_expr_t *expr = arg->expr;
  asn1p_expr_t *v;
  int isFirstField = 1;
  MAKE_CLASS_NAME("asn1c_lang_CPP_type_SET_SEQUENCE_OPERATOR_EQUAL_implementation", expr);
  OUT("bool ");
  out_full_class_name(arg);
  OUT("::operator ==(const %s& other) const {\n", className);
  INDENT(+1);
  if (!HAS_MEMBERS(arg, expr))
    OUT("(void)other;\n");
  OUT("return ");
  TQ_FOR(v, &(expr->members), next) {
    if (IS_CLASS_FIELD(v)) {
      if (!isFirstField) {
        OUT(" &&\n");
        OUT("       ");
      } else {
        isFirstField = 0;
      }
      const char* identifier = MKID_safe(v);
      if (IS_PTR_MEMBER(v)) {
        OUT("((!this->%s && !other.%s) || "
                "(this->%s && other.%s && *this->%s == *other.%s))", 
                identifier, identifier, identifier, identifier, identifier, identifier);
      } else {
        OUT("this->%s == other.%s", identifier, identifier);
      }
    }
  }
  if (isFirstField)
    OUT("true");
  OUT(";\n");
  INDENT(-1);
  OUT("}\n");
  OUT("\n");
  FREE_CLASS_NAME;
}

static void asn1c_lang_CPP_type_SET_SEQUENCE_extra_function_implementation(arg_t *arg) {
  asn1c_lang_CPP_type_SET_SEQUENCE_operator_equal_implementation(arg);
  asn1c_lang_CPP_type_SET_SEQUENCE_DEFAULT_extra_function_implementation(arg);
  emit_getPtrOnMember_implementation(arg);
}

static void asn1c_lang_CPP_type_SET_extra_copy_move(arg_t *arg, int isMove) {
  (void)arg;
  (void)isMove;
  //deprecated code
//  if (isMove) {
//    OUT("/* bitmask move */\n");
//    OUT("constr_SET::operator =(std::move(other));\n");
//  } else {
//    OUT("/* bitmask copy */\n");
//    OUT("constr_SET::operator =(other);\n");
//  }
}

int
asn1c_lang_CPP_type_SET(arg_t *arg) {
  return GenerateClass(arg, "constr_SET", asn1c_lang_CPP_type_SET_def, 
                       asn1c_lang_CPP_type_SET_extra_type_definition,
                       0, 
                       asn1c_lang_CPP_type_SET_SEQUENCE_extra_function_definition);
}

static int
asn1c_lang_CPP_type_SET_def(arg_t *arg) {
	asn1p_expr_t *expr = arg->expr;
	asn1p_expr_t *v;
	int elements;
	tag2el_t *tag2el = NULL;
	int tag2el_count = 0;
	tag2el_t *tag2el_cxer = NULL;
	int tag2el_cxer_count = 0;
	int tags_count;
	int all_tags_count;
	enum tvm_compat tv_mode;
	char *p;

	/*
	 * Fetch every inner tag from the tag to elements map.
	 */
	if(_fill_tag2el_map(arg, &tag2el, &tag2el_count, -1, FTE_ALLTAGS)) {
		if(tag2el) free(tag2el);
		return -1;
	}
	if(_fill_tag2el_map(arg, &tag2el_cxer, &tag2el_cxer_count, -1, FTE_CANONICAL_XER)) {
		if(tag2el) free(tag2el);
		if(tag2el_cxer) free(tag2el_cxer);
		return -1;
	}
	if(tag2el_cxer_count == tag2el_count
	&& memcmp(tag2el, tag2el_cxer, tag2el_count) == 0) {
		free(tag2el_cxer);
		tag2el_cxer = 0;
	}

	GEN_INCLUDE_STD("constr_SET");
	if(!arg->embed)
		GEN_DECLARE(expr);	/* asn_DEF_xxx */

	REDIR(OT_STAT_DEFS);

	/*
	 * Print out the table according to which parsing is performed.
	 */
	if(expr_elements_count(arg, expr)) {
		int comp_mode = 0;	/* {root,ext=1,root,root,...} */

		OUT("static asn_TYPE_member_t asn_MBR_%s_%d[] = {\n",
			MKID(expr), expr->_type_unique_index);
	
		elements = 0;
		INDENTED(TQ_FOR(v, &(expr->members), next) {
			if(v->expr_type == A1TC_EXTENSIBLE) {
				if(comp_mode < 3) comp_mode++;
			} else {
				emit_member_table(arg, v, elements);
				elements++;
			}
		});
		OUT("};\n");
	} else {
		elements = 0;
	}

	/*
	 * Print out asn_DEF_<type>_[all_]tags[] vectors.
	 */
	tv_mode = emit_tags_vectors(arg, expr, &tags_count, &all_tags_count);

	/*
	 * Tags to elements map.
	 */
	emit_tag2member_map(arg, tag2el, tag2el_count, 0);
  ++arg->ignore_code;
	if(tag2el_cxer)
	emit_tag2member_map(arg, tag2el_cxer, tag2el_cxer_count, "_cxer");
  --arg->ignore_code;

	/*
	 * Emit a map of mandatory elements.
	 */
	OUT("static const uint8_t asn_MAP_%s_mmap_%d",
		MKID(expr), expr->_type_unique_index);
	p = MKID_safe(expr);
	OUT("[(%d + (8 * sizeof(unsigned int)) - 1) / 8]", elements);
	OUT(" = {\n");
	INDENTED(
	if(elements) {
		int el = 0;
		TQ_FOR(v, &(expr->members), next) {
			if(v->expr_type == A1TC_EXTENSIBLE) continue;
			if(el) {
				if((el % 8) == 0)
					OUT(",\n");
				else
					OUT(" | ");
			}
			OUT("(%d << %d)",
				(v->marker.flags & EM_OMITABLE) != EM_OMITABLE,
				7 - (el % 8));
			el++;
		}
	} else {
		OUT("0");
	}
	);
	OUT("\n");
	OUT("};\n");

	OUT("static asn_SET_specifics_t asn_SPC_%s_specs_%d = {\n",
		MKID(expr), expr->_type_unique_index);
	INDENTED(
//		OUT("sizeof(struct ");
//			out_name_chain(arg, ONC_avoid_keywords);
//		OUT("),\n");
//		OUT("offsetof(struct ");
//			out_name_chain(arg, ONC_avoid_keywords);
//		OUT(", _asn_ctx),\n");
//		OUT("offsetof(struct ");
//			out_name_chain(arg, ONC_avoid_keywords);
//		OUT(", _presence_map),\n");
		p = MKID(expr);
    if(tag2el_count) {
      OUT("asn_MAP_%s_tag2el_%d,\n", p, expr->_type_unique_index);
      OUT("%d,\t/* Count of tags in the map */\n", tag2el_count);
    } else {
      OUT("0,\t/* No top level tags */\n");
      OUT("0,\t/* No tags in the map */\n");
    }
    ++arg->ignore_code;
		if(tag2el_cxer)
			OUT("asn_MAP_%s_tag2el_cxer_%d,\n",
				p, expr->_type_unique_index);
		else
			OUT("asn_MAP_%s_tag2el_%d,\t/* Same as above */\n",
				p, expr->_type_unique_index);
		OUT("%d,\t/* Count of tags in the CXER map */\n",
			tag2el_cxer_count);
    --arg->ignore_code;
		OUT("%d,\t/* Whether extensible */\n",
			compute_extensions_start(expr) == -1 ? 0 : 1);
		OUT("(unsigned int *)asn_MAP_%s_mmap_%d\t/* Mandatory elements map */\n",
			p, expr->_type_unique_index);
	);
	OUT("};\n");

	/*
	 * Emit asn_DEF_xxx table.
	 */
	emit_type_DEF(arg, expr, tv_mode, tags_count, all_tags_count, elements,
			ETD_HAS_SPECIFICS);
  
  /*
   * Emit functions of the class
   */
  emit_class_support_functions(arg, "constr_SET", asn1c_lang_CPP_type_SET_extra_copy_move, 
        asn1c_lang_CPP_type_SET_SEQUENCE_extra_function_implementation);

	REDIR(OT_TYPE_DECLS);

	return 0;
} /* _SET_def() */


int
asn1c_lang_CPP_type_SEx_OF(arg_t *arg) {
	asn1p_expr_t *expr = arg->expr;
	asn1p_expr_t *memb = TQ_FIRST(&expr->members);
  
	DEPENDENCIES;
  
  if (IS_GENERATE_DECLARATION) {
    int arg_for_value_type = 0;
    if (!arg->embed) {
      OUT_NOINDENT("extern asn_TYPE_descriptor_t "
          "asn_DEF_%s;\n", MKID(expr));
    } 
    /*
     * README README
     * The implementation of the A_SET_OF() macro is already indirect.
     */
    memb->marker.flags |= EM_INDIRECT;
    

    if(memb->expr_type & ASN_CONSTR_MASK
    || ((memb->expr_type == ASN_BASIC_ENUMERATED
      || (0 /* -- prohibited by X.693:8.3.4 */
        && memb->expr_type == ASN_BASIC_INTEGER))
          && expr_elements_count(arg, memb))) 
    {
      arg_for_value_type = 1;
    }
    emit_SEx_OF_class(arg, arg_for_value_type, memb);
    assert(arg->target->target == OT_TYPE_DECLS);
    
//    if (isEmbed)
//      out_class_name(arg, expr);
//    else
//      OUT("%s", MKID_safe(expr));
    /*
     * SET OF/SEQUENCE OF definition
     */
    return 0;
  } else {
    if(arg->embed) {
      if (expr->marker.flags & EM_INDIRECT) {
        if(!expr->_anonymous_type && !IS_INDIRECT_CHOICE_TYPE(expr))
          out_pointer_head(arg); //prints "std::unique_ptr<" or nothing
      }
      OUT("class ");
      out_class_name(arg, expr);
      if(!expr->_anonymous_type) {
        if (expr->marker.flags & EM_INDIRECT)
          out_pointer_tail(arg, expr); //prints "*" or ">"
        OUT(" %s", MKID_safe(expr));
        ZERO_OUT_PTR_FIELD(arg, expr);
        if((expr->marker.flags & EM_OPTIONAL) == EM_OPTIONAL)
          OUT("\t/* OPTIONAL */");
      }
    }
    return 0;
  }

}

static int
asn1c_lang_CPP_type_SEx_OF_def(arg_t *arg, int seq_of) {
	asn1p_expr_t *expr = arg->expr;
	asn1p_expr_t *v;
	int tags_count;
	int all_tags_count;
	enum tvm_compat tv_mode;

	/*
	 * Print out the table according to which parsing is performed.
	 */
	if(seq_of) {
		GEN_INCLUDE_STD("constr_SEQUENCE_OF");
	} else {
		GEN_INCLUDE_STD("constr_SET_OF");
	}
	//if(!arg->embed)
	//	GEN_DECLARE(expr);	/* asn_DEF_xxx */
  
  if (expr->constraints && !(arg->flags & A1C_NO_CONSTRAINTS)) {
    REDIR(OT_CODE);
    emit_constraint_for_type(arg, expr);
  }

	REDIR(OT_STAT_DEFS);

	/*
	 * Print out the table according to which parsing is performed.
	 */
	OUT("static asn_TYPE_member_t asn_MBR_%s_%d[] = {\n",
		MKID(expr), expr->_type_unique_index);
	INDENT(+1);
		v = TQ_FIRST(&(expr->members));
		if(!v->Identifier) {
        if(ENABLE_STRDUP_IDENTIFIER) {
          v->Identifier = strdup(
            asn1c_make_identifier(0,
              expr, (char*)0, (char*)0));
        } else {
          v->Identifier = strdup("Member");
        }
			assert(v->Identifier);
		}
		v->_anonymous_type = 1;
		arg->embed++;
		emit_member_table(arg, v, 0);
		arg->embed--;
	INDENT(-1);
	OUT("};\n");

	/*
	 * Print out asn_DEF_<type>_[all_]tags[] vectors.
	 */
	tv_mode = emit_tags_vectors(arg, expr, &tags_count, &all_tags_count);

  ++arg->ignore_code;
	OUT("static asn_SET_OF_specifics_t asn_SPC_%s_specs_%d = {\n",
		MKID(expr), expr->_type_unique_index);
	INDENTED(
//		OUT("sizeof(struct ");
//			out_name_chain(arg, ONC_avoid_keywords);
//		OUT("),\n");
//		OUT("offsetof(struct ");
//			out_name_chain(arg, ONC_avoid_keywords);
//		OUT(", _asn_ctx),\n");
		{
		int as_xvl = expr_as_xmlvaluelist(arg, v);
		OUT("%d,\t/* XER encoding is %s */\n",
			as_xvl,
			as_xvl ? "XMLValueList" : "XMLDelimitedItemList");
		}
	);
	OUT("};\n");
  --arg->ignore_code;

	/*
	 * Emit asn_DEF_xxx table.
	 */
	emit_type_DEF(arg, expr, tv_mode, tags_count, all_tags_count, 1,
			ETD_HAS_SPECIFICS);
  
	REDIR(OT_TYPE_DECLS);

	return 0;
} /* _SEx_OF_def() */

static void asn1c_lang_CPP_type_CHOICE_extra_type_definition(arg_t *arg) {
  asn1p_expr_t *expr = arg->expr;
  asn1p_expr_t *v;
  OUT("enum ");
  //out_name_chain(arg, ONC_noflags);
  EMIT_CHOICE_PR_ENUM_NAME(expr);
	OUT(" {\n");
	INDENTED(
		int skipComma = 1;
//		out_name_chain(arg, ONC_noflags);
//    OUT("_");
    EMIT_CHOICE_PR_NOTHING_MEMBER_NAME;
		OUT(",\t/* No components present */\n");
		TQ_FOR(v, &(expr->members), next) {
			if(skipComma) skipComma = 0;
			else OUT(",\n");
			if(v->expr_type == A1TC_EXTENSIBLE) {
				OUT("/* Extensions may appear below */\n");
				skipComma = 1;
				continue;
			}
			//out_name_chain(arg, ONC_noflags);
      //OUT("_");
			EMIT_CHOICE_PR_ENUM_MEMBER_NAME(v);
		}
		OUT("\n");
	);
	OUT("};\n"); 
}

static void asn1c_lang_CPP_type_CHOICE_extra_field_definition(arg_t *arg) {
  EMIT_CHOICE_PR_ENUM_NAME(arg->expr);
	OUT(" _present = ");
  EMIT_CHOICE_PR_ENUM_NAME(arg->expr);
  OUT("::");
  EMIT_CHOICE_PR_NOTHING_MEMBER_NAME;
  OUT(";\n");
}

static void asn1c_lang_CPP_type_CHOICE_extra_function_definition(arg_t *arg) {
  MAKE_CLASS_NAME("asn1c_lang_CPP_type_SET_SEQUENCE_extra_function_definition", arg->expr);
  OUT("bool operator ==(const %s& other) const;\n", className);
  OUT("bool operator !=(const %s& other) const {\n", className);
  INDENTED(OUT("return !(this->operator == (other));\n"););
  OUT("}\n");
  
  EMIT_CHOICE_PR_ENUM_NAME(arg->expr);
  OUT(" FetchPresent() const { return this->_present; }\n");
  if (!IS_USED_UNION_WITH_CHOICE(arg->expr)) {
    OUT("void SetPresent(");
    EMIT_CHOICE_PR_ENUM_NAME(arg->expr);
    OUT(" present) { this->_present = present; }\n");
  }
  INDENT(-1);
  OUT("private:\n");
  INDENT(+1);
  if (IS_USED_UNION_WITH_CHOICE(arg->expr))
    OUT("void _freeData();\n");
  OUT("int _fetchPresent() const override { return static_cast<int>(this->_present); }\n");
  OUT("void _setPresent(int present) override { this->_present = static_cast<");
  EMIT_CHOICE_PR_ENUM_NAME(arg->expr);
  OUT(">(present); }\n");
  emit_getPtrOnMember_header(arg);
  FREE_CLASS_NAME;
}

static void asn1c_lang_CPP_type_CHOICE_operator_equal_implementation(arg_t* arg) {
  asn1p_expr_t *expr = arg->expr;
  asn1p_expr_t *v;
  MAKE_CLASS_NAME("asn1c_lang_CPP_type_CHOICE_operator_equal_implementation", expr);
  OUT("bool ");
  out_full_class_name(arg);
  OUT("::operator ==(const %s& other) const {\n", className);
  INDENT(+1);
  OUT("if (this->_present != other._present)\n");
  INDENTED(OUT("return false;\n"););
  OUT("switch (this->_present) {\n");
  OUT("case ");
  EMIT_CHOICE_PR_ENUM_NAME(expr);
  OUT("::");
  EMIT_CHOICE_PR_NOTHING_MEMBER_NAME;
  OUT(":\n");
  INDENTED(OUT("return true;\n"););
  TQ_FOR(v, &(expr->members), next) {
    if (IS_CLASS_FIELD(v)) {
      OUT("case ");
      EMIT_CHOICE_PR_ENUM_NAME(expr);
      OUT("::");
      EMIT_CHOICE_PR_ENUM_MEMBER_NAME(v);
      OUT(":\n");
      INDENT(+1);
      OUT("return ");
      const char* identifier = MKID_safe(v);
      if (IS_PTR_MEMBER(v)) {
        if (!IS_USED_UNION_WITH_CHOICE(expr)) {
          OUT("((!this->%s && !other.%s) || "
                  "(this->%s && other.%s && *this->%s == *other.%s))", 
                  identifier, identifier, identifier, identifier, identifier, identifier);
        } else {
          OUT("((!this->_choice.%s && !other._choice.%s) || "
                  "(this->_choice.%s && other._choice.%s && *this->_choice.%s == *other._choice.%s))", 
                  identifier, identifier, identifier, identifier, identifier, identifier);
        }
      } else {
        OUT("this->%s == other.%s", identifier, identifier);
      }
      OUT(";\n");
      INDENT(-1);
    }
  }
  OUT("default:\n");
  INDENTED(
    OUT("/* This shouldn't be executed */\n");
    OUT("return false;\n");
  );
  OUT("} //switch end\n");
  INDENT(-1);
  OUT("}\n");
  OUT("\n");
  FREE_CLASS_NAME;
}

static void asn1c_lang_CPP_type_CHOICE_freeData_implementation(arg_t* arg) {
  asn1p_expr_t *expr = arg->expr;
  asn1p_expr_t *v;
  OUT("void ");
  out_full_class_name(arg);
  OUT("::_freeData() {\n");
  INDENT(+1);
  OUT("switch (this->_present) {\n");
  OUT("case ");
  EMIT_CHOICE_PR_ENUM_NAME(expr);
  OUT("::");
  EMIT_CHOICE_PR_NOTHING_MEMBER_NAME;
  OUT(":\n");
  INDENTED(OUT("return;\n"););
  TQ_FOR(v, &(expr->members), next) {
    if (IS_CLASS_FIELD(v)) {
      OUT("case ");
      EMIT_CHOICE_PR_ENUM_NAME(expr);
      OUT("::");
      EMIT_CHOICE_PR_ENUM_MEMBER_NAME(v);
      OUT(":\n");
      INDENT(+1);
      const char* identifier = MKID_safe(v);
      OUT("delete this->_choice.%s;\n", identifier);
      OUT("this->_choice.%s = nullptr;\n", identifier);
      OUT("break;\n");
      INDENT(-1);
    }
  }
  OUT("default:\n");
  INDENTED(
    OUT("/* This shouldn't be executed */\n");
    OUT("return;\n");
  );
  OUT("} //switch end\n");
  OUT("this->_present = ");
  EMIT_CHOICE_PR_ENUM_NAME(expr);
  OUT("::");
  EMIT_CHOICE_PR_NOTHING_MEMBER_NAME;
  OUT(";\n");
  INDENT(-1);
  OUT("}\n");
  OUT("\n");
}

static void asn1c_lang_CPP_type_CHOICE_extra_function_implementation(arg_t* arg) {
  if (IS_USED_UNION_WITH_CHOICE(arg->expr))
    asn1c_lang_CPP_type_CHOICE_freeData_implementation(arg);
  asn1c_lang_CPP_type_CHOICE_operator_equal_implementation(arg);
  emit_getPtrOnMember_implementation(arg);
}

static void asn1c_lang_CPP_type_CHOICE_extra_copy_move(arg_t *arg, int isMove) {
  if (isMove) {
    OUT("_present = other._present;\n");
    OUT("other._present = ");
    EMIT_CHOICE_PR_ENUM_NAME(arg->expr);
    OUT("::");
    EMIT_CHOICE_PR_NOTHING_MEMBER_NAME;
    OUT(";\n");
  } else {
    OUT("_present = other._present;\n");
  }
}

int
asn1c_lang_CPP_type_CHOICE(arg_t *arg) {
  return GenerateClass(arg, "constr_CHOICE", 
                       asn1c_lang_CPP_type_CHOICE_def, 
                       asn1c_lang_CPP_type_CHOICE_extra_type_definition, 
                       asn1c_lang_CPP_type_CHOICE_extra_field_definition,
                       asn1c_lang_CPP_type_CHOICE_extra_function_definition);
}

static int
asn1c_lang_CPP_type_CHOICE_def(arg_t *arg) {
	asn1p_expr_t *expr = arg->expr;
	asn1p_expr_t *v;
	int elements;	/* Number of elements */
	tag2el_t *tag2el = NULL;
	int tag2el_count = 0;
	int tags_count;
	int all_tags_count;
	enum tvm_compat tv_mode;
	int *cmap = 0;

	/*
	 * Fetch every inner tag from the tag to elements map.
	 */
	if(_fill_tag2el_map(arg, &tag2el, &tag2el_count, -1, FTE_ALLTAGS)) {
		if(tag2el) free(tag2el);
		return -1;
	}

	GEN_INCLUDE_STD("constr_CHOICE");
	if(!arg->embed)
		GEN_DECLARE(expr);	/* asn_DEF_xxx */

	REDIR(OT_STAT_DEFS);

	/*
	 * Print out the table according to which parsing is performed.
	 */
	if(expr_elements_count(arg, expr)) {

		OUT("static asn_TYPE_member_t asn_MBR_%s_%d[] = {\n",
			MKID(expr), expr->_type_unique_index);

		elements = 0;
		INDENTED(TQ_FOR(v, &(expr->members), next) {
			if(v->expr_type == A1TC_EXTENSIBLE)
				continue;
			emit_member_table(arg, v, elements);
			elements++;
		});
		OUT("};\n");
	} else {
		elements = 0;
	}

	/* Create a canonical elements map */
	if(elements && (arg->flags & A1C_GEN_PER)) {
		int i;
		cmap = compute_canonical_members_order(arg, elements);
		if(cmap) {
			OUT("static const int asn_MAP_%s_cmap_%d[] = {",
				MKID(expr),
				expr->_type_unique_index);
			for(i = 0; i < elements; i++) {
				if(i) OUT(",");
				OUT(" %d", cmap[i]);
			}
			OUT(" };\n");
			free(cmap);
		}
	}

	if(arg->embed) {
		/*
		 * Our parent structure has already taken this into account.
		 */
		tv_mode = _TVM_SAME;
		tags_count = all_tags_count = 0;
	} else {
		tv_mode = emit_tags_vectors(arg, expr,
			&tags_count, &all_tags_count);
	}

	/*
	 * Tags to elements map.
	 */
	emit_tag2member_map(arg, tag2el, tag2el_count, 0);

	OUT("static asn_CHOICE_specifics_t asn_SPC_%s_specs_%d = {\n",
		MKID(expr), expr->_type_unique_index);
	INDENTED(
//		OUT("sizeof(struct ");
//			out_name_chain(arg, ONC_avoid_keywords);
//		OUT("),\n");
//		OUT("offsetof(struct ");
//			out_name_chain(arg, ONC_avoid_keywords);
//		OUT(", _asn_ctx),\n");
//		OUT("offsetof(struct ");
//			out_name_chain(arg, ONC_avoid_keywords);
//		OUT(", present),\n");
//		OUT("sizeof(((struct ");
//			out_name_chain(arg, ONC_avoid_keywords);
//		OUT(" *)0)->present),\n");
    if(tag2el_count) {      
      OUT("asn_MAP_%s_tag2el_%d,\n",
        MKID(expr), expr->_type_unique_index);
      OUT("%d,\t/* Count of tags in the map */\n", tag2el_count);
    } else {
      OUT("0,\t/* No top level tags */\n");
      OUT("0,\t/* No tags in the map */\n");
    }
    ++arg->ignore_code;
		if(C99_MODE) OUT(".canonical_order = ");
		if(cmap) OUT("asn_MAP_%s_cmap_%d,\t/* Canonically sorted */\n",
			MKID(expr), expr->_type_unique_index);
		else OUT("0,\n");
    --arg->ignore_code;
		if(C99_MODE) OUT(".ext_start = ");
		OUT("%d\t/* Extensions start */\n",
			compute_extensions_start(expr));
	);
	OUT("};\n");

	/*
	 * Emit asn_DEF_xxx table.
	 */
	emit_type_DEF(arg, expr, tv_mode, tags_count, all_tags_count, elements,
			ETD_HAS_SPECIFICS);
  
  /*
   * Emit functions of the class
   */
  emit_class_support_functions(arg, "constr_CHOICE", asn1c_lang_CPP_type_CHOICE_extra_copy_move, 
                              asn1c_lang_CPP_type_CHOICE_extra_function_implementation);

	REDIR(OT_TYPE_DECLS);

	return 0;
} /* _CHOICE_def() */

int
asn1c_lang_CPP_type_REFERENCE(arg_t *arg) {
	asn1p_ref_t *ref;

	ref = arg->expr->reference;
	if(ref->components[ref->comp_count-1].name[0] == '&') {
		asn1p_expr_t *extract;
		arg_t tmp;
		int ret;

		extract = asn1f_class_access_ex(arg->asn, arg->expr->module,
			arg->expr, arg->expr->rhs_pspecs, ref);
		if(extract == NULL)
			return -1;

		extract = asn1p_expr_clone(extract, 0);
		if(extract) {
			if(extract->Identifier)
				free(extract->Identifier);
			extract->Identifier = strdup(arg->expr->Identifier);
			if(extract->Identifier == NULL) {
				asn1p_expr_free(extract);
				return -1;
			}
      //it seems that we should also copy expr->marker.flags. 
      //Otherwise the OPTIONAL field will not be generated as pointer.
      //The problem arose on the type:
      //    PrivateExtension ::= SEQUENCE {
      //        extId		MAP-EXTENSION.&extensionId ({ExtensionSet}),
      //        extType		MAP-EXTENSION.&ExtensionType ({ExtensionSet}{@extId})	OPTIONAL
      //    }
      //This type is from MAP protocol.
      extract->marker.flags = arg->expr->marker.flags;
      //we also need to copy pointer to parent expr.
      //Otherwise member in union of CHOICE will not have 
      //correct pointer (smart and insecure).
      extract->parent_expr = arg->expr->parent_expr;
		} else {
			return -1;
		}

		tmp = *arg;
		tmp.asn = arg->asn;
		tmp.expr = extract;

		ret = arg->default_cb(&tmp);

		asn1p_expr_free(extract);

		return ret;
	}


	return asn1c_lang_CPP_type_SIMPLE_TYPE(arg);
}

static void emit_constraint_for_type(arg_t* arg, asn1p_expr_t *expr) {
  char* p = MKID(expr);
  OUT("static ");
  OUT("int\n");
  OUT("%s", p);
  if(HIDE_INNER_DEFS) OUT("_%d", expr->_type_unique_index);
  OUT("_constraint(asn_TYPE_descriptor_t *td, const void *sptr,\n");
  INDENT(+1);
  OUT("\t\tasn_app_constraint_failed_f *ctfailcb, void *app_key) {");
  OUT("\n");
  DEBUG("expr constraint checking code for %s", p);
  if(asn1c_emit_constraint_checking_code(arg) == 1) {
    OUT("/* Replace with underlying type checker */\n");
    if (ASN_CONSTR_SET_OF == expr->expr_type || ASN_CONSTR_SEQUENCE_OF == expr->expr_type) {
      OUT("return %s_constraint(td, sptr, ctfailcb, app_key);\n", 
              expr->expr_type == ASN_CONSTR_SEQUENCE_OF ? "SEQUENCE_OF" : "SET_OF");
    } else {
      OUT("td->check_constraints = ");
      emit_namespace_name(arg, expr, expr);
      OUT("asn_DEF_%s.check_constraints;\n", asn1c_type_name(arg, expr, TNF_SAFE));
      OUT("return td->check_constraints"
        "(td, sptr, ctfailcb, app_key);\n");
    }
  }
  INDENT(-1);
  OUT("}\n");
  OUT("\n");
}

int
asn1c_lang_CPP_type_SIMPLE_TYPE(arg_t *arg) {
	asn1p_expr_t *expr = arg->expr;
	int tags_count;
	int all_tags_count;
	enum tvm_compat tv_mode;
	enum etd_spec etd_spec;
	char *p;

	if(arg->embed) {
		enum tnfmt tnfmt = TNF_CTYPE;

		/*
		 * If this is an optional compound type,
		 * refer it using "struct X" convention,
		 * as it may recursively include the current structure.
		 */
		if(expr->marker.flags & (EM_INDIRECT | EM_UNRECURSE)) {
			if(terminal_structable(arg, expr)) {
				REDIR(OT_FWD_DECLS);
        emit_class_dependency(arg, arg->expr);
			}
		}

    REDIR(OT_TYPE_DECLS);

    if (expr->marker.flags&EM_INDIRECT) {
      if(!expr->_anonymous_type && !IS_INDIRECT_CHOICE_TYPE(expr))
        out_pointer_head(arg); //prints "std::unique_ptr<" or nothing
    }
    emit_namespace_name(arg, expr->parent_expr, expr);
		OUT("%s", asn1c_type_name(arg, arg->expr, tnfmt));
		if(!expr->_anonymous_type) {
      if (expr->marker.flags&EM_INDIRECT)
        out_pointer_tail(arg, expr); //printf "*" or ">"
      OUT("\t");
			OUT("%s", MKID_safe(expr));
      ZERO_OUT_PTR_FIELD(arg, expr);
			if((expr->marker.flags & (EM_DEFAULT & ~EM_INDIRECT))
					== (EM_DEFAULT & ~EM_INDIRECT)) 
      {
        const char* printableValue = asn1f_printable_value(expr->marker.default_value);
        if (safe_string((const uint8_t*)printableValue, strlen(printableValue)))
          OUT("\t/* DEFAULT %s */", printableValue);
        else
          OUT("\t/* DEFAULT */");
      } else if((expr->marker.flags & EM_OPTIONAL)
					== EM_OPTIONAL)
				OUT("\t/* OPTIONAL */");
		}

	} else {
    if (!IS_SINGLE_UNIT(arg) || (!(expr->expr_type & ASN_CONSTR_MASK) && expr->expr_type > ASN_CONSTR_MASK)) {
      GEN_INCLUDE(asn1c_type_name(arg, expr, TNF_INCLUDE));
    }

		REDIR(OT_TYPE_DECLS);
    //OUT("class %s;\n", MKID(expr));
    
    //we will generate class for Reference in implementation part since 
    //&asn_DEF_ must be defined first
	}

	if((expr->expr_type == ASN_BASIC_ENUMERATED)
	|| (0 /* -- prohibited by X.693:8.3.4 */
		&& expr->expr_type == ASN_BASIC_INTEGER
		&& expr_elements_count(arg, expr))
	|| (expr->expr_type == ASN_BASIC_INTEGER
		&& asn1c_type_fits_long(arg, expr) == FL_FITS_UNSIGN)
	)
		etd_spec = ETD_HAS_SPECIFICS;
	else
		etd_spec = ETD_NO_SPECIFICS;

	/*
	 * If this type just blindly refers the other type, alias it.
	 * 	Type1 ::= Type2
	 */
	if(arg->embed && etd_spec == ETD_NO_SPECIFICS) {
		REDIR(OT_TYPE_DECLS);
		return 0;
	}
	if((!expr->constraints || (arg->flags & A1C_NO_CONSTRAINTS))
	&& (arg->embed || expr->tag.tag_class == TC_NOCLASS)
	&& etd_spec == ETD_NO_SPECIFICS
	&& 0	/* This shortcut is incompatible with XER */
	) {
		char *type_name;
		REDIR(OT_FUNC_DECLS);
		type_name = asn1c_type_name(arg, expr, TNF_SAFE);
		OUT("/* This type is equivalent to %s */\n", type_name);
		if(HIDE_INNER_DEFS) OUT("/* ");
		OUT("#define\tasn_DEF_%s\t", MKID(expr));
		type_name = asn1c_type_name(arg, expr, TNF_SAFE);
		OUT("asn_DEF_%s", type_name);
		if(HIDE_INNER_DEFS)
			OUT("\t// (Use -fall-defs-global to expose) */");
		OUT("\n");
		REDIR(OT_CODE);
		OUT("/* This type is equivalent to %s */\n", type_name);
		OUT("\n");
		REDIR(OT_TYPE_DECLS);
		return 0;
	}

	REDIR(OT_STAT_DEFS);

	/*
	 * Print out asn_DEF_<type>_[all_]tags[] vectors.
	 */
	tv_mode = emit_tags_vectors(arg, expr, &tags_count, &all_tags_count);
	DEBUG("emit tag vectors for %s %d, %d, %d", expr->Identifier,
		tv_mode, tags_count, all_tags_count);

	emit_type_DEF(arg, expr, tv_mode, tags_count, all_tags_count,
		0, etd_spec);

	REDIR(OT_CODE);

	/*
	 * Emit suicidal functions.
	 */

	/*
	 * This function replaces certain fields from the definition
	 * of a type with the corresponding fields from the basic type
	 * (from which the current type is inherited).
	 */
	OUT("/*\n");
	OUT(" * This type is implemented using %s,\n",
		asn1c_type_name(arg, expr, TNF_SAFE));
	OUT(" * so here we adjust the DEF accordingly.\n");
	OUT(" */\n");
	OUT("static void\n");
	OUT("%s_%d_inherit_TYPE_descriptor(asn_TYPE_descriptor_t *td) {\n",
		MKID(expr), expr->_type_unique_index);
	INDENT(+1);
  {
    asn1p_expr_t *terminal = asn1f_find_terminal_type_ex(arg->asn, expr);
    char *temp = asn1c_type_name(arg, expr, TNF_SAFE);
    char *type_name = malloc(strlen(temp) + 1);
    if (!type_name) {
      FATAL("Unable to allocate memory for type_memory in asn1c_lang_CPP_type_SIMPLE_TYPE");
    } else {
      strcpy(type_name, temp);
      OUT("td->print_struct   = ");
      emit_namespace_name(arg, expr, expr);
      OUT("asn_DEF_%s.print_struct;\n",   type_name);
      //This line is buggy for SET OF/SEQUENCE OF types. 
      //This inheritance will happen in constraint function if it is needed
      //OUT("td->check_constraints = asn_DEF_%s.check_constraints;\n", type_name);
      OUT("td->ber_decoder    = ");
      emit_namespace_name(arg, expr, expr);
      OUT("asn_DEF_%s.ber_decoder;\n",    type_name);
      
      OUT("td->der_encoder    = ");
      emit_namespace_name(arg, expr, expr);
      OUT("asn_DEF_%s.der_encoder;\n",    type_name);
      
      ++arg->ignore_code;
      OUT("//"); OUT("td->xer_decoder    = ");
                 emit_namespace_name(arg, expr, expr);
                 OUT("asn_DEF_%s.xer_decoder;\n",    type_name);
                 
      OUT("//"); OUT("td->xer_encoder    = ");
                 emit_namespace_name(arg, expr, expr);
                 OUT("asn_DEF_%s.xer_encoder;\n",    type_name);
                 
      OUT("//"); OUT("td->uper_decoder   = ");
                 emit_namespace_name(arg, expr, expr);
                 OUT("asn_DEF_%s.uper_decoder;\n",   type_name);
                 
      OUT("//"); OUT("td->uper_encoder   = ");
                 emit_namespace_name(arg, expr, expr);
                 OUT("asn_DEF_%s.uper_encoder;\n",   type_name);
      if(!terminal && !tags_count) {
        OUT("/* The next four lines are here because of -fknown-extern-type */\n");
        OUT("td->tags           = ");
        emit_namespace_name(arg, expr, expr);
        OUT("asn_DEF_%s.tags;\n",         type_name);
        
        OUT("td->tags_count     = ");
        emit_namespace_name(arg, expr, expr);
        OUT("asn_DEF_%s.tags_count;\n",   type_name);
        
        OUT("td->all_tags       = ");
        emit_namespace_name(arg, expr, expr);
        OUT("asn_DEF_%s.all_tags;\n",     type_name);
        
        OUT("td->all_tags_count = ");
        emit_namespace_name(arg, expr, expr);
        OUT("asn_DEF_%s.all_tags_count;\n",type_name);
        OUT("/* End of these lines */\n");
      }
      OUT("//"); OUT("if(!td->per_constraints)\n");
      OUT("//"); OUT("\ttd->per_constraints = ");
                 emit_namespace_name(arg, expr, expr);
                 OUT("asn_DEF_%s.per_constraints;\n", type_name);
      --arg->ignore_code;
      OUT("td->elements       = ");
      emit_namespace_name(arg, expr, expr);
      OUT("asn_DEF_%s.elements;\n",       type_name);
      
      OUT("td->elements_count = ");
      emit_namespace_name(arg, expr, expr);
      OUT("asn_DEF_%s.elements_count;\n", type_name);
      
      if(etd_spec != ETD_NO_SPECIFICS) {
        INDENT(-1);
        OUT("     /* ");
      }
      OUT("td->specifics      = ");
      emit_namespace_name(arg, expr, expr);
      OUT("asn_DEF_%s.specifics;",        type_name);
      if(etd_spec == ETD_NO_SPECIFICS) {
        INDENT(-1);
        OUT("\n");
      } else {
        OUT("\t// Defined explicitly */\n");
      }
    free(type_name);
    }
  }
	OUT("}\n");
	OUT("\n");
  
  /*
	 * Constraint checking.
	 */
	if(!(arg->flags & A1C_NO_CONSTRAINTS)) {
		emit_constraint_for_type(arg, expr);
	}

  
//	p = MKID(expr);
//	if(HIDE_INNER_DEFS) OUT("static ");
//	OUT("void\n");
//	OUT("%s", p);
//	if(HIDE_INNER_DEFS) OUT("_%d", expr->_type_unique_index);
//	OUT("_free(asn_TYPE_descriptor_t *td,\n");
//	INDENTED(
//	OUT("\tvoid *struct_ptr, int contents_only) {\n");
//	OUT("%s_%d_inherit_TYPE_descriptor(td);\n",
//		p, expr->_type_unique_index);
//	OUT("td->free_struct(td, struct_ptr, contents_only);\n");
//	);
//	OUT("}\n");
//	OUT("\n");

	p = MKID(expr);
	OUT("static ");
	OUT("int\n");
	OUT("%s", p);
	if(HIDE_INNER_DEFS) OUT("_%d", expr->_type_unique_index);
	OUT("_print(asn_TYPE_descriptor_t *td, const void *struct_ptr,\n");
	INDENTED(
	OUT("\tint ilevel, asn_app_consume_bytes_f *cb, void *app_key) {\n");
	OUT("%s_%d_inherit_TYPE_descriptor(td);\n",
		p, expr->_type_unique_index);
	OUT("return td->print_struct(td, struct_ptr, ilevel, cb, app_key);\n");
	);
	OUT("}\n");
	OUT("\n");

	p = MKID(expr);
	OUT("static ");
	OUT("asn_dec_rval_t\n");
	OUT("%s", p);
	if(HIDE_INNER_DEFS) OUT("_%d", expr->_type_unique_index);
	OUT("_decode_ber(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,\n");
	INDENTED(
	OUT("\tvoid **structure, const void *bufptr, size_t size, int tag_mode) {\n");
	OUT("%s_%d_inherit_TYPE_descriptor(td);\n",
		p, expr->_type_unique_index);
	OUT("return td->ber_decoder(opt_codec_ctx, td, structure, bufptr, size, tag_mode);\n");
	);
	OUT("}\n");
	OUT("\n");

  
	p = MKID(expr);
	OUT("static ");
	OUT("asn_enc_rval_t\n");
	OUT("%s", p);
	if(HIDE_INNER_DEFS) OUT("_%d", expr->_type_unique_index);
	OUT("_encode_der(asn_TYPE_descriptor_t *td,\n");
	INDENTED(
	OUT("\tvoid *structure, int tag_mode, ber_tlv_tag_t tag,\n");
	OUT("\tasn_app_consume_bytes_f *cb, void *app_key) {\n");
	OUT("%s_%d_inherit_TYPE_descriptor(td);\n",
		p, expr->_type_unique_index);
	OUT("return td->der_encoder(td, structure, tag_mode, tag, cb, app_key);\n");
	);
	OUT("}\n");
	OUT("\n");

  ++arg->ignore_code;
	p = MKID(expr);
	OUT("static ");
	OUT("asn_dec_rval_t\n");
	OUT("%s", p);
	if(HIDE_INNER_DEFS) OUT("_%d", expr->_type_unique_index);
	OUT("_decode_xer(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,\n");
	INDENTED(
	OUT("\tvoid **structure, const char *opt_mname, const void *bufptr, size_t size) {\n");
	OUT("%s_%d_inherit_TYPE_descriptor(td);\n",
		p, expr->_type_unique_index);
	OUT("return td->xer_decoder(opt_codec_ctx, td, structure, opt_mname, bufptr, size);\n");
	);
	OUT("}\n");
	OUT("\n");

	p = MKID(expr);
	OUT("static ");
	OUT("asn_enc_rval_t\n");
	OUT("%s", p);
	if(HIDE_INNER_DEFS) OUT("_%d", expr->_type_unique_index);
	OUT("_encode_xer(asn_TYPE_descriptor_t *td, void *structure,\n");
	INDENTED(
	OUT("\tint ilevel, enum xer_encoder_flags_e flags,\n");
	OUT("\tasn_app_consume_bytes_f *cb, void *app_key) {\n");
	OUT("%s_%d_inherit_TYPE_descriptor(td);\n",
		p, expr->_type_unique_index);
	OUT("return td->xer_encoder(td, structure, ilevel, flags, cb, app_key);\n");
	);
	OUT("}\n");
	OUT("\n");

  if(arg->flags & A1C_GEN_PER) {
	p = MKID(expr);

	OUT("static ");
	OUT("asn_dec_rval_t\n");
	OUT("%s", p);
	if(HIDE_INNER_DEFS) OUT("_%d", expr->_type_unique_index);
	OUT("_decode_uper(asn_codec_ctx_t *opt_codec_ctx, asn_TYPE_descriptor_t *td,\n");
	INDENTED(
	OUT("\tasn_per_constraints_t *constraints, void **structure, asn_per_data_t *per_data) {\n");
	OUT("%s_%d_inherit_TYPE_descriptor(td);\n",
		p, expr->_type_unique_index);
	OUT("return td->uper_decoder(opt_codec_ctx, td, constraints, structure, per_data);\n");
	);
	OUT("}\n");
	OUT("\n");

	p = MKID(expr);
	OUT("static ");
	OUT("asn_enc_rval_t\n");
	OUT("%s", p);
	if(HIDE_INNER_DEFS) OUT("_%d", expr->_type_unique_index);
	OUT("_encode_uper(asn_TYPE_descriptor_t *td,\n");
	INDENTED(
	OUT("\tasn_per_constraints_t *constraints,\n");
	OUT("\tvoid *structure, asn_per_outp_t *per_out) {\n");
	OUT("%s_%d_inherit_TYPE_descriptor(td);\n",
		p, expr->_type_unique_index);
	OUT("return td->uper_encoder(td, constraints, structure, per_out);\n");
	);
	OUT("}\n");
	OUT("\n");
  }
  --arg->ignore_code;

	REDIR(OT_FUNC_DECLS);

	p = MKID(expr);
	if(HIDE_INNER_DEFS) {
//		OUT("/* extern asn_TYPE_descriptor_t asn_DEF_%s_%d;"
//			"\t// (Use -fall-defs-global to expose) */\n",
//			p, expr->_type_unique_index);
	} else {
		OUT("extern asn_TYPE_descriptor_t asn_DEF_%s;\n", p);
    ++arg->ignore_code;
		//OUT("asn_struct_free_f %s_free;\n", p);
		OUT("asn_struct_print_f %s_print;\n", p);
		OUT("asn_constr_check_f %s_constraint;\n", p);
		OUT("ber_type_decoder_f %s_decode_ber;\n", p);
		OUT("der_type_encoder_f %s_encode_der;\n", p);
    
		OUT("xer_type_decoder_f %s_decode_xer;\n", p);
		OUT("xer_type_encoder_f %s_encode_xer;\n", p);
		if(arg->flags & A1C_GEN_PER) {
		OUT("per_type_decoder_f %s_decode_uper;\n", p);
		OUT("per_type_encoder_f %s_encode_uper;\n", p);
		}
    --arg->ignore_code;
	}
  
  if (!arg->embed) {
    OUT("\n");  
    OUT("\n");
    emit_ref_class(arg);
  }

	REDIR(OT_TYPE_DECLS);

	return 0;
}

static void emit_getPtrOnMember_header(arg_t* arg) {
  OUT("AsnAbstractType* _getPtrOnMember(int itemIndex, bool createNew) override;\n");
  OUT("const AsnAbstractType* _getPtrOnMember(int itemIndex) const override;\n");
}

static void
emit_getPtrOnMember_implementation_with_switch(arg_t* arg) {
  {
    asn1p_expr_t *expr = arg->expr;
    int counter = 0;
    asn1p_expr_t *v;
    int wasPtrField = 0;
    OUT("AsnAbstractType* ");
    out_full_class_name(arg);
    OUT("::_getPtrOnMember(int itemIndex, bool createNew) ");
    OUT("{\n");
    INDENT(+1);
      if (IS_USED_UNION_WITH_CHOICE(expr)) {
        INDENT(-1);
        OUT("#ifdef DEBUG\n");
        INDENT(+1);
        OUT("if (this->_present != static_cast<");
        EMIT_CHOICE_PR_ENUM_NAME(expr);
        OUT(">(itemIndex + 1))\n");
        INDENTED(
          OUT("throw std::runtime_error(\"Invalid item index \" + std::to_string(itemIndex) + \" in ");
          out_full_class_name(arg);
          OUT("::_getPtrOnField\");\n");
        );
        INDENT(-1);
        OUT("#endif\n");
        INDENT(+1);
      }
      OUT("switch (itemIndex) {\n");
      TQ_FOR(v, &(expr->members), next) {
        if (IS_CLASS_FIELD(v)) {
          char* identifier = 0; 
          {
            char* identifierTemp = MKID_safe(v);
            identifier = malloc(strlen(identifierTemp) + 1);
            if (!identifier) {
              FATAL("Unable to allocate memory for identifier");
              return;
            }
            strcpy(identifier, identifierTemp);
          }
          OUT("case %d:\n", counter);
          INDENTED(
            if (IS_PTR_MEMBER(v)) {
              wasPtrField = 1;
              if (IS_USED_UNION_WITH_CHOICE(expr)) {
                OUT("if (!this->_choice.%s && createNew)\n", identifier);
                INDENTED(
                  OUT("this->_choice.%s = new ", identifier);
                  emit_constructor_name_for_field(arg, v);
                  OUT("();\n");
                );
                OUT("return this->_choice.%s;\n", identifier);
              } else {
                OUT("if (!this->%s && createNew)\n", identifier);
                INDENT(+1);
                  if (IS_SECURE_POINTERS(arg)) {
                    OUT("this->%s.reset(new ", identifier);
                    emit_constructor_name_for_field(arg, v);
                    OUT("());\n");
                  } else {
                    OUT("this->%s = new ", identifier);
                    emit_constructor_name_for_field(arg, v);
                    OUT("();\n");
                  }
                INDENT(-1);
                OUT("return this->%s", identifier);
                if (IS_SECURE_POINTERS(arg))
                  OUT(".get()");
                OUT(";\n");
              }
            } else {
              OUT("return &this->%s;\n", identifier);
            }
          );
          ++counter;
          free(identifier);
        }
      }
      OUT("default:\n");
      INDENTED(
        OUT("/* This shouldn't be executed */\n");
        OUT("throw std::runtime_error(\"Invalid item index \" + std::to_string(itemIndex) + \" in ");
        out_full_class_name(arg);
        OUT("::_getPtrOnField\");\n");
      );
      OUT("} //switch end\n");
      if (!wasPtrField)
        OUT("(void)createNew;\n");
    INDENT(-1);
    OUT("}\n");
    OUT("\n");
  }
  
  {
    asn1p_expr_t *expr = arg->expr;
    int counter = 0;
    asn1p_expr_t *v;
    OUT("const AsnAbstractType* ");
    out_full_class_name(arg);
    OUT("::_getPtrOnMember(int itemIndex) const ");
    OUT("{\n");
    INDENT(+1);
      if (IS_USED_UNION_WITH_CHOICE(expr)) {
        INDENT(-1);
        OUT("#ifdef DEBUG\n");
        INDENT(+1);
        OUT("if (this->_present != static_cast<");
        EMIT_CHOICE_PR_ENUM_NAME(expr);
        OUT(">(itemIndex + 1))\n");
        INDENTED(
          OUT("throw std::runtime_error(\"Invalid item index \" + std::to_string(itemIndex) + \" in ");
          out_full_class_name(arg);
          OUT("::_getPtrOnField\");\n");
        );
        INDENT(-1);
        OUT("#endif\n");
        INDENT(+1);
      }
      OUT("switch (itemIndex) {\n");
      TQ_FOR(v, &(expr->members), next) {
        if (IS_CLASS_FIELD(v)) {
          char* identifier = 0; 
          {
            char* identifierTemp = MKID_safe(v);
            identifier = malloc(strlen(identifierTemp) + 1);
            if (!identifier) {
              FATAL("Unable to allocate memory for identifier");
              return;
            }
            strcpy(identifier, identifierTemp);
          }
          OUT("case %d:\n", counter);
          INDENTED(
            if (IS_USED_UNION_WITH_CHOICE(expr)) {
              OUT("return this->_choice.%s;\n", MKID_safe(v));
            } else {
              if (IS_PTR_MEMBER(v)) {
                OUT("return this->%s", identifier);
                if (IS_SECURE_POINTERS(arg))
                  OUT(".get()");
                OUT(";\n");
              } else {
                OUT("return &this->%s;\n", identifier);
              }
            }
          );
          ++counter;
          free(identifier);
        }
      }
      OUT("default:\n");
      INDENTED(
        OUT("/* This shouldn't be executed */\n");
        OUT("throw std::runtime_error(\"Invalid item index \" + std::to_string(itemIndex) + \" in ");
        out_full_class_name(arg);
        OUT("::_getPtrOnField\");\n");
      );
      OUT("} //switch end\n");
    INDENT(-1);
    OUT("}\n");
    OUT("\n");
  }
}

static void
out_asn_MEMBERS(arg_t *arg, asn1p_expr_t *expr) {
  OUT("asn_MEMBERS_%s_%d", MKID(expr), expr->_type_unique_index);
}

static void
out_asn_MBR(arg_t *arg, asn1p_expr_t *expr) {
  OUT("asn_MBR_%s_%d", MKID(expr), expr->_type_unique_index);
}

static void
out_asn_MEMBERS_t(arg_t *arg, asn1p_expr_t *expr) {
  out_asn_MEMBERS(arg, expr);
  OUT("_t");
}

static void
out_generalized_pointer_to_member(arg_t *arg) {
  OUT("void* ");
  out_full_class_name(arg);
  OUT("::*");
}

static void
emit_MemberTables(arg_t *arg) {
  assert(!IS_USED_UNION_WITH_CHOICE(arg->expr));
  asn1p_expr_t *expr = arg->expr;
  if (!HAS_MEMBERS(arg, expr))
    return;
  asn1p_expr_t *v;
  OUT("typedef std::");
  if (IS_SECURE_POINTERS(arg))
    OUT("tuple<");
  else
    OUT("pair<");
  out_generalized_pointer_to_member(arg);
  OUT(", \n");
  if (IS_SECURE_POINTERS(arg)) {
    OUT("                   std::function<AsnAbstractType*(void*&,bool)>,\n");
    OUT("                   std::function<const AsnAbstractType*(void* const&)>> ");
  } else {
    OUT("                  std::function<AsnAbstractType*()>> ");
  }
  
  out_asn_MEMBERS_t(arg, expr);
  OUT(";\n");
  OUT("\n");
  OUT("static const ");
  out_asn_MEMBERS_t(arg, expr);
  OUT(" ");
  out_asn_MEMBERS(arg, expr);
  OUT("[] = {\n", MKID(expr), expr->_type_unique_index);
  INDENT(+1);
    TQ_FOR(v, &(expr->members), next) {
      if (IS_CLASS_FIELD(v)) {
        char* identifier = 0; 
        {
          char* identifierTemp = MKID_safe(v);
          identifier = malloc(strlen(identifierTemp) + 1);
          if (!identifier) {
            FATAL("Unable to allocate memory for identifier");
            return;
          }
          strcpy(identifier, identifierTemp);
        }
        out_asn_MEMBERS_t(arg, expr);
        OUT("(reinterpret_cast<");
        out_generalized_pointer_to_member(arg);
        OUT(">(&");
        out_full_class_name(arg);
        OUT("::%s), \n", identifier);
        INDENT(+2);
            if (IS_PTR_MEMBER(v)) {
              if (IS_SECURE_POINTERS(arg)) {
                OUT("[](void*& memb_ptr, bool createNew) {\n");
                INDENT(+1);
                EMIT_FULL_TYPE_OF_FIELD;
                OUT("& ptr(reinterpret_cast<");
                EMIT_FULL_TYPE_OF_FIELD;
                OUT("&>(memb_ptr));\n");
                OUT("if (!ptr && createNew)\n");
                INDENTED(
                  OUT("ptr.reset(new ");
                  emit_full_constructor_name_for_field(arg, v);
                  OUT("());\n");
                );
                OUT("return static_cast<AsnAbstractType*>(ptr.get());\n");
                INDENT(-1);
                OUT("},\n");
                OUT("[](void* const& memb_ptr) { return static_cast<const AsnAbstractType*>(reinterpret_cast<");
                EMIT_FULL_TYPE_OF_FIELD;
                OUT(" const&>(memb_ptr).get()); }");
              } else {
                OUT("[]() { return static_cast<AsnAbstractType*>(new ");
                emit_full_constructor_name_for_field(arg, v);
                OUT("()); }");
              }
            } else {
              if (IS_SECURE_POINTERS(arg)) {
                OUT("[](void*& memb_ptr, bool) { return static_cast<AsnAbstractType*>(&reinterpret_cast<");
                EMIT_FULL_TYPE_OF_FIELD;
                OUT("&>(memb_ptr)); },\n");
                OUT("[](void* const& memb_ptr) { return static_cast<const AsnAbstractType*>(&reinterpret_cast<");
                EMIT_FULL_TYPE_OF_FIELD;
                OUT(" const&>(memb_ptr)); }");
              } else {
                OUT("0");
              }
            }
        OUT("\n");
        INDENT(-2);
        OUT("),\n");
        free(identifier);
      }
    }
  INDENT(-1);
  OUT("};\n");
  OUT("\n");
}

static void
emit_index_checking_for_member_tables(arg_t* arg) {
  OUT("#ifdef DEBUG\n");
  INDENT(+1);
  OUT("if (itemIndex < 0 || itemIndex >= ");
  out_asn_DEF(arg, arg->embed, 0);
  OUT(".elements_count");
  OUT(")\n");
  INDENTED(
    OUT("throw std::runtime_error(\"Invalid item index \" + std::to_string(itemIndex) + \" in ");
    out_full_class_name(arg);
    OUT("::_getPtrOnField\");\n");
  );
  INDENT(-1);
  OUT("#endif\n");
}

static void emit_getPtrOnMember_implementation_without_switch_for_secure_pointers(arg_t* arg) {
  {
    asn1p_expr_t *expr = arg->expr;
    OUT("AsnAbstractType* ");
    out_full_class_name(arg);
    OUT("::_getPtrOnMember(int itemIndex, bool createNew) ");
    OUT("{\n");
    emit_index_checking_for_member_tables(arg);
    INDENT(+1);
      if (!HAS_MEMBERS(arg, expr)) {
        OUT("(void)itemIndex;\n");
        OUT("(void)createNew;\n");
        OUT("return nullptr;\n");
      } else {
        OUT("const auto& memb_ptr = std::get<0>(");
        out_asn_MEMBERS(arg, expr);
        OUT("[itemIndex]);\n");
        OUT("return std::get<1>(");
        out_asn_MEMBERS(arg, expr);
        OUT("[itemIndex])(this->*memb_ptr, createNew);\n");
      }
    INDENT(-1);
    OUT("}\n");
    OUT("\n");
  }
  
  {
    asn1p_expr_t *expr = arg->expr;
    OUT("const AsnAbstractType* ");
    out_full_class_name(arg);
    OUT("::_getPtrOnMember(int itemIndex) const ");
    OUT("{\n");
    emit_index_checking_for_member_tables(arg);
    INDENT(+1);
      if (!HAS_MEMBERS(arg, expr)) {
        OUT("(void)itemIndex;\n");
        OUT("return nullptr;\n");
      } else {
        OUT("const auto& memb_ptr = std::get<0>(");
        out_asn_MEMBERS(arg, expr);
        OUT("[itemIndex]);\n");
        OUT("return std::get<2>(");
        out_asn_MEMBERS(arg, expr);
        OUT("[itemIndex])(this->*memb_ptr);\n");
      }
    INDENT(-1);
    OUT("}\n");
    OUT("\n");
  }
}

static void emit_getPtrOnMember_implementation_without_switch_for_insecure_pointers(arg_t* arg) {
  {
    asn1p_expr_t *expr = arg->expr;
    OUT("AsnAbstractType* ");
    out_full_class_name(arg);
    OUT("::_getPtrOnMember(int itemIndex, bool createNew) ");
    OUT("{\n");
    emit_index_checking_for_member_tables(arg);
    INDENT(+1);
      if (!HAS_MEMBERS(arg, expr)) {
        OUT("(void)itemIndex;\n");
        OUT("(void)createNew;\n");
        OUT("return nullptr;\n");
      } else {
        OUT("const auto& memb_ptr = ");
        out_asn_MEMBERS(arg, expr);
        OUT("[itemIndex].first;\n");
        OUT("if ((");
        out_asn_MBR(arg, expr);
        OUT("[itemIndex].flags & ATF_POINTER) && !(this->*memb_ptr) && createNew) {\n");
        INDENT(+1);
          OUT("AsnAbstractType* newObj = ");
          out_asn_MEMBERS(arg, expr);
          OUT("[itemIndex].second();\n");
          OUT("this->*memb_ptr = newObj;\n");
          OUT("return newObj;\n");
        INDENT(-1);
        OUT("}\n");
        OUT("if (");
        out_asn_MBR(arg, expr);
        OUT("[itemIndex].flags & ATF_POINTER)\n");
        INDENTED(OUT("return reinterpret_cast<AsnAbstractType*>(this->*memb_ptr);\n"););
        OUT("else\n");
        INDENTED(OUT("return &reinterpret_cast<AsnAbstractType&>(this->*memb_ptr);\n"););
      }
    INDENT(-1);
    OUT("}\n");
    OUT("\n");
  }
  
  {
    asn1p_expr_t *expr = arg->expr;
    OUT("const AsnAbstractType* ");
    out_full_class_name(arg);
    OUT("::_getPtrOnMember(int itemIndex) const ");
    OUT("{\n");
    emit_index_checking_for_member_tables(arg);
    INDENT(+1);
      if (!HAS_MEMBERS(arg, expr)) {
        OUT("(void)itemIndex;\n");
        OUT("return nullptr;\n");
      } else {
        OUT("const auto& memb_ptr = ");
        out_asn_MEMBERS(arg, expr);
        OUT("[itemIndex].first;\n");
        OUT("if (");
        out_asn_MBR(arg, expr);
        OUT("[itemIndex].flags & ATF_POINTER)\n");
        INDENTED(OUT("return reinterpret_cast<const AsnAbstractType*>(this->*memb_ptr);\n"););
        OUT("else\n");
        INDENTED(OUT("return &reinterpret_cast<const AsnAbstractType&>(this->*memb_ptr);\n"););
      }
    INDENT(-1);
    OUT("}\n");
    OUT("\n");
  }
}

static void emit_getPtrOnMember_implementation_without_switch(arg_t* arg) {
  emit_MemberTables(arg);
  if (IS_SECURE_POINTERS(arg))
    emit_getPtrOnMember_implementation_without_switch_for_secure_pointers(arg);
  else
    emit_getPtrOnMember_implementation_without_switch_for_insecure_pointers(arg);
}

static void emit_getPtrOnMember_implementation(arg_t* arg) {
  if (arg->flags & A1C_NO_SWITCH && !IS_USED_UNION_WITH_CHOICE(arg->expr)) {
    emit_getPtrOnMember_implementation_without_switch(arg);
  } else {
    emit_getPtrOnMember_implementation_with_switch(arg);
  }
}



static
void emit_ref_class(arg_t *arg) {
  asn1p_expr_t *expr = arg->expr;
  MAKE_CLASS_NAME("out_ref_class", expr);
  OUT("class %s : public ", className);
  emit_namespace_name(arg, arg->expr, arg->expr);
  OUT("%s {\n", asn1c_type_name(arg, arg->expr, TNF_CTYPE));
  OUT("public:\n");
  INDENT(+1);
    OUT("%s() : %s() { }\n", className, asn1c_type_name(arg, arg->expr, TNF_CTYPE));
    OUT("%s(const %s&) = default;\n", className, className);
    OUT("%s(%s&&) noexcept = default;\n", className, className);
    OUT("%s& operator =(const %s&) = default;\n", className, className);
    OUT("%s& operator =(%s&&) noexcept = default;\n", className, className);
    OUT("using %s::operator =;\n", asn1c_type_name(arg, arg->expr, TNF_CTYPE));
    OUT("virtual ~%s() noexcept { }\n", className);
  INDENT(-1);
  OUT("private:\n");
  INDENT(+1);
    OUT("asn_TYPE_descriptor_t* _getDefaultTypeDescriptorPtr() const override { return ");
    out_asn_DEF(arg, arg->embed, 1);
    OUT("; }\n");
  INDENT(-1);
  OUT("}; //End of %s\n", className);
}

int
asn1c_lang_CPP_type_EXTENSIBLE(arg_t *arg) {

	OUT("/*\n");
	OUT(" * This type is extensible,\n");
	OUT(" * possible extensions are below.\n");
	OUT(" */\n");

	return 0;
}

static int
compute_extensions_start(asn1p_expr_t *expr) {
	asn1p_expr_t *v;
	int eidx = 0;
	TQ_FOR(v, &(expr->members), next) {
		if(v->expr_type == A1TC_EXTENSIBLE)
			return eidx;
		eidx++;
	}
	return -1;
}

static int
_print_tag(arg_t *arg, struct asn1p_type_tag_s *tag) {

	OUT("(");
	switch(tag->tag_class) {
	case TC_UNIVERSAL:		OUT("ASN_TAG_CLASS_UNIVERSAL"); break;
	case TC_APPLICATION:		OUT("ASN_TAG_CLASS_APPLICATION"); break;
	case TC_CONTEXT_SPECIFIC:	OUT("ASN_TAG_CLASS_CONTEXT"); break;
	case TC_PRIVATE:		OUT("ASN_TAG_CLASS_PRIVATE"); break;
	case TC_NOCLASS:
		break;
	}
	OUT(" | (%" PRIdASN " << 2))", tag->tag_value);

	return 0;
}


static int
_tag2el_cmp(const void *ap, const void *bp) {
	const tag2el_t *a = ap;
	const tag2el_t *b = bp;
	const struct asn1p_type_tag_s *ta = &a->el_tag;
	const struct asn1p_type_tag_s *tb = &b->el_tag;

	if(ta->tag_class == tb->tag_class) {
		if(ta->tag_value == tb->tag_value) {
			/*
			 * Sort by their respective positions.
			 */
			if(a->el_no < b->el_no)
				return -1;
			else if(a->el_no > b->el_no)
				return 1;
			return 0;
		} else if(ta->tag_value < tb->tag_value)
			return -1;
		else
			return 1;
	} else if(ta->tag_class < tb->tag_class) {
		return -1;
	} else {
		return 1;
	}
}

/*
 * For constructed types, number of external tags may be greater than
 * number of elements in the type because of CHOICE type.
 * T ::= SET {		-- Three possible tags:
 *     a INTEGER,	-- One tag is here...
 *     b Choice1	-- ... and two more tags are there.
 * }
 * Choice1 ::= CHOICE {
 *     s1 IA5String,
 *     s2 ObjectDescriptor
 * }
 */
static int
_fill_tag2el_map(arg_t *arg, tag2el_t **tag2el, int *count, int el_no, fte_e flags) {
	asn1p_expr_t *expr = arg->expr;
	arg_t tmparg = *arg;
	asn1p_expr_t *v;
	int element = 0;
	int original_count = *count;
	int sort_until = -1;

	TQ_FOR(v, &(expr->members), next) {
		if(v->expr_type == A1TC_EXTENSIBLE) {
			/*
			 * CXER mandates sorting
			 * only for the root part.
			 */
			if(flags == FTE_CANONICAL_XER
			&& sort_until == -1)
				sort_until = *count;
			continue;
		}

		tmparg.expr = v;

		if(_add_tag2el_member(&tmparg, tag2el, count,
				(el_no==-1)?element:el_no, flags)) {
			return -1;
		}

		element++;
	}


	if(flags == FTE_CANONICAL_XER) {
		if(sort_until == -1) sort_until = *count;
		qsort((*tag2el) + original_count,
			sort_until - original_count,
				sizeof(**tag2el), _tag2el_cmp);
		if(arg->expr->expr_type == ASN_CONSTR_CHOICE
		&& (sort_until - original_count) >= 1) {
			/* Only take in account the root component */
			*count = original_count + 1;
		}
	} else {
		/*
		 * Sort the map according to canonical order of their
		 * tags and element numbers.
		 */
		qsort(*tag2el, *count, sizeof(**tag2el), _tag2el_cmp);
	}

	/*
	 * Initialize .toff_{first|last} members.
	 */
	if(*count) {
		struct asn1p_type_tag_s *cur_tag = 0;
		tag2el_t *cur = *tag2el;
		tag2el_t *end = cur + *count;
		int occur, i;
		for(occur = 0; cur < end; cur++) {
			if(cur_tag == 0
			|| cur_tag->tag_value != cur->el_tag.tag_value
			|| cur_tag->tag_class != cur->el_tag.tag_class) {
				cur_tag = &cur->el_tag;
				occur = 0;
			} else {
				occur++;
			}
			cur->toff_first = -occur;
			for(i = 0; i >= -occur; i--)
				cur[i].toff_last = -i;
		}
	}

	return 0;
}

static int
_add_tag2el_member(arg_t *arg, tag2el_t **tag2el, int *count, int el_no, fte_e flags) {
	struct asn1p_type_tag_s tag;
	int ret;

	assert(el_no >= 0);

	ret = asn1f_fetch_outmost_tag(arg->asn, arg->expr->module,
			arg->expr, &tag, AFT_IMAGINARY_ANY);
	if(ret == 0) {
		tag2el_t *te;
		int new_count = (*count) + 1;
		void *p;

		if(tag.tag_value == -1) {
			/*
			 * This is an untagged ANY type,
			 * proceed without adding a tag
			 */
			return 0;
		}

		p = realloc(*tag2el, new_count * sizeof(tag2el_t));
		if(p)	*tag2el = p;
		else	return -1;

		if(0) DEBUG("Found tag for %s: %ld",
			arg->expr->Identifier,
			(long)tag.tag_value);

		te = &((*tag2el)[*count]);
		te->el_tag = tag;
		te->el_no = el_no;
		te->from_expr = arg->expr;
		*count = new_count;
		return 0;
	}

	DEBUG("Searching tag in complex expression %s:%x at line %d",
		arg->expr->Identifier,
		arg->expr->expr_type,
		arg->expr->_lineno);

	/*
	 * Iterate over members of CHOICE type.
	 */
	if(arg->expr->expr_type == ASN_CONSTR_CHOICE) {
		return _fill_tag2el_map(arg, tag2el, count, el_no, flags);
	}

	if(arg->expr->expr_type == A1TC_REFERENCE) {
		arg_t tmp = *arg;
		asn1p_expr_t *expr;
		expr = asn1f_lookup_symbol_ex(tmp.asn, tmp.expr,
			arg->expr->reference);
		if(expr) {
			tmp.expr = expr;
			return _add_tag2el_member(&tmp, tag2el, count, el_no, flags);
		} else {
			FATAL("Cannot dereference %s at line %d",
				arg->expr->Identifier,
				arg->expr->_lineno);
			return -1;
		}
	}

	DEBUG("No tag for %s at line %d",
		arg->expr->Identifier,
		arg->expr->_lineno);

	return -1;
}

static int
emit_tag2member_map(arg_t *arg, tag2el_t *tag2el, int tag2el_count, const char *opt_modifier) {
	asn1p_expr_t *expr = arg->expr;
	int i;

	if(!tag2el_count) return 0;	/* No top level tags */

	OUT("static const asn_TYPE_tag2member_t asn_MAP_%s_tag2el%s_%d[] = {\n",
		MKID(expr), opt_modifier?opt_modifier:"",
		expr->_type_unique_index);
	for(i = 0; i < tag2el_count; i++) {
		OUT("    { ");
		_print_tag(arg, &tag2el[i].el_tag);
		OUT(", ");
		OUT("%d, ", tag2el[i].el_no);
		OUT("%d, ", tag2el[i].toff_first);
		OUT("%d ", tag2el[i].toff_last);
		OUT("}%s /* %s",
			(i + 1 < tag2el_count) ? "," : "",
			tag2el[i].from_expr->Identifier);
    if(arg->flags & A1C_LINE_REFS)
        OUT(" at %d", tag2el[i].from_expr->_lineno);
    OUT(" */\n");
	}
	OUT("};\n");

	return 0;
}

static enum tvm_compat
emit_tags_vectors(arg_t *arg, asn1p_expr_t *expr, int *tags_count_r, int *all_tags_count_r) {
	struct asn1p_type_tag_s *tags = 0;	/* Effective tags */
	struct asn1p_type_tag_s *all_tags = 0;	/* The full array */
	int tags_count = 0;
	int all_tags_count = 0;
	enum tvm_compat tv_mode = _TVM_SAME;
	int i;

	/* Cleanup before proceeding. */
	*tags_count_r = 0;
	*all_tags_count_r = 0;

	/* Fetch a chain of tags */
	tags_count = asn1f_fetch_tags(arg->asn, expr->module, expr, &tags, 0);
	if(tags_count < 0) {
		DEBUG("fail to fetch tags for %s", expr->Identifier);
		return -1;
	}

	/* Fetch a chain of tags */
	all_tags_count = asn1f_fetch_tags(arg->asn, expr->module, expr,
		&all_tags, AFT_FULL_COLLECT);
	if(all_tags_count < 0) {
		if(tags) free(tags);
		DEBUG("fail to fetch tags chain for %s", expr->Identifier);
		return -1;
	}

	assert(tags_count <= all_tags_count);
	assert((tags_count?0:1) == (all_tags_count?0:1));

	if(tags_count <= all_tags_count) {
		for(i = 0; i < tags_count; i++) {
			if(tags[i].tag_value != all_tags[i].tag_value
			|| tags[i].tag_class != all_tags[i].tag_class) {
				tv_mode = _TVM_DIFFERENT;
				break;
			}
		}
		if(i == tags_count && tags_count < all_tags_count)
			tv_mode = _TVM_SUBSET;
	} else {
		tv_mode = _TVM_DIFFERENT;
	}

#define	EMIT_TAGS_TABLE(name, tags, tags_count)	do {			\
		OUT("static const ber_tlv_tag_t asn_DEF_%s%s_tags_%d[] = {\n",\
			MKID(expr), name,			\
			expr->_type_unique_index);			\
		INDENT(+1);						\
		/* Print the array of collected tags */			\
		for(i = 0; i < tags_count; i++) {			\
			if(i) OUT(",\n");				\
			_print_tag(arg, &tags[i]);			\
		}							\
		OUT("\n");						\
		INDENT(-1);						\
		OUT("};\n");						\
	} while(0)

	if(tags_count) {
		if(tv_mode == _TVM_SUBSET)
			EMIT_TAGS_TABLE("", all_tags, all_tags_count);
		else
			EMIT_TAGS_TABLE("", tags, tags_count);
	}

	if(all_tags_count) {
		if(tv_mode == _TVM_DIFFERENT)
			EMIT_TAGS_TABLE("_all", all_tags, all_tags_count);
	}

	if(tags) free(tags);
	if(all_tags) free(all_tags);

	*tags_count_r = tags_count;
	*all_tags_count_r = all_tags_count;

	return tv_mode;
}

static int
expr_elements_count(arg_t *arg, asn1p_expr_t *expr) {
	asn1p_expr_t *topmost_parent;
	asn1p_expr_t *v;
	int elements = 0;

	topmost_parent = asn1f_find_terminal_type_ex(arg->asn, expr);
	if(!topmost_parent) return 0;

	if(!(topmost_parent->expr_type & ASN_CONSTR_MASK)
	&& !topmost_parent->expr_type == ASN_BASIC_INTEGER
	&& !topmost_parent->expr_type == ASN_BASIC_ENUMERATED)
		return 0;

	TQ_FOR(v, &(topmost_parent->members), next) {
		if(v->expr_type != A1TC_EXTENSIBLE)
			elements++;
	}

	return elements;
}

static asn1p_expr_type_e
expr_get_type(arg_t *arg, asn1p_expr_t *expr) {
	asn1p_expr_t *terminal;
	terminal = asn1f_find_terminal_type_ex(arg->asn, expr);
	if(terminal) return terminal->expr_type;
	return A1TC_INVALID;
}

static asn1c_integer_t
PER_FROM_alphabet_characters(asn1cnst_range_t *range) {
	asn1c_integer_t numchars = 0;
	if(range->el_count) {
		int i;
		for(i = 0; i < range->el_count; i++)
			numchars
			+= PER_FROM_alphabet_characters(range->elements[i]);
	} else {
		assert(range->left.type == ARE_VALUE);
		assert(range->right.type == ARE_VALUE);
		numchars = 1 + (range->right.value - range->left.value);
	}
	return numchars;
}

static int
emit_single_member_PER_constraint(arg_t *arg, asn1cnst_range_t *range, int alphabetsize, char *type) {
	if(!range || range->incompatible || range->not_PER_visible) {
		OUT("{ APC_UNCONSTRAINED,\t-1, -1,  0,  0 }");
		return 0;
	}

	if(range->left.type == ARE_VALUE) {
		if(range->right.type == ARE_VALUE) {
			asn1c_integer_t cover = 1;
			asn1c_integer_t r = 1 + range->right.value
					      - range->left.value;
			size_t rbits;	/* Value range bits */
			ssize_t ebits;	/* Value effective range bits */

			if(range->empty_constraint)
				r = 0;

			if(alphabetsize) {
				/* X.691: 27.5.2 */
				r = PER_FROM_alphabet_characters(range);
			}

			/* Compute real constraint */
			for(rbits = 0; rbits < (8 * sizeof(r)); rbits++) {
				if(r <= cover)
					break;
				cover *= 2;	/* Can't do shifting */
				if(cover < 0) {
					FATAL("Constraint at line %d too wide "
						"for %d-bits integer type",
						arg->expr->_lineno,
						sizeof(r) * 8);
					rbits = sizeof(r);
					break;
				}
			}

			if(alphabetsize) {
				ebits = rbits;
			} else {
				/* X.691, #10.9.4.1 */
				for(ebits = 0; ebits <= 16; ebits++)
					if(r <= 1 << ebits) break;
				if(ebits == 17
				|| range->right.value >= 65536)
					ebits = -1;
			if(0) {
				/* X.691, #10.5.7.1 */
				for(ebits = 0; ebits <= 8; ebits++)
					if(r <= 1 << ebits) break;
				if(ebits == 9) {
					if(r <= 65536)
						ebits = 16;
					else
						ebits = -1;
				}
			}
			}

			OUT("{ APC_CONSTRAINED%s,%s% d, % d, ",
				range->extensible
					? " | APC_EXTENSIBLE" : "",
				range->extensible ? " " : "\t", rbits, ebits);

			if(alphabetsize) {
				asn1c_integer_t lv = range->left.value;
				asn1c_integer_t rv = range->right.value;
				int gcmt = 0;
				if(lv > 0x7fffffff) { lv = 0x7fffffff; gcmt++; }
				if(rv > 0x7fffffff) { rv = 0x7fffffff; gcmt++; }
				if(gcmt) {
					OINTS(lv); OUT(", "); OINTS(rv); OUT(" }");
					goto pcmt;
				}
			}
		} else {
			if(range->extensible) {
				OUT("{ APC_SEMI_CONSTRAINED | APC_EXTENSIBLE, "
					"-1, ");
			} else {
				OUT("{ APC_SEMI_CONSTRAINED,\t-1, -1, ");
			}
		}
		OINTS(range->left.value); OUT(", ");
		OINTS(range->right.value); OUT(" }");
	} else {
		OUT("{ APC_UNCONSTRAINED,\t-1, -1,  0,  0 }");
	}

  pcmt:

	/*
	 * Print some courtesy debug information.
	 */
	if(range->left.type == ARE_VALUE
	|| range->right.type == ARE_VALUE) {
		OUT("\t/* ");
		if(type) OUT("(%s", type);
		OUT("(");
		if(range->left.type == ARE_VALUE)
			OUT("%" PRIdASN, range->left.value);
		else
			OUT("MIN");
		OUT("..");
		if(range->right.type == ARE_VALUE)
			OUT("%" PRIdASN, range->right.value);
		else
			OUT("MAX");
		if(range->extensible) OUT(",...");
		if(type) OUT(")");
		OUT(") */");
	}

	return 0;
}

static int
emit_member_PER_constraints(arg_t *arg, asn1p_expr_t *expr, const char *pfx) {
	int save_target = arg->target->target;
	asn1cnst_range_t *range;
	asn1p_expr_type_e etype;

	etype = expr_get_type(arg, expr);

	if((arg->flags & A1C_GEN_PER)
	&& (expr->constraints
		|| etype == ASN_BASIC_ENUMERATED
		|| etype == ASN_CONSTR_CHOICE)
	) {
		/* Fall through */
	} else {
		return 0;
	}

	REDIR(OT_CTDEFS);

	OUT("static asn_per_constraints_t "
		"asn_PER_%s_%s_constr_%d GCC_NOTUSED = {\n",
		pfx, MKID(expr), expr->_type_unique_index);

	INDENT(+1);

	/*
	 * ENUMERATED and CHOICE are special.
	 */
	if(etype == ASN_BASIC_ENUMERATED
	|| etype == ASN_CONSTR_CHOICE) {
		asn1cnst_range_t tmprng;
		asn1p_expr_t *v;
		int extensible = 0;
		int eidx = -1;

		expr = asn1f_find_terminal_type_ex(arg->asn, expr);
		assert(expr);

		TQ_FOR(v, &(expr->members), next) {
			if(v->expr_type == A1TC_EXTENSIBLE) {
				extensible++;
				break;
			}
			eidx++;
		}

		memset(&tmprng, 0, sizeof (tmprng));
		tmprng.extensible = extensible;
		if(eidx < 0) tmprng.empty_constraint = 1;
		tmprng.left.type = ARE_VALUE;
		tmprng.left.value = 0;
		tmprng.right.type = ARE_VALUE;
		tmprng.right.value = eidx < 0 ? 0 : eidx;
		if(emit_single_member_PER_constraint(arg, &tmprng, 0, 0))
			return -1;
	} else if(etype & ASN_STRING_KM_MASK) {
		range = asn1constraint_compute_PER_range(etype,
				expr->combined_constraints, ACT_CT_FROM,
				0, 0, 0);
		DEBUG("Emitting FROM constraint for %s", expr->Identifier);

		if((range->left.type == ARE_MIN && range->right.type == ARE_MAX)
		|| range->not_PER_visible) {
			switch(etype) {
			case ASN_STRING_BMPString:
				range->left.type = ARE_VALUE;
				range->left.value = 0;
				range->right.type = ARE_VALUE;
				range->right.value = 65535;
				range->not_PER_visible = 0;
				range->extensible = 0;
				break;
			case ASN_STRING_UniversalString:
				OUT("{ APC_CONSTRAINED,\t32, 32,"
					" 0, 2147483647 }"
					" /* special case 1 */\n");
				goto avoid;
			default:
				break;
			}
		}
		if(emit_single_member_PER_constraint(arg, range, 1, 0))
			return -1;
		avoid:
		asn1constraint_range_free(range);
	} else {
		range = asn1constraint_compute_PER_range(etype,
				expr->combined_constraints, ACT_EL_RANGE,
				0, 0, 0);
		if(emit_single_member_PER_constraint(arg, range, 0, 0))
			return -1;
		asn1constraint_range_free(range);
	}
	OUT(",\n");

	range = asn1constraint_compute_PER_range(etype,
			expr->combined_constraints, ACT_CT_SIZE, 0, 0, 0);
	if(emit_single_member_PER_constraint(arg, range, 0, "SIZE"))
		return -1;
	asn1constraint_range_free(range);
	OUT(",\n");

	if((etype & ASN_STRING_KM_MASK) && (expr->_mark & TM_PERFROMCT)) {
		int old_target = arg->target->target;
		REDIR(OT_CODE);

		OUT("static int asn_PER_MAP_%s_%d_v2c(unsigned int value) {\n",
			MKID(expr), expr->_type_unique_index);
		OUT("\tif(value >= sizeof(permitted_alphabet_table_%d)/"
			"sizeof(permitted_alphabet_table_%d[0]))\n",
			expr->_type_unique_index,
			expr->_type_unique_index);
		OUT("\t\treturn -1;\n");
		OUT("\treturn permitted_alphabet_table_%d[value] - 1;\n",
			expr->_type_unique_index);
		OUT("}\n");

		OUT("static int asn_PER_MAP_%s_%d_c2v(unsigned int code) {\n",
			MKID(expr), expr->_type_unique_index);
		OUT("\tif(code >= sizeof(permitted_alphabet_code2value_%d)/"
			"sizeof(permitted_alphabet_code2value_%d[0]))\n",
			expr->_type_unique_index,
			expr->_type_unique_index);
		OUT("\t\treturn -1;\n");
		OUT("\treturn permitted_alphabet_code2value_%d[code];\n",
			expr->_type_unique_index);
		OUT("}\n");

		REDIR(old_target);

		OUT("asn_PER_MAP_%s_%d_v2c,\t/* Value to PER code map */\n",
			MKID(expr), expr->_type_unique_index);
		OUT("asn_PER_MAP_%s_%d_c2v\t/* PER code to value map */\n",
			MKID(expr), expr->_type_unique_index);
	} else if(etype & ASN_STRING_KM_MASK) {
		DEBUG("No PER value map necessary for %s", MKID(expr));
		OUT("0, 0\t/* No PER character map necessary */\n");
	} else {
		OUT("0, 0\t/* No PER value map */\n");
	}

	INDENT(-1);

	OUT("};\n");

	REDIR(save_target);

	return 0;
}

static int
safe_string(const uint8_t *buf, int size) {
  if (strstr((const char*)buf, "*/"))
    return 0;
	const uint8_t *end = buf + size;
	for(; buf < end; buf++) {
		int ch = *buf;
		if((ch < 0x20 || ch > 0x7e) /*|| ch == '"'*/)
			return 0;
	}
	return 1;
}

static int
is_one_byte_string(asn1p_expr_type_e etype) {
  switch (etype) {
    case ASN_STRING_UTF8String:
    case ASN_STRING_IA5String:
    case ASN_STRING_VisibleString:
    case ASN_STRING_ISO646String:
    case ASN_STRING_NumericString:
    case ASN_STRING_PrintableString:
      return 1;
    default:
      return 0;
  };
}

static void
emit_default_value(arg_t *arg, asn1p_value_t *v, asn1p_expr_type_e etype) {

	OUT("static %s defv = ", is_one_byte_string(etype) ? "std::string" : "std::vector<uint8_t>");
	assert(v->type == ATV_STRING);
  
  uint8_t *b = v->value.string.buf;
  uint8_t *e = v->value.string.size + b;
  OUT("{ ");
  for(;b < e; b++) {
    if (ASN_STRING_BMPString == etype)
      OUT("0x00, ");
    else if (ASN_STRING_UniversalString == etype)
      OUT("0x00, 0x00, 0x00, ");
    OUT("0x%02x", *b);
    if ((b + 1) != e)
      OUT(", ");
  }
  OUT(" };");

	if(safe_string(v->value.string.buf, v->value.string.size)) {
		OUT(" /* %s */", v->value.string.buf);
	} 
  OUT("\n");
}

static int
try_inline_default(arg_t *arg, asn1p_expr_t *expr, int out, int only_func_name) {
	int save_target = arg->target->target;
	asn1p_expr_type_e etype = expr_get_type(arg, expr);
	int fits_long = 0;

	switch(etype) {
	case ASN_BASIC_BOOLEAN: {
		fits_long = 1;
    if (!expr->marker.default_value || 
            (expr->marker.default_value->type != ATV_TRUE && 
            expr->marker.default_value->type != ATV_FALSE))
      break;
    int value = (expr->marker.default_value->type == ATV_TRUE);
    if(!out) {
      if (2 == only_func_name)
        return 1;
			OUT("asn_DFL_%d_set_%s", expr->_type_unique_index, value ? "true" : "false");
      if (!only_func_name)
        OUT(",\t/* DEFAULT %" PRIdASN " */\n",
          expr->marker.default_value->value.v_integer);
			return 1;
		}
    REDIR(OT_STAT_DEFS);
		OUT("static int asn_DFL_%d_set_%s", expr->_type_unique_index, value ? "true" : "false"); 
    OUT("(int set_value, void **sptr) {\n");
		INDENT(+1);
		OUT("%s *st = static_cast<%s*>(*sptr);\n", 
            asn1c_type_name(arg, expr, TNF_CTYPE), 
            asn1c_type_name(arg, expr, TNF_CTYPE));
		OUT("\n");
		OUT("if(!st) {\n");
		INDENTED(OUT("return -1;\n"));
		OUT("}\n");
		OUT("\n");
		OUT("if(set_value) {\n");
		INDENT(+1);
      OUT("/* Install default value %s */\n", value ? "true" : "false");
      OUT("*st = %s ;\n", value ? "0xFF" : "0");
      OUT("return 0;\n");
		INDENT(-1);
		OUT("} else {\n");
		INDENT(+1);
      OUT("/* Test default value %s */\n", value ? "true" : "false");
      OUT("return (%s(*st));\n", value ? "" : "!");
		INDENT(-1);
		OUT("}\n");
		INDENT(-1);
		OUT("}\n");
		REDIR(save_target);
    return 1;
  }
	case ASN_BASIC_INTEGER:
	case ASN_BASIC_ENUMERATED:
		if(expr->marker.default_value == NULL
		|| expr->marker.default_value->type != ATV_INTEGER)
			break;
		if(!fits_long)
			fits_long = asn1c_type_fits_long(arg, expr)!=FL_NOTFIT;
		if(fits_long && !expr->marker.default_value->value.v_integer)
			expr->marker.flags &= ~EM_INDIRECT;
		if(!out) {
      if (2 == only_func_name)
        return 1;
			OUT("asn_DFL_%d_set_%" PRIdASN, expr->_type_unique_index,
				expr->marker.default_value->value.v_integer);
      if (!only_func_name)
        OUT(",\t/* DEFAULT %" PRIdASN " */\n",
          expr->marker.default_value->value.v_integer);
			return 1;
		}
		REDIR(OT_STAT_DEFS);
		OUT("static int asn_DFL_%d_set_%" PRIdASN "(int set_value, void **sptr) {\n",
			expr->_type_unique_index,
			expr->marker.default_value->value.v_integer);
		INDENT(+1);
		OUT("%s *st = static_cast<%s*>(*sptr);\n", 
            asn1c_type_name(arg, expr, TNF_CTYPE), 
            asn1c_type_name(arg, expr, TNF_CTYPE));
		OUT("\n");
		OUT("if(!st) {\n");
		INDENTED(OUT("return -1;\n"));
		OUT("}\n");
		OUT("\n");
		OUT("if(set_value) {\n");
		INDENT(+1);
		OUT("/* Install default value %" PRIdASN " */\n",
			expr->marker.default_value->value.v_integer);
		if(fits_long) {
			OUT("*st = ");
			OINT(expr->marker.default_value->value.v_integer);
			OUT(";\n");
			OUT("return 0;\n");
		} else {
			OUT("return st->FromLong(");
			OINT(expr->marker.default_value->value.v_integer);
			OUT(") ? 0 : -1;\n");
		}
		INDENT(-1);
		OUT("} else {\n");
		INDENT(+1);
		OUT("/* Test default value %" PRIdASN " */\n",
			expr->marker.default_value->value.v_integer);
		if(fits_long) {
			OUT("return (*st == %" PRIdASN ");\n",
				expr->marker.default_value->value.v_integer);
		} else {
			OUT("%s value;\n", asn1c_type_name(arg, expr, TNF_CTYPE));
      OUT("if (!value.FromLong(%" PRIdASN "))\n", expr->marker.default_value->value.v_integer);
      INDENTED(OUT("return -1;\n"););
			OUT("return (value == *st);\n");
		}
		INDENT(-1);
		OUT("}\n");
		INDENT(-1);
		OUT("}\n");
		REDIR(save_target);
		return 1;
	case ASN_BASIC_NULL:
		//expr->marker.flags &= ~EM_INDIRECT;
		return 0;
	default:
	  if(etype & ASN_STRING_KM_MASK) {
		if(expr->marker.default_value == NULL
		|| expr->marker.default_value->type != ATV_STRING)
			break;
		if(!out) {
      if (2 == only_func_name)
        return 1;
			OUT("asn_DFL_%d_set", expr->_type_unique_index);
      if (!only_func_name) {
        OUT(",\t/* DEFAULT ");
        if (safe_string(expr->marker.default_value->value.string.buf, expr->marker.default_value->value.string.size))
          OUT("\"%s\" ", expr->marker.default_value->value.string.buf);
        OUT("*/\n");
      }
			return 1;
		}
		REDIR(OT_STAT_DEFS);
		OUT("static int asn_DFL_%d_set(int set_value, void **sptr) {\n", expr->_type_unique_index);
		INDENT(+1);
		emit_default_value(arg, expr->marker.default_value, etype);
		OUT("%s *st = static_cast<%s*>(*sptr);\n", 
            asn1c_type_name(arg, expr, TNF_CTYPE), 
            asn1c_type_name(arg, expr, TNF_CTYPE));
		OUT("\n");
		OUT("if(!st) {\n");
    INDENTED(OUT("return -1;\n"));
		OUT("}\n");
		OUT("\n");
		OUT("if(set_value) {\n");
		INDENT(+1);
      OUT("*st = defv;\n");
			OUT("return 0;\n");
		INDENT(-1);
		OUT("} else {\n");
		INDENT(+1);
			OUT("if(*st != defv)\n");
			OUT("\treturn 0;\n");
			OUT("return 1;\n");
		INDENT(-1);
		OUT("}\n"); OUT("\n");
		INDENT(-1);
		OUT("}\n");
		REDIR(save_target);
		return 1;
	  }
	  break;
	}
	return 0;
}

static int
emit_member_table(arg_t *arg, asn1p_expr_t *expr, int element_index) {
	int save_target;
	arg_t tmp_arg;
	struct asn1p_type_tag_s outmost_tag_s;
	struct asn1p_type_tag_s *outmost_tag;
	int complex_contents;
	char *p;

	if(asn1f_fetch_outmost_tag(arg->asn,
			expr->module, expr, &outmost_tag_s,
			AFT_IMAGINARY_ANY)) {
		outmost_tag = 0;
	} else {
		outmost_tag = &outmost_tag_s;
	}

	OUT("{ ");

	if(outmost_tag && outmost_tag->tag_value == -1)
		OUT("static_cast<asn_TYPE_flags_e>(ATF_OPEN_TYPE | ");
	OUT("%s",
		(expr->marker.flags & EM_INDIRECT)?"ATF_POINTER":"ATF_NOFLAGS");
  if(outmost_tag && outmost_tag->tag_value == -1)
    OUT(")");
  OUT(", ");
	if((expr->marker.flags & EM_OMITABLE) == EM_OMITABLE) {
		asn1p_expr_t *tv;
		int opts = 0;
		for(tv = expr;
			tv && (tv->marker.flags & EM_OMITABLE) == EM_OMITABLE;
			tv = TQ_NEXT(tv, next), opts++) {
			if(tv->expr_type == A1TC_EXTENSIBLE)
				opts--;
		}
		OUT("%d, ", opts);
	} else {
		OUT("0, ");
	}
//	if(expr->_anonymous_type) {
//		assert(arg->expr->expr_type == ASN_CONSTR_SET_OF
//			|| arg->expr->expr_type == ASN_CONSTR_SEQUENCE_OF);
//		OUT("0,\n");
//	} else {
//    OUT("%d,\n", element_index); 
//  }
  OUT("\n");
	INDENT(+1);
	if(C99_MODE) OUT(".tag = ");
	if(outmost_tag) {
		if(outmost_tag->tag_value == -1)
			OUT("static_cast<ber_tlv_tag_t>(-1) /* Ambiguous tag (ANY?) */");
		else
			_print_tag(arg, outmost_tag);
	} else {
		OUT("static_cast<ber_tlv_tag_t>(-1) /* Ambiguous tag (CHOICE?) */");
	}

	OUT(",\n");
	if(C99_MODE) OUT(".tag_mode = ");
	if((!(expr->expr_type &  ASN_CONSTR_MASK)
	   || expr->expr_type == ASN_CONSTR_CHOICE)
	&& expr->tag.tag_class) {
		if(expr->tag.tag_mode == TM_IMPLICIT)
		OUT("-1,\t/* IMPLICIT tag at current level */\n");
		else
		OUT("+1,\t/* EXPLICIT tag at current level */\n");
	} else {
		OUT("0,\n");
	}

	complex_contents =
		(expr->expr_type & ASN_CONSTR_MASK)
		|| expr->expr_type == ASN_BASIC_ENUMERATED
		|| (0 /* -- prohibited by X.693:8.3.4 */
			&& expr->expr_type == ASN_BASIC_INTEGER
			&& expr_elements_count(arg, expr))
		|| (expr->expr_type == ASN_BASIC_INTEGER
			&& asn1c_type_fits_long(arg, expr) == FL_FITS_UNSIGN);
	if(C99_MODE) OUT(".type = ");
	OUT("(asn_TYPE_descriptor_t*)&");
  emit_namespace_name(arg, arg->expr, expr);
  OUT("asn_DEF_");
	if(complex_contents) {
		OUT("%s", MKID(expr));
		//if(!(arg->flags & A1C_ALL_DEFS_GLOBAL))
			OUT("_%d", expr->_type_unique_index);
	} else {
		OUT("%s", asn1c_type_name(arg, expr, TNF_SAFE));
	}
	OUT(",\n");
	if(C99_MODE) OUT(".memb_constraints = ");
	if(expr->constraints) {
		if(arg->flags & A1C_NO_CONSTRAINTS) {
			OUT("0,\t/* No check because of -fno-constraints */\n");
		} else {
			char *id = MKID(expr);
			if(expr->_anonymous_type
					&& !strcmp(expr->Identifier, "Member"))
				id = asn1c_type_name(arg, expr, TNF_SAFE);
			OUT("memb_%s_constraint_%d,\n", id,
				arg->expr->_type_unique_index);
		}
	} else {
		OUT("0,\t/* Defer constraints checking to the member type */\n");
	}
  ++arg->ignore_code;
	if(C99_MODE) OUT(".per_constraints = ");
	if(arg->flags & A1C_GEN_PER) {
		if(expr->constraints) {
			OUT("&asn_PER_memb_%s_constr_%d,\n",
				MKID(expr),
				expr->_type_unique_index);
		} else {
			OUT("0,\t/* No PER visible constraints */\n");
		}
	} else {
		OUT("0,\t/* PER is not compiled, use -gen-PER */\n");
	}
  --arg->ignore_code;
	if(C99_MODE) OUT(".default_value = ");
	if(try_inline_default(arg, expr, 0, 0)) {
	} else {
		OUT("0,\n");
	}
	if(C99_MODE) OUT(".name = ");
	if(expr->_anonymous_type && !strcmp(expr->Identifier, "Member")) {
		OUT("\"\"\n");
	} else {
		OUT("\"%s\"\n", expr->Identifier);
	}
	OUT("},\n");
	INDENT(-1);

	if(!expr->constraints || (arg->flags & A1C_NO_CONSTRAINTS))
		return 0;

	save_target = arg->target->target;
	REDIR(OT_CODE);

	if(expr->_anonymous_type && !strcmp(expr->Identifier, "Member"))
		p = asn1c_type_name(arg, expr, TNF_SAFE);
	else
		p = MKID(expr);
	OUT("static int\n");
	OUT("memb_%s_constraint_%d(asn_TYPE_descriptor_t *td, const void *sptr,\n", p, arg->expr->_type_unique_index);
	INDENT(+1);
	OUT("\t\tasn_app_constraint_failed_f *ctfailcb, void *app_key) {\n");
	tmp_arg = *arg;
	tmp_arg.expr = expr;
	DEBUG("member constraint checking code for %s", p);
	if(asn1c_emit_constraint_checking_code(&tmp_arg) == 1) {
		OUT("return td->check_constraints"
			"(td, sptr, ctfailcb, app_key);\n");
	}
	INDENT(-1);
	OUT("}\n");
	OUT("\n");

	if(emit_member_PER_constraints(arg, expr, "memb"))
		return -1;

	REDIR(save_target);

	return 0;
}

/*
 * Generate "asn_DEF_XXX" type definition.
 */
static int
emit_type_DEF(arg_t *arg, asn1p_expr_t *expr, enum tvm_compat tv_mode, int tags_count, int all_tags_count, int elements_count, enum etd_spec spec) {
	asn1p_expr_t *terminal;
	int using_type_name = 0;
	char *p = MKID(expr);

	terminal = asn1f_find_terminal_type_ex(arg->asn, expr);

	if(emit_member_PER_constraints(arg, expr, "type"))
		return -1;

	if(HIDE_INNER_DEFS)
		OUT("static\n");
	OUT("asn_TYPE_descriptor_t asn_DEF_%s", p);
	if(HIDE_INNER_DEFS) OUT("_%d", expr->_type_unique_index);
	OUT(" = {\n");
	INDENT(+1);

		if(expr->_anonymous_type) {
			p = ASN_EXPR_TYPE2STR(expr->expr_type);
			OUT("\"%s\",\n", p?p:"");
			OUT("\"%s\",\n",
				p ? asn1c_make_identifier(AMI_CHECK_RESERVED,
					0, p, (char*)0) : "");
		} else {
			OUT("\"%s\",\n", expr->Identifier);
			OUT("\"%s\",\n", expr->Identifier);
		}

		if(expr->expr_type & ASN_CONSTR_MASK) {
			using_type_name = 1;
			p = asn1c_type_name(arg, arg->expr, TNF_SAFE);
		} else {
			p = MKID(expr);
		}

#define FUNCREF(foo)	do {				\
	OUT("%s", p);					\
	if(HIDE_INNER_DEFS && !using_type_name)		\
		OUT("_%d", expr->_type_unique_index);	\
	OUT("_" #foo ",\n");				\
} while(0)

		//OUT("0,//"); FUNCREF(free);
    FUNCREF(print);
    if (!(arg->flags & A1C_NO_CONSTRAINTS) &&
            expr->constraints && (ASN_CONSTR_SET_OF == expr->expr_type || 
                                    ASN_CONSTR_SEQUENCE_OF == expr->expr_type)) 
    {
      p = MKID(expr);
      int temp = using_type_name;
      using_type_name = 0;
      FUNCREF(constraint);
      using_type_name = temp;
      p = asn1c_type_name(arg, arg->expr, TNF_SAFE);
    } else {
      if(arg->flags & A1C_NO_CONSTRAINTS) {
        OUT("0,\t/* No check because of -fno-constraints */\n");
      } else {
        FUNCREF(constraint);
      }
    }
		FUNCREF(decode_ber);
    FUNCREF(encode_der);
    ++arg->ignore_code;
		OUT("0,//"); FUNCREF(decode_xer);
		OUT("0,//"); FUNCREF(encode_xer);
		if(arg->flags & A1C_GEN_PER) {
			OUT("0,//"); FUNCREF(decode_uper);
			OUT("0,//"); FUNCREF(encode_uper);
		} else {
			OUT("0, 0,\t/* No PER support, "
				"use \"-gen-PER\" to enable */\n");
		}
    --arg->ignore_code;

		if(!terminal || terminal->expr_type == ASN_CONSTR_CHOICE) {
		//if(expr->expr_type == ASN_CONSTR_CHOICE) {
			OUT("CHOICE_outmost_tag,\n");
		} else {
			OUT("0,\t/* Use generic outmost tag fetcher */\n");
		}

		p = MKID(expr);
		if(tags_count) {
			OUT("asn_DEF_%s_tags_%d,\n",
				p, expr->_type_unique_index);
			OUT("sizeof(asn_DEF_%s_tags_%d)\n",
				p, expr->_type_unique_index);
			OUT("\t/sizeof(asn_DEF_%s_tags_%d[0])",
				p, expr->_type_unique_index);
			if(tv_mode == _TVM_SUBSET
			&& tags_count != all_tags_count)
				OUT(" - %d", all_tags_count - tags_count);
			OUT(", /* %d */\n", tags_count);
		} else {
			OUT("0,\t/* No effective tags (pointer) */\n");
			OUT("0,\t/* No effective tags (count) */\n");
		}

		if(all_tags_count && tv_mode == _TVM_DIFFERENT) {
			OUT("asn_DEF_%s_all_tags_%d,\n",
				p, expr->_type_unique_index);
			OUT("sizeof(asn_DEF_%s_all_tags_%d)\n",
				p, expr->_type_unique_index);
			OUT("\t/sizeof(asn_DEF_%s_all_tags_%d[0]), /* %d */\n",
				p, expr->_type_unique_index, all_tags_count);
		} else if(all_tags_count) {
			OUT("asn_DEF_%s_tags_%d,\t/* Same as above */\n",
				p, expr->_type_unique_index);
			OUT("sizeof(asn_DEF_%s_tags_%d)\n",
				p, expr->_type_unique_index);
			OUT("\t/sizeof(asn_DEF_%s_tags_%d[0]), /* %d */\n",
				p, expr->_type_unique_index, all_tags_count);
		} else {
			OUT("0,\t/* No tags (pointer) */\n");
			OUT("0,\t/* No tags (count) */\n");
		}
    
    ++arg->ignore_code;
		if(arg->flags & A1C_GEN_PER) {
			if(expr->constraints
			|| expr->expr_type == ASN_BASIC_ENUMERATED
			|| expr->expr_type == ASN_CONSTR_CHOICE) {
				OUT("&asn_PER_type_%s_constr_%d,\n",
					p, expr->_type_unique_index);
			} else {
				OUT("0,\t/* No PER visible constraints */\n");
			}
		} else {
			OUT("0,\t/* No PER visible constraints */\n");
		}
    --arg->ignore_code;

		if(elements_count) {
			OUT("asn_MBR_%s_%d,\n", p, expr->_type_unique_index);
			if(expr->expr_type == ASN_CONSTR_SEQUENCE_OF
			|| expr->expr_type == ASN_CONSTR_SET_OF) {
				OUT("%d,\t/* Single element */\n",
					elements_count);
				assert(elements_count == 1);
			} else {
				OUT("%d,\t/* Elements count */\n",
					elements_count);
			}
		} else {
			if(expr_elements_count(arg, expr))
				OUT("0, 0,\t/* Defined elsewhere */\n");
			else
				OUT("0, 0,\t/* No members */\n");
		}

		switch(spec) {
		case ETD_NO_SPECIFICS:
			OUT("0\t/* No specifics */\n");
			break;
		case ETD_HAS_SPECIFICS:
      if (expr->expr_type == ASN_CONSTR_SEQUENCE_OF || 
              expr->expr_type == ASN_CONSTR_SET_OF)
      {
        OUT("0");
      } else {
        OUT("&asn_SPC_%s_specs_%d",
          p, expr->_type_unique_index);
      }
      OUT("\t/* Additional specs */\n");
		}
	INDENT(-1);
	OUT("};\n");
	OUT("\n");

	return 0;
}

static int
expr_as_xmlvaluelist(arg_t *arg, asn1p_expr_t *expr) {
	/*
	 * X.680, 25.5, Table 5
	 */
	switch(expr_get_type(arg, expr)) {
	case ASN_BASIC_BOOLEAN:
	case ASN_BASIC_ENUMERATED:
	case ASN_BASIC_NULL:
		return 1;
	case ASN_CONSTR_CHOICE:
		return 2;
	default:
		return 0;
	}
}

static int
out_name_chain(arg_t *arg, enum onc_flags onc_flags) {
	asn1p_expr_t *expr = arg->expr;
	char *id;

	assert(expr->Identifier);

	if(( (arg->flags & A1C_COMPOUND_NAMES && !(onc_flags & ONC_force_no_compound_name))
	   || onc_flags & ONC_force_compound_name)
	&& ((expr->expr_type & ASN_CONSTR_MASK)
	   || expr->expr_type == ASN_BASIC_ENUMERATED
	   || ((expr->expr_type == ASN_BASIC_INTEGER
	   	|| expr->expr_type == ASN_BASIC_BIT_STRING)
		&& expr_elements_count(arg, expr))
	   )
	&& expr->parent_expr
	&& expr->parent_expr->Identifier) {
		arg_t tmparg = *arg;

		tmparg.expr = expr->parent_expr;
		if(0) tmparg.flags &= ~A1C_COMPOUND_NAMES;

		out_name_chain(&tmparg, onc_flags);

		OUT("__");	/* a separator between id components */

		/* Fall through */
	}

	if(onc_flags & ONC_avoid_keywords)
		id = MKID_safe(expr);
	else
		id = MKID(expr);
	OUT("%s", id);

	return 0;
}

static void
emit_class_dependency(arg_t* arg, asn1p_expr_t *expr) {
  if (!(arg->flags & A1C_NO_NAMESPACE)) {
    char* temp = asn1c_make_namespace_name(arg, expr, 1);
    char* namespace_name = malloc(strlen(temp) + 1);
    if (!namespace_name) {
      FATAL("Unable to allocate memory for namespace name in emit_class_dependency");
    } else {
      strcpy(namespace_name, temp);
      OUT("namespace %s { class %s; }\n", 
              namespace_name, 
              asn1c_type_name(arg, expr, TNF_RSAFE));
      free(namespace_name);
    }
  } else {
    OUT("class %s;\n", asn1c_type_name(arg, expr, TNF_RSAFE));
  }
}

static int
emit_include_dependencies(arg_t *arg) {
	asn1p_expr_t *expr = arg->expr;
	asn1p_expr_t *memb;
  
	/* Avoid recursive definitions. */
	TQ_FOR(memb, &(expr->members), next) {
		expr_break_recursion(arg, memb);
	}

	TQ_FOR(memb, &(expr->members), next) {

		if(memb->marker.flags & (EM_INDIRECT | EM_UNRECURSE)) {
			if(terminal_structable(arg, memb)) {
				int saved_target = arg->target->target;
				REDIR(OT_FWD_DECLS);
        emit_class_dependency(arg, memb);
				REDIR(saved_target);
			}
		}
    
    if((!(memb->expr_type & ASN_CONSTR_MASK)
      && memb->expr_type > ASN_CONSTR_MASK)
    || memb->meta_type == AMT_TYPEREF) {
      if(memb->marker.flags & EM_UNRECURSE) {
        if (!IS_SINGLE_UNIT(arg)) {
          GEN_POSTINCLUDE(asn1c_type_name(arg,
            memb, TNF_INCLUDE));
        }
      } else {
        char* typename = asn1c_type_name(arg, memb, TNF_INCLUDE);
        if (typename) {
          GEN_INCLUDE(typename);
        }
      }
    }
	}

	return 0;
}

/*
 * Check if it is better to make this type indirectly accessed via
 * a pointer.
 * This may be the case for the following recursive definition:
 * Type ::= CHOICE { member Type };
 */
static int
expr_break_recursion(arg_t *arg, asn1p_expr_t *expr) {
	int ret;

	if(expr->marker.flags & EM_UNRECURSE)
		return 1;	/* Already broken */

	/* -fdirect-choice compiles members of CHOICE as direct members */
	if(!(arg->flags & A1C_DIRECT_CHOICE)
	 && arg->expr->expr_type == ASN_CONSTR_CHOICE
	 && (expr_get_type(arg, expr) & ASN_CONSTR_MASK)
	) {
		/* Break cross-reference */
		expr->marker.flags |= EM_INDIRECT | EM_UNRECURSE;
		return 1;
	}

	if((expr->marker.flags & EM_INDIRECT)
	|| arg->expr->expr_type == ASN_CONSTR_SET_OF
	|| arg->expr->expr_type == ASN_CONSTR_SEQUENCE_OF) {
		if(terminal_structable(arg, expr)) {
			expr->marker.flags |= EM_UNRECURSE;

			if(arg->expr->expr_type == ASN_CONSTR_SET_OF
			|| arg->expr->expr_type == ASN_CONSTR_SEQUENCE_OF) {
				/* Don't put EM_INDIRECT even if recursion */
				return 1;
			}

			/* Fall through */
		}
	}

	/* Look for recursive back-references */
	ret = expr_defined_recursively(arg, expr);
	switch(ret) {
	case 2: /* Explicitly break the recursion */
	case 1: /* Use safer typing */
		expr->marker.flags |= EM_INDIRECT;
		expr->marker.flags |= EM_UNRECURSE;
		break;
	}

	return 0;
}

/*
 * Check if the type can be represented using simple `struct TYPE`.
 */
static asn1p_expr_t *
terminal_structable(arg_t *arg, asn1p_expr_t *expr) {
	asn1p_expr_t *terminal = asn1f_find_terminal_type_ex(arg->asn, expr);
	if(terminal
	&& !terminal->parent_expr
	&& (terminal->expr_type & ASN_CONSTR_MASK)) {
		return terminal;
	}
	return 0;
}

static int
asn1c_recurse(arg_t *arg, asn1p_expr_t *expr, int (*callback)(arg_t *arg, void *key), void *key) {
	arg_t tmp = *arg;
	int maxret = 0;
	int ret;

	if(expr->_mark) return 0;
	expr->_mark |= TM_RECURSION;

	/* Invoke callback for every type going into recursion */
	tmp.expr = expr;
	maxret = callback(&tmp, key);
	if(maxret <= 1) {
		/*
		 * Recursively invoke myself and the callbacks.
		 */
		TQ_FOR(tmp.expr, &(expr->members), next) {
			ret = asn1c_recurse(&tmp, tmp.expr, callback, key);
			if(ret > maxret)
				maxret = ret;
			if(maxret > 1) break;
		}
	}

	expr->_mark &= ~TM_RECURSION;
	return maxret;
}

static int
check_is_refer_to(arg_t *arg, void *key) {
	asn1p_expr_t *terminal = terminal_structable(arg, arg->expr);
	if(terminal == key) {
		if(arg->expr->marker.flags & EM_INDIRECT)
			return 1; /* This is almost safe indirection */
		return 2;
	} else if(terminal) {
		/* This might be N-step circular loop. Dive into it. */
		return asn1c_recurse(arg, terminal, check_is_refer_to, key);
	}
	return 0;
}

/*
 * Check if the possibly inner expression defined recursively.
 */
static int
expr_defined_recursively(arg_t *arg, asn1p_expr_t *expr) {
	asn1p_expr_t *terminal;
	asn1p_expr_t *topmost;

	/* If expression is top-level, there's no way it can be recursive. */
	if(expr->parent_expr == 0) return 0;
	if(expr->expr_type != A1TC_REFERENCE)
		return 0;	/* Basic types are never recursive */

	terminal = terminal_structable(arg, expr);
	if(!terminal) return 0;	/* Terminal cannot be indirected */

	/* Search for the parent container for the given expression */
	topmost = expr;
	while(topmost->parent_expr)
		topmost = topmost->parent_expr;

	/* Look inside the terminal type if it mentions the parent expression */
	return asn1c_recurse(arg, terminal, check_is_refer_to, topmost);
}

struct canonical_map_element {
	int eidx;
	asn1p_expr_t *expr;
};
static int compar_cameo(const void *ap, const void *bp);
static arg_t *cameo_arg;
static int *
compute_canonical_members_order(arg_t *arg, int el_count) {
	struct canonical_map_element *cmap;
	int *rmap;
	asn1p_expr_t *v;
	int eidx = 0;
	int ext_start = -1;
	int nextmax = -1;
	int already_sorted = 1;

	cmap = calloc(el_count, sizeof *cmap);
	assert(cmap);

	TQ_FOR(v, &(arg->expr->members), next) {
		if(v->expr_type != A1TC_EXTENSIBLE) {
			cmap[eidx].eidx = eidx;
			cmap[eidx].expr = v;
			eidx++;
		} else if(ext_start == -1)
			ext_start = eidx;
	}

	cameo_arg = arg;
	if(ext_start == -1) {
		/* Sort the whole thing */
		qsort(cmap, el_count, sizeof(*cmap), compar_cameo);
	} else {
		/* Sort root and extensions independently */
		qsort(cmap, ext_start, sizeof(*cmap), compar_cameo);
		qsort(cmap + ext_start, el_count - ext_start,
			sizeof(*cmap), compar_cameo);
	}

	/* move data back to a simpler map */
	rmap = calloc(el_count, sizeof *rmap);
	assert(rmap);
	for(eidx = 0; eidx < el_count; eidx++) {
		rmap[eidx] = cmap[eidx].eidx;
		if(rmap[eidx] <= nextmax)
			already_sorted = 0;
		else
			nextmax = rmap[eidx];
	}
	free(cmap);

	if(already_sorted) { free(rmap); rmap = 0; }
	return rmap;
}
static int compar_cameo(const void *ap, const void *bp) {
	const struct canonical_map_element *a = (const void *)ap;
	const struct canonical_map_element *b = (const void *)bp;
	struct asn1p_type_tag_s atag, btag;
	arg_t *arg = cameo_arg;

	if(asn1f_fetch_outmost_tag(arg->asn, a->expr->module, a->expr,
			&atag, AFT_IMAGINARY_ANY | AFT_CANON_CHOICE))
		return 1;

	if(asn1f_fetch_outmost_tag(arg->asn, b->expr->module, b->expr,
			&btag, AFT_IMAGINARY_ANY | AFT_CANON_CHOICE))
		return -1;

	if(atag.tag_class < btag.tag_class)
		return -1;
	if(atag.tag_class > btag.tag_class)
		return 1;
	if(atag.tag_value < btag.tag_value)
		return -1;
	if(atag.tag_value > btag.tag_value)
		return 1;
	return 0;

}
