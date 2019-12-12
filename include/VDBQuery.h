#ifndef __VDBQuery_h
#define __VDBQuery_h

#include "dlInterface.h"

#ifdef  __cplusplus
extern "C" {
#endif

/*
	This returns the world space bounding box of the given file. It is written
	to bbox as: xmin ymin zmin xmax ymax zmax
*/
DL_INTERFACE bool DlVDBGetFileBBox(
	const char *filename,
	double *bbox );

DL_INTERFACE bool DlVDBGetGridNames(
	const char *filename,
	int *num_grids,
	const char *const **grid_names );

DL_INTERFACE void DlVDBFreeGridNames(
	const char *const *grid_names );

#ifdef __cplusplus
}
#endif

#endif
