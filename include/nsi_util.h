#ifndef __nsi_util_h
#define __nsi_util_h

#include "nsi.h"

#ifdef  __cplusplus
extern "C" {
#endif

DL_INTERFACE void NSIParseTypeString(
	const char *type_string,
	NSIParam_t *result );

DL_INTERFACE int NSITypeToString(
	const NSIParam_t *type,
	unsigned result_length,
	char *result );

#ifdef __cplusplus
}
#endif

#endif

