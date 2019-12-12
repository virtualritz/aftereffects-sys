/******************************************************************************/
/*                                                                            */
/*    Copyright (c)The 3Delight Developers.                                   */
/*    All Rights Reserved.                                                    */
/*                                                                            */
/******************************************************************************/

// ===========================================================================
// = LIBRARY
//     3delight
// = FILENAME
//     delight.h
// = AUTHOR(S)
//     Patrick Fournier
// = VERSION
//     $Revision$
// = DATE RELEASED
//     $Date$
// = RCSID
//     $Id$
// ===========================================================================


#ifndef __delight_H
#define __delight_H

#include "dlInterface.h"

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

DL_INTERFACE const char* DlGetVersionString(); /* 1.1.1a (Jan 01 2000) */
DL_INTERFACE const char* DlGetLibNameAndVersionString(); /* 3DeLight 1.1.1a (Jan 01 2000) */
DL_INTERFACE const char* DlGetCopyrightString(); /* Copyright (c) 1999-2007 The 3Delight Team. */

DL_INTERFACE int DlIsFreeLibrary(); /* 1 if this is free, thread-limited lib, 0 otherwise. */

/*
	As a convenience, i_output[i_output_size] is set to zero so i_output can be
	handled as a string.
*/
typedef void (*DlJobFinishedCallback)(
	void *i_cbdata, int i_status,
	unsigned i_output_size, const char *i_output );

DL_INTERFACE void DlStartBatchJob( const char *i_command, void *i_cbdata, int i_max_jobs );
DL_INTERFACE void DlWaitForBatchJobs( DlJobFinishedCallback i_callback );


/*
	Communicate progress information to the user via a JSON-encoded string.
*/
DL_INTERFACE int DlProgress(int i_handle, const char* i_info);

#ifdef __cplusplus
}
#endif

#endif // __delight_HH

