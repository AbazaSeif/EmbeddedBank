/*
	rsa_def.h - RSAEURO types and constants

    Copyright (c) J.S.A.Kapp 1994 - 1996.

	RSAEURO - RSA Library compatible with RSAREF 2.0.

	All functions prototypes are the Same as for RSAREF.
	To aid compatiblity the source and the files follow the
	same naming comventions that RSAREF uses.  This should aid
	direct importing to your applications.

	This library is legal everywhere outside the US.  And should
	NOT be imported to the US and used there.

	Global types and contants file.

	Revision 1.00 - JSAK.
*/

#ifndef _RSA_DEF_H_
#define _RSA_DEF_H_

/* PROTOTYPES should be set to one if and only if the compiler supports
		 function argument prototyping.
	 The following makes PROTOTYPES default to 1 if it has not already been
		 defined as 0 with C compiler flags. */

#ifndef PROTOTYPES
    #define PROTOTYPES 1
#endif

typedef unsigned char *POINTER; /* POINTER defines a generic pointer type */
typedef unsigned short UINT2;   /* UINT2 defines a two byte word          */
typedef unsigned long  UINT4;   /* UINT4 defines a four byte word         */
#ifndef UINT
    #define UINT unsigned int   /* UINT  defines two/four byte word       */
#endif
#ifndef BYTE
    #define BYTE unsigned char  /* BYTE  defines a unsigned_char          */
#endif

#ifndef NULL_PTR
    #define NULL_PTR ((POINTER)0)
#endif

#ifndef UNUSED_ARG
    #define UNUSED_ARG(x) x = *(&x);
#endif

/* PROTO_LIST is defined depending on how PROTOTYPES is defined above.
  If using PROTOTYPES, then PROTO_LIST returns the list, otherwise it
  returns an empty list. */

#if PROTOTYPES
    #define PROTO_LIST(list) list
#else
    #define PROTO_LIST(list) ()
#endif

#endif /* _GLOBAL_H_ */
