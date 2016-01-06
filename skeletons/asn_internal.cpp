/*
 * Copyright (c) 2014-2016 Dmitriy Chugunov <chugunovdima@gmail.com>. All rights reserved.
 * Redistribution and modifications are permitted subject to BSD license.
 */

#include "asn_internal.hpp"

#if	EMIT_ASN_DEBUG == 1	/* And it was asked to emit this code... */
#ifdef	__GNUC__
#ifdef	ASN_THREAD_SAFE
#else	/* !ASN_THREAD_SAFE */
#undef  ASN_DEBUG_INDENT_ADD
#undef  asn_debug_indent
int asn_debug_indent;
#endif	/* ASN_THREAD_SAFE */
#else	/* !__GNUC__ */
#endif	/* __GNUC__ */
#else	/* EMIT_ASN_DEBUG != 1 */
#endif	/* EMIT_ASN_DEBUG */
