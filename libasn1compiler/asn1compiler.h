#ifndef	ASN1_COMPILER_H
#define	ASN1_COMPILER_H

#include <asn1parser.h>

enum asn1c_flags {
	A1C_NOFLAGS,
	/*
	 * Debug the compiler.
	 */
	A1C_DEBUG		= 0x0001,
	/*
	 * Do not split the target output in several files, just print it.
	 * (Note: the output is not likely to be compilable in this case).
	 */
	A1C_PRINT_COMPILED	= 0x0002,
	/*
	 * Generate only the tables for ASN.1 types,
	 * do not emit ASN.1 parsing support code.
	 */
	A1C_OMIT_SUPPORT_CODE	= 0x0004,
	/*
	 * Use wide types by default (INTEGER_t etc) instead of native/long.
	 */
	A1C_USE_WIDE_TYPES	= 0x0008,
	/*
	 * Do not use C99 extensions.
	 */
	A1C_NO_C99		= 0x0010,
	/*
	 * Do not generate constraint checking code.
	 */
	A1C_NO_CONSTRAINTS	= 0x0080,
	/*
	 * Generate type_id_PR_member things identifiers of id_PR_member.
	 */
	A1C_COMPOUND_NAMES	= 0x0100,
	/*
	 * Do not generate courtesy #includes for external dependencies.
	 */
	A1C_NO_INCLUDE_DEPS	= 0x0200,
	/*
	 * Compile members of CHOICE as direct members.
	 */
	A1C_DIRECT_CHOICE	= 0x0400,
	/*
	 * -flink-skeletons
	 * Symlink support files rather than copy them.
	 */
	A1C_LINK_SKELETONS	= 0x0800,
	/*
	 * -gen-PER
	 * Generate PER support code
	 */
	A1C_GEN_PER			= 0x1000,
	/*
	 * -pdu={all|auto|Type}
	 * Generate PDU table
	 */
	A1C_PDU_ALL			= 0x2000,
	A1C_PDU_AUTO		= 0x4000,
	A1C_PDU_TYPE		= 0x8000,
	/*
	 * -fincludes-quoted
	 * Avoid generating #include <foo>, generate "foo" instead.
	 */
	A1C_INCLUDES_QUOTED	= 0x10000,
  /*
	 * -fline-refs
	 * Include ASN.1 module's line numbers in comments.
	 */
	A1C_LINE_REFS       = 0x20000,
  /*
   * -fno-namespace
   * Avoid generating namespace name.
   */
  A1C_NO_NAMESPACE    = 0x40000,
  /*
   * -finsecure-pointers
   * Use raw pointers instead of smart (safe) pointers.
   */
  A1C_INSECURE_POINTERS    = 0x80000,
  /*
   * -fno-switch
   * Use member tables instead of switch for getting pointer to member by index.
   */
  A1C_NO_SWITCH            = 0x100000,
  /*
   * -fptr-choice-getters
   * Use pointers instead of references as return types of getters of classes for CHOICE.
   */
  A1C_PTR_CHOICE_GETTERS            = 0x200000,
  /*
   * -fshort-ifdef
   * Use short form (without module name) of #ifdef directive in *.hpp files.
   */
  A1C_SHORT_IFDEF            = 0x400000,
  /*
   * -fsingle-unit
   * Generate single translation unit for entire ASN.1-file instead of generating a translation unit for each type in ASN.1-file.
   */
  A1C_SINGLE_UNIT            = 0x800000
};

/*
 * Compile the ASN.1 specification.
 */
int asn1_compile(asn1p_t *asn, const char *datadir, enum asn1c_flags,
	int argc, int optc, char **argv);

void asn1c__add_pdu_type(const char *typename);

#endif	/* ASN1_COMPILER_H */
