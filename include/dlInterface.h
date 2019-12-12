/******************************************************************************/
/*                                                                            */
/*    Copyright (c)The 3Delight Developers.                                   */
/*    All Rights Reserved.                                                    */
/*                                                                            */
/******************************************************************************/

/*
	LIBRARY
	  3delight
	FILENAME
	  dlInterface.h
	AUTHOR(S)
	  Marco Jacques
	VERSION
	  $Revision$
	DATE RELEASED
	  $Date$
	RCSID
	  $Id$
	COPYRIGHT
	  Copyright © 1999-2000 The 3Delight Developers.
	  All Rights Reserved.
*/

/*
	This will be included for files which must import or export symbol from the
	3DL library.  It will avoid having the required definitions scattered at
	differents places
*/

#ifndef __dlInterface_H
#define __dlInterface_H

/*
	Macro DL_INTERFACE

	This macro prefixes, in header files, functions and variables which are
	exported from the 3Delight library.

	On unix systems, it uses the gcc visibility attribute to ensure the symbol
	is exported even if the code is built with -fvisibility=hidden.

	On Windows, it needs to add __declspec(dllexport) when building the library
	(ie. exporting the symbol). When using the symbol from somewhere else (ie.
	linking against lib3delight), it should instead add __declspec(dllimport).
	Unlike dllexport, dllimport is optional and will only improve call
	performance.
*/

#ifdef _WIN32
#	define _3DL_ALWAYS_IMPORT __declspec(dllimport)
#	define _3DL_ALWAYS_EXPORT __declspec(dllexport)
#else
#	define _3DL_ALWAYS_IMPORT
#	if __GNUC__ >= 4
#		define _3DL_ALWAYS_EXPORT __attribute__ ((visibility("default")))
#	else
#		define _3DL_ALWAYS_EXPORT
#	endif
#endif

#ifdef STATIC_3DELIGHT
#	define _3DL_IMPORT
#	define _3DL_EXPORT
#else
#	define _3DL_IMPORT _3DL_ALWAYS_IMPORT
#	define _3DL_EXPORT _3DL_ALWAYS_EXPORT
#endif

#if defined(BUILDING_3DELIGHT) && !defined(LINKING_WITH_3DELIGHT)
#define DL_INTERFACE _3DL_EXPORT
#else
#define DL_INTERFACE _3DL_IMPORT
#endif

/*
	Macro DL_EXPORT_VAR

	This macro is used only in cpp files for exporting variables.
*/

#define _3DL_EXPORT_VAR _3DL_EXPORT

/*
	Macro _3DL_EXTERN_C

	Use to declare functions with C calling convention in headers which might
	be compiled as both C or C++.
*/
#ifdef  __cplusplus
#define _3DL_EXTERN_C extern "C"
#else
#define _3DL_EXTERN_C
#endif

#endif

