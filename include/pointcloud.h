/******************************************************************************/
/*                                                                            */
/*    Copyright (c)The 3Delight Developers.                                   */
/*    All Rights Reserved.                                                    */
/*                                                                            */
/******************************************************************************/

#ifndef __pointcloud_h
#define __pointcloud_h

#include "dlInterface.h"

#ifdef  __cplusplus
extern "C" {
#endif

typedef void *PtcPointCloud;

DL_INTERFACE extern PtcPointCloud PtcSafeOpenPointCloudFile(
		const char *filename );
DL_INTERFACE extern PtcPointCloud PtcOpenPointCloudFile(
		const char *filename, int *nvars, const char **vartypes, const char **varnames );
DL_INTERFACE extern PtcPointCloud PtcCreatePointCloudFile(
	const char *i_filename, int i_nvars,
	const char * const*i_vartypes, const char * const*i_varnames,
	float *i_world2eye, float *i_world2ndc, float *i_format );

DL_INTERFACE extern int PtcGetPointCloudInfo(
	PtcPointCloud pointcloud, const char *request, void *result );
DL_INTERFACE extern int PtcReadDataPoint(
	PtcPointCloud pointcloud, 
	float *point, float *normal, float *radius, float *data );
DL_INTERFACE extern int PtcWriteDataPoint( PtcPointCloud i_pointcloud,
	const float *i_point, const float *i_normal, float i_radius, const float *i_data );

DL_INTERFACE extern void PtcClosePointCloudFile( PtcPointCloud );
DL_INTERFACE extern void PtcFinishPointCloudFile( PtcPointCloud );

#ifdef  __cplusplus
}
#endif

#endif
