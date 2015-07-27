
SUBDIRS = . tests

dist_pkgdata_DATA =				\
		$(srcdir)/README		\
		$(srcdir)/*.cpp                 \
		$(srcdir)/*.hpp                 \
		$(srcdir)/file-dependencies

uninstall-local:
	-@echo -n " "
	-rm -f -r $(DESTDIR)$(pkgdatadir)

smodsdir=$(pkgdatadir)

nobase_dist_smods_DATA =     \
	standard-modules/README  \
	standard-modules/ASN1-Object-Identifier-Module.asn1 \
	standard-modules/ASN1C-UsefulInformationObjectClasses.asn1

check_LTLIBRARIES = libasn1cskeletons.la

libasn1cskeletons_la_CFLAGS = $(TESTSUITE_CFLAGS)
libasn1cskeletons_la_CXXFLAGS = $(TESTSUITE_CFLAGS) -std=c++11
libasn1cskeletons_la_SOURCES = 				\
	ANY.cpp \
	ANY.hpp \
	AsnAbstractType.hpp \
	AsnAbstractType.cpp \
	asn_application.hpp \
	AsnNativePrimitiveType.hpp \
	asn_codecs.hpp \
	asn_codecs_prim.hpp \
	asn_internal.cpp \
	asn_internal.hpp \
	asn_system.hpp \
	ber_decoder.cpp \
	ber_decoder.hpp \
	ber_tlv_length.cpp \
	ber_tlv_length.hpp \
	ber_tlv_tag.cpp \
	ber_tlv_tag.hpp \
	BIT_STRING.cpp \
	BIT_STRING.hpp \
	BMPString.cpp \
	BMPString.hpp \
	BOOLEAN.cpp \
	BOOLEAN.hpp \
	constraints.cpp \
	constraints.hpp \
	constr_CHOICE.cpp \
	constr_CHOICE.hpp \
	constr_SEQUENCE.cpp \
	constr_SEQUENCE.hpp \
	constr_SEQUENCE_OF.cpp \
	constr_SEQUENCE_OF.hpp \
	constr_SET.cpp \
	constr_SET.hpp \
	constr_SET_OF.cpp \
	constr_SET_OF.hpp \
	constr_TYPE.cpp \
	constr_TYPE.hpp \
	der_encoder.cpp \
	der_encoder.hpp \
	ENUMERATED.cpp \
	ENUMERATED.hpp \
	GeneralizedTime.cpp \
	GeneralizedTime.hpp \
	GeneralString.cpp \
	GeneralString.hpp \
	GraphicString.cpp \
	GraphicString.hpp \
	IA5String.cpp \
	IA5String.hpp \
	INTEGER.cpp \
	INTEGER.hpp \
	ISO646String.cpp \
	ISO646String.hpp \
	NativeEnumerated.cpp \
	NativeEnumerated.hpp \
	NativeInteger.cpp \
	NativeInteger.hpp \
	NativeReal.cpp \
	NativeReal.hpp \
	NULL.cpp \
	NULL.hpp \
	NumericString.cpp \
	NumericString.hpp \
	ObjectDescriptor.cpp \
	ObjectDescriptor.hpp \
	OBJECT_IDENTIFIER.cpp \
	OBJECT_IDENTIFIER.hpp \
	OCTET_STRING.cpp \
	OCTET_STRING.hpp \
	PrintableString.cpp \
	PrintableString.hpp \
	REAL.cpp \
	REAL.hpp \
	RELATIVE-OID.cpp \
	RELATIVE-OID.hpp \
	T61String.cpp \
	T61String.hpp \
	TeletexString.cpp \
	TeletexString.hpp \
	UniversalString.cpp \
	UniversalString.hpp \
	UTCTime.cpp \
	UTCTime.hpp \
	UTF8String.cpp \
	UTF8String.hpp \
	VideotexString.cpp \
	VideotexString.hpp \
	VisibleString.cpp \
	VisibleString.hpp 

