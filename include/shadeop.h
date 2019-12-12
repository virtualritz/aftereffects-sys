/******************************************************************************/
/*                                                                            */
/*    Copyright (c)The 3Delight Developers.                                   */
/*    All Rights Reserved.                                                    */
/*                                                                            */
/******************************************************************************/
 
// ===========================================================================
// = LIBRARY
//     shaderCompiler
// = FILENAME
//     shadeop.h
// = VERSION
//     $ $
// = DATE RELEASED
//     $Date$
// = RCSID
//     $Id$
// ===========================================================================

#ifndef __shadeop_H
#define __shadeop_H

#include "dlInterface.h"

#include <string.h>
#include <stdlib.h>

/****************************************************************************
 * How to use this file.
 *
 * This file must be included when we define a shadeop in a DSO.
 *
 * The macro SHADEOP_TABLE creates a table describing the functions 
 * defined in the DSO.  
 *
 * The macro SHADEOP_INIT creates the prototype of the initialization
 * function.
 *
 * The macro SHADEOP creates the prototype of the method function
 *
 * The macro SHADEOP_CLEANUP creates the prototype of the cleanup function.
 *
 *
 * See also end of file for an exemple.
 ****************************************************************************/


/****************************************************************************
  Struct SHADEOP_STRUCT
****************************************************************************/

typedef struct _SHADEOP_SPEC {
	const char *declaration;          /* if zero length string, end of table signaled. */
	const char *initfunctionname;     /* optional */
	const char *cleanupfunctionname;  /* optional */
} SHADEOP_SPEC;


/****************************************************************************
   Macro SHADEOP_TABLE
****************************************************************************/

#define SHADEOP_TABLE(SHADEOP)   SHADEOP_SPEC _3DL_EXPORT SHADEOP ## _shadeops[]


/****************************************************************************
   Macro SHADEOP_INIT
****************************************************************************/

#define SHADEOP_INIT(FUNC)       void _3DL_EXPORT *FUNC(void)


/****************************************************************************
   Macro SHADEOP
****************************************************************************/

#define SHADEOP(FUNC)            int _3DL_EXPORT FUNC(void *initdata, int argc, void **argv)


/****************************************************************************
   Macro SHADEOP_CLEANUP
****************************************************************************/

#define SHADEOP_CLEANUP(FUNC)    void _3DL_EXPORT FUNC(void *initdata)


/****************************************************************************
   Macro ASSIGN_STRING

   For affectations to strings. Requires linking with lib3delight on windows
   and OS X. Migrate to the RslPlugin API and use the RixTokenStorage interface
   if you must avoid that.
*****************************************************************************/

_3DL_EXTERN_C DL_INTERFACE char* RslGetToken( const char *i_token );
#define ASSIGN_STRING(VAR, S)    { (VAR) = RslGetToken(S); }

/****************************************************************************
   Structure STRING_DESC

   For compatibility, to help people see TheLight and get out of the dark ;-)
*****************************************************************************/
typedef struct
{
	char *s;
} STRING_DESC;

#endif

