/******************************************************************************/
/*                                                                            */
/*    Copyright (c)The 3Delight Developers.                                   */
/*    All Rights Reserved.                                                    */
/*                                                                            */
/*    These coded instructions, statements, and computer programs  contain    */
/*    unpublished  proprietary and  confidential information of  Centre de    */
/*    traitement  en  imagerie virtuelle inc. (CTIV), and are protected by    */
/*    Federal copyright law. They may not be disclosed to third parties or    */
/*    or duplicated in any form, in whole or in  part, without  the  prior    */
/*    written consent of CTIV.                                                */
/*                                                                            */
/******************************************************************************/

// ===========================================================================
// = LIBRARY
//     3delight
// = FILENAME
//     rx.h
// = AUTHOR(S)
//     Charles De Lean
// = VERSION
//     $Revision$
// = DATE RELEASED
//     $Date$
// = RCSID
//     $Id$
// ===========================================================================

#ifndef __dlRX_H
#define __dlRX_H

#include <ri.h>
#include <dlInterface.h>

#ifdef  __cplusplus
class RixContext;

extern "C" {

/*
	To obtain the global RixContext which gives access to some of the
	interfaces also available to a RslPlugin.
*/
DL_INTERFACE extern RixContext* RxGetRixContext();
#endif

/*
	Public (DSO) interface for noise.
*/

DL_INTERFACE extern RtInt RxNoise(
	RtInt i_inDimension,
	RtFloat *i_in,
	RtInt i_outDimension,
	RtFloat *o_out);

DL_INTERFACE extern RtInt RxPNoise(
	RtInt i_inDimension,
	RtFloat *i_in,
	RtFloat *i_period,
	RtInt i_outDimension,
	RtFloat *o_out);

DL_INTERFACE extern RtInt RxCellNoise(
	RtInt i_inDimension,
	RtFloat *i_in,
	RtInt i_outDimension,
	RtFloat *o_out);

/*
	Public (DSO) interface for textures.
*/

/*
	Single point environment lookup. This is deprecated. Use the multi point
	version whenever possible.
*/
DL_INTERFACE extern RtInt RxEnvironmentV(
	RtString i_fileName,
	RtInt i_firstChannel,
	RtInt i_nChannels,
	RtPoint i_dir0,
	RtPoint i_dir1,
	RtPoint i_dir2,
	RtPoint i_dir3,
	RtFloat *o_result,
	RtInt i_n,
	RtToken i_tokens[],
	RtPointer i_parms[]);

DL_INTERFACE extern RtInt RxEnvironment(
	RtString i_fileName,
	RtInt i_firstChannel,
	RtInt i_nChannels,
	RtPoint i_dir0,
	RtPoint i_dir1,
	RtPoint i_dir2,
	RtPoint i_dir3,
	RtFloat *o_result,
	...);

/*
	Multi point environment lookup with single direction vector.

	This will do proper filtering if called from a Rsl plugin over all points
	at once. Otherwise it falls back on RxEnvironmentPoints4 with the same
	direction duplicated (ie. no filtering).
*/
DL_INTERFACE extern RtInt RxEnvironmentPoints1V(
	RtString i_fileName,
	RtInt i_nPoints,
	RtInt i_firstChannel,
	RtInt i_nChannels,
	const RtPoint *i_dir,
	RtFloat *o_result,
	RtInt i_n,
	RtToken i_tokens[],
	RtPointer i_params[] );

DL_INTERFACE extern RtInt RxEnvironmentPoints1(
	RtString i_fileName,
	RtInt i_nPoints,
	RtInt i_firstChannel,
	RtInt i_nChannels,
	const RtPoint *i_dir,
	RtFloat *o_result,
	... );

/*
	Multi point environment lookup with 4 direction vectors as the corners of
	the lookup area.
*/
DL_INTERFACE extern RtInt RxEnvironmentPoints4V(
	RtString i_fileName,
	RtInt i_nPoints,
	RtInt i_firstChannel,
	RtInt i_nChannels,
	const RtPoint *i_dir0,
	const RtPoint *i_dir1,
	const RtPoint *i_dir2,
	const RtPoint *i_dir3,
	RtFloat *o_result,
	RtInt i_n,
	RtToken i_tokens[],
	RtPointer i_params[] );

DL_INTERFACE extern RtInt RxEnvironmentPoints4(
	RtString i_fileName,
	RtInt i_nPoints,
	RtInt i_firstChannel,
	RtInt i_nChannels,
	const RtPoint *i_dir0,
	const RtPoint *i_dir1,
	const RtPoint *i_dir2,
	const RtPoint *i_dir3,
	RtFloat *o_result,
	... );

/*
	Single point shadow lookup. This is deprecated. Use the multi point version
	whenever possible.
*/
DL_INTERFACE extern RtInt RxShadowV(
	RtString i_fileName,
	RtInt i_firstChannel,
	RtPoint i_P0,
	RtPoint i_P1,
	RtPoint i_P2,
	RtPoint i_P3,
	RtFloat *o_result,
	RtInt i_n,
	RtToken i_tokens[],
	RtPointer i_parms[]);

DL_INTERFACE extern RtInt RxShadow(
	RtString i_fileName,
	RtInt i_firstChannel,           
	RtPoint i_P0,
	RtPoint i_P1,
	RtPoint i_P2,
	RtPoint i_P3,
	RtFloat *o_result,
	...);

/*
	Multi point shadow lookup with single position.

	This will do proper filtering if called from a Rsl plugin over all points
	at once. Otherwise it falls back on RxShadowPoints4 with the same point
	duplicated (ie. no filtering).
*/
DL_INTERFACE extern RtInt RxShadowPoints1V(
	RtString i_fileName,
	RtInt i_nPoints,
	RtInt i_firstChannel,
	const RtPoint *i_P,
	RtFloat *o_result,
	RtInt i_n,
	RtToken i_tokens[],
	RtPointer i_params[] );

DL_INTERFACE extern RtInt RxShadowPoints1(
	RtString i_fileName,
	RtInt i_nPoints,
	RtInt i_firstChannel,
	const RtPoint *i_P,
	RtFloat *o_result,
	... );

/*
	Multi point shadow lookup with 4 positions as the corners of the lookup
	area.
*/
DL_INTERFACE extern RtInt RxShadowPoints4V(
	RtString i_fileName,
	RtInt i_nPoints,
	RtInt i_firstChannel,
	const RtPoint *i_P0,
	const RtPoint *i_P1,
	const RtPoint *i_P2,
	const RtPoint *i_P3,
	RtFloat *o_result,
	RtInt i_n,
	RtToken i_tokens[],
	RtPointer i_params[] );

DL_INTERFACE extern RtInt RxShadowPoints4(
	RtString i_fileName,
	RtInt i_nPoints,
	RtInt i_firstChannel,           
	const RtPoint *i_P0,
	const RtPoint *i_P1,
	const RtPoint *i_P2,
	const RtPoint *i_P3,
	RtFloat *o_result,
	... );

/*
	Single point texture lookup. This is deprecated. Use the multi point
	version whenever possible.
*/
DL_INTERFACE extern RtInt RxTextureV(
	RtString i_fileName,
	RtInt i_firstChannel,
	RtInt i_nChannels,
	RtFloat i_s0,
	RtFloat i_t0,
	RtFloat i_s1,
	RtFloat i_t1,
	RtFloat i_s2,
	RtFloat i_t2,
	RtFloat i_s3,
	RtFloat i_t3,
	RtFloat *o_result,
	RtInt i_n,
	RtToken i_tokens[],
	RtPointer i_parms[]);

DL_INTERFACE extern RtInt RxTexture(
	RtString i_fileName,
	RtInt i_firstChannel,
	RtInt i_nChannels,
	RtFloat i_s0,
	RtFloat i_t0,
	RtFloat i_s1,
	RtFloat i_t1,
	RtFloat i_s2,
	RtFloat i_t2,
	RtFloat i_s3,
	RtFloat i_t3,
	RtFloat *o_result,
	...);

/*
	Multi point texture lookup with simple (s,t) pair.

	This will do proper filtering if called from a Rsl plugin over all points
	at once. Otherwise it falls back on RxTexturePoints4 with the same (s,t)
	duplicated (ie. no filtering).
*/
DL_INTERFACE extern RtInt RxTexturePoints1V(
	RtString i_fileName,
	RtInt i_nPoints,
	RtInt i_firstChannel,
	RtInt i_nChannels,
	const RtFloat *i_s,
	const RtFloat *i_t,
	RtFloat *o_result,
	RtInt i_n,
	RtToken i_tokens[],
	RtPointer i_params[] );

DL_INTERFACE extern RtInt RxTexturePoints1(
	RtString i_fileName,
	RtInt i_nPoints,
	RtInt i_firstChannel,
	RtInt i_nChannels,
	const RtFloat *i_s,
	const RtFloat *i_t,
	RtFloat *o_result,
	... );

/*
	Multi point texture lookup with 4 (s,t) pairs as the corners of the lookup
	area.
*/
DL_INTERFACE extern RtInt RxTexturePoints4V(
	RtString i_fileName,
	RtInt i_nPoints,
	RtInt i_firstChannel,
	RtInt i_nChannels,
	const RtFloat *i_s0,
	const RtFloat *i_t0,
	const RtFloat *i_s1,
	const RtFloat *i_t1,
	const RtFloat *i_s2,
	const RtFloat *i_t2,
	const RtFloat *i_s3,
	const RtFloat *i_t3,
	RtFloat *o_result,
	RtInt i_n,
	RtToken i_tokens[],
	RtPointer i_params[] );

DL_INTERFACE extern RtInt RxTexturePoints4(
	RtString i_fileName,
	RtInt i_nPoints,
	RtInt i_firstChannel,
	RtInt i_nChannels,
	const RtFloat *i_s0,
	const RtFloat *i_t0,
	const RtFloat *i_s1,
	const RtFloat *i_t1,
	const RtFloat *i_s2,
	const RtFloat *i_t2,
	const RtFloat *i_s3,
	const RtFloat *i_t3,
	RtFloat *o_result,
	... );

/*
	The following are just wrappers for compatibility. They all call the
	equivalent 'Points4' version so there's no need to use them in new code.
*/
DL_INTERFACE extern RtInt RxEnvironmentPointsV( RtString i_fileName, RtInt i_nPoints, RtInt i_firstChannel, RtInt i_nChannels, RtFloat *i_dir0, RtFloat *i_dir1, RtFloat *i_dir2, RtFloat *i_dir3, RtFloat *o_result, RtInt i_n, RtToken i_tokens[], RtPointer i_params[] );
DL_INTERFACE extern RtInt RxEnvironmentPoints( RtString i_fileName, RtInt i_nPoints, RtInt i_firstChannel, RtInt i_nChannels, RtFloat *i_dir0, RtFloat *i_dir1, RtFloat *i_dir2, RtFloat *i_dir3, RtFloat *o_result, ... );
DL_INTERFACE extern RtInt RxShadowPointsV( RtString i_fileName, RtInt i_nPoints, RtInt i_firstChannel, RtFloat *i_P0, RtFloat *i_P1, RtFloat *i_P2, RtFloat *i_P3, RtFloat *o_result, RtInt i_n, RtToken i_tokens[], RtPointer i_params[] );
DL_INTERFACE extern RtInt RxShadowPoints( RtString i_fileName, RtInt i_nPoints, RtInt i_firstChannel, RtFloat *i_P0, RtFloat *i_P1, RtFloat *i_P2, RtFloat *i_P3, RtFloat *o_result, ... );
DL_INTERFACE extern RtInt RxTexturePointsV( RtString i_fileName, RtInt i_nPoints, RtInt i_firstChannel, RtInt i_nChannels, RtFloat *i_s0, RtFloat *i_t0, RtFloat *i_s1, RtFloat *i_t1, RtFloat *i_s2, RtFloat *i_t2, RtFloat *i_s3, RtFloat *i_t3, RtFloat *o_result, RtInt i_n, RtToken i_tokens[], RtPointer i_params[] );
DL_INTERFACE extern RtInt RxTexturePoints( RtString i_fileName, RtInt i_nPoints, RtInt i_firstChannel, RtInt i_nChannels, RtFloat *i_s0, RtFloat *i_t0, RtFloat *i_s1, RtFloat *i_t1, RtFloat *i_s2, RtFloat *i_t2, RtFloat *i_s3, RtFloat *i_t3, RtFloat *o_result, ... );

/*
	Public (DSO) interface for information retrieval.

	RxAttribute, RxOption, and RxRendererInfo return the
	current values of the named Attribute or Option.

	The caller passes in a buffer and it is filled-in with the
	resulting requested info.  Return value is 0 on success, or
	-1 if name can't be found, or N if the supplied buffer was
	too short and needs to be at least N bytes long.  Caller
	supplies the addresses of several other return values which
	are filled in:  resulttype is the RxInfoType_t of the values
	put into the result buffer, and resultcount is the number of
	those (multibyte) items.
*/

typedef enum
{
	RxInfoFloat,
	RxInfoInteger,
	RxInfoStringV,
	RxInfoColor,
	RxInfoNormal,
	RxInfoVector,
	RxInfoPoint,
	RxInfoHPoint,
	RxInfoMPoint,
	RxInfoMatrix
} RxInfoType_t;

DL_INTERFACE extern RtInt RxAttribute (
	RtString i_name,
	RtPointer o_result, 
	RtInt i_resultLen,
	RxInfoType_t *o_resulttype,
	RtInt *o_resultcount);

DL_INTERFACE extern RtInt RxOption (
	RtString i_name,
	RtPointer o_result,
	RtInt i_resultLen,
	RxInfoType_t *o_resulttype,
	RtInt *o_resultcount);

DL_INTERFACE extern RtInt RxRendererInfo (
	RtString i_name,
	RtPointer o_result,
	RtInt i_resultLen, 
	RxInfoType_t *o_resulttype,
	RtInt *o_resultcount);

DL_INTERFACE extern RtInt RxTextureInfo (
	RtString i_texture,
	RtString i_name,
	RtPointer o_result,
	RtInt i_resultLen, 
	RxInfoType_t *o_resulttype,
	RtInt *o_resultcount);

/*
	Public (DSO) interface for point transformation.
*/

DL_INTERFACE extern RtInt RxTransformPoints(
	RtToken i_fromspace,
	RtToken i_tospace,
	RtInt i_n,
	RtPoint io_p[],
	RtFloat i_time);

DL_INTERFACE extern RtInt RxTransform(
	RtToken i_fromspace,
	RtToken i_tospace,
	RtFloat i_time,
	RtMatrix o_matrix );

/*
	Public (DSO) interface for file caching.
*/
DL_INTERFACE extern RtString RxCacheFile(
	RtString i_filename);

/*
	Public (DSO) interface for locating files.

	PARAMETERS

	i_category
		One of "shader", "texture", "display", "archive", "procedural",
		"resource" to specify which searchpaths to use for finding the file.

		"none" can also be specified to use none of the searchpaths but still
		apply dirmap resolution if the path is an absolute path.

	i_filename
		The name of the file to find.

	RETURNS
		A string which is the full path to the first copy of the file found. If
		the file was not found, NULL is returned.

	NOTES
		The "dirmap" option is also applied to the returned path.
*/
DL_INTERFACE extern const char* RxFindFile(
	const char *i_category,
	const char *i_filename );

/*
	Public interface for the random() shadeop.

	This returns the same pseudorandom values as would the random() shadeop. It
	currently only works inside a RslPlugin or dso shadeop. In other contexts,
	it will return 0.
*/
DL_INTERFACE extern float RxRandom();

/*
	RxAborting

	Returns 1 if the render is aborting and 0 otherwise. In the aborting case,
	plugins should return as quickly as possible to speed up the shaders.
*/
DL_INTERFACE extern int RxAborting();

#ifdef  __cplusplus
}
#endif

#endif /* ndef __dlRX_H */
