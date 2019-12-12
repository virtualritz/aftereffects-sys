/******************************************************************************/
/*                                                                            */
/*    Copyright (c)The 3Delight Developers.                                   */
/*    All Rights Reserved.                                                    */
/*                                                                            */
/******************************************************************************/

#ifndef __rif_H
#define __rif_H

#include "dlInterface.h"

#include <stdarg.h>
#include <string.h>

class RifPlugin;

/* */
typedef enum
{
	k_RifRIB, k_RifRenderer
} RifEmbedding;

typedef enum
{
	k_RifFloat=0, k_RifPoint, k_RifColor,  k_RifInteger,
	k_RifString, k_RifVector, k_RifNormal, k_RifHPoint,
	k_RifMatrix, k_RifMPoint
} RifTokenType;

typedef enum
{
	k_RifConstant=0, k_RifUniform, k_RifVarying, k_RifVertex, k_RifFaceVarying, k_RifFaceVertex
} RifTokenDetail;

typedef enum {
	k_RifParseNextLayer,
	k_RifParseThisLayer, 
	k_RifParseFirstLayer
} RifParseMode;

/* Define our plugin factory entry point */
#ifdef  __cplusplus
extern "C" {
#endif

/* These functions should be prensent in the Ri filter */
_3DL_EXPORT RifPlugin *RifPluginManufacture( int argc, char **argv );
_3DL_EXPORT RtVoid RifPluginDelete( RifPlugin * );

/* These functions are provided by the renderer */
DL_INTERFACE RifPlugin *RifLoadPlugin(
	const char *i_name, int i_argc, const char **i_argv );
DL_INTERFACE RtVoid RifUnloadPlugins( void );
DL_INTERFACE RtVoid RifAddPlugin( RifPlugin *i_plugin );
DL_INTERFACE RtVoid RifRemovePlugin( RifPlugin *i_plugin );

DL_INTERFACE RifPlugin *RifGetCurrentPlugin();
DL_INTERFACE RifEmbedding RifGetEmbedding(); 
DL_INTERFACE RtInt RifGetDeclaration(
	RtToken i_token, RifTokenType *, RifTokenDetail *, RtInt *o_array_len);
/*
	Returns the token's name or null upon failure.
	eg. "vertex float foo" -> "foo", "P" -> "P", etc
	Do not delete the returned string.
*/
DL_INTERFACE RtString RifGetTokenName( RtToken i_token );

DL_INTERFACE RtVoid RifGetChainInfo(RtInt *o_current, RtInt *o_total );
DL_INTERFACE RtVoid RifParseFile(const char *i_filename, RifParseMode i_mode );
DL_INTERFACE RtVoid RifParseBuffer(const char *i_buf, unsigned i_size, RifParseMode i_mode );  
#ifdef  __cplusplus
}
#endif

struct RifFilter
{
	enum
	{
		k_UnknownVersion = 0,
		k_CurrentVersion = 1
	};

	enum
	{
		k_Continue = 1,
		k_Terminate = 2
	} DefaultFiltering;

	int Filtering;
	short Version;
	void *ClientData;
	char Reserved[64];

	RifFilter()
	{
		memset( this, 0, sizeof(RifFilter) );
		Version = k_CurrentVersion;
		Filtering = k_Continue;
	}

	/* Transforms */
	RtVoid (*Perspective)(RtFloat fov);
	RtVoid (*ConcatTransform)(RtMatrix transform);
	RtVoid (*CoordinateSystem)(RtToken space);
	RtVoid (*ScopedCoordinateSystem)(RtToken space);
	RtVoid (*CoordSysTransform)(RtToken space);
	RtVoid (*Identity)(void);
	RtVoid (*Transform)(RtMatrix transform);
	RtVoid (*TransformBegin)(void);
	RtVoid (*TransformEnd)(void);
	RtVoid (*Translate)(RtFloat dx, RtFloat dy, RtFloat dz);
	RtPoint *(*TransformPoints)( RtToken fromspace, RtToken tospace, RtInt n, RtPoint points[]);
	RtVoid (*Rotate)( RtFloat angle, RtFloat dx, RtFloat dy, RtFloat dz);
	RtVoid (*Scale)(RtFloat dx, RtFloat dy, RtFloat dz);
	RtVoid (*Skew)(
		RtFloat angle,
		RtFloat dx1, RtFloat dy1, RtFloat dz1,
		RtFloat dx2, RtFloat dy2, RtFloat dz2);

	/* Attributes */
	RtVoid (*AttributeBegin)(void);
	RtVoid (*AttributeEnd)( void );
	RtVoid (*AttributeV)(
		RtToken name, RtInt n, RtToken tokens[], RtPointer parms[] );
	RtVoid (*MultiplyShadingRate)(RtFloat ratemultiplier);
	RtVoid (*ShadingRate)(RtFloat size);
	RtVoid (*ShadingInterpolation)(RtToken type);
	RtVoid (*Bound)( RtBound bound );
	RtVoid (*Color)( RtColor color );
	RtVoid (*Opacity)(RtColor color);
	RtVoid (*Matte)(RtBoolean onoff);
	RtVoid (*ReverseOrientation)(void);
	RtVoid (*TextureCoordinates)(
		RtFloat s1, RtFloat t1,
		RtFloat s2, RtFloat t2,
		RtFloat s3, RtFloat t3,
		RtFloat s4, RtFloat t4);

	RtVoid (*Sides)(RtInt sides);
	RtToken (*Declare)(char *name, char *declaration);

	RtVoid (*Basis)(RtBasis ubasis, RtInt ustep, RtBasis vbasis, RtInt vstep);
	RtVoid (*Detail)(RtBound bound);
	RtVoid (*DetailRange)(RtFloat minvisible,
		RtFloat lowertransition,
		RtFloat uppertransition,
		RtFloat maxvisible);
	RtVoid (*GeometricApproximation)(RtToken type, RtFloat value);
	RtVoid (*Orientation)(RtToken orientation);
	RtVoid (*RelativeDetail)(RtFloat relativedetail);
	RtVoid (*Illuminate)( RtLightHandle light, RtBoolean onoff);

	RtLightHandle (*LightSourceV)(
		RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]);
	RtLightHandle (*AreaLightSourceV)(
		RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]);
	RtVoid (*AtmosphereV)(
		RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]);
	RtVoid (*ImagerV)(
		RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]);
	RtVoid (*DeformationV)(
		RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]);
	RtVoid (*DisplacementV)(
		RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]);
	RtVoid (*ExteriorV)(
		RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]);
	RtVoid (*InteriorV)(
		RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]);
	RtVoid (*SurfaceV)(
		RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]);
	RtVoid (*ShaderV)(
		RtToken name, RtToken handle, RtInt n, RtToken tokens[], RtPointer parms[]);
	/* Conditional RIB */
	RtVoid (*IfBeginV)(RtToken expression, RtInt n, RtToken tokens[], RtPointer params[]);
	RtVoid (*ElseIfV)(RtToken expression, RtInt n, RtToken tokens[], RtPointer params[]);
	RtVoid (*Else)(void);
	RtVoid (*IfEnd)(void);

	/* Options */
	RtVoid (*OptionV)(RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]);
	RtVoid (*HiderV)(
			RtToken type, RtInt n, RtToken tokens[],
			RtPointer parms[]);
	RtVoid (*DisplayV)(
		char *name, RtToken type, RtToken mode,
		RtInt n, RtToken tokens[],
		RtPointer parms[] );
	RtVoid (*DisplayChannelV)(
		char *channel, RtInt n, RtToken tokens[], RtPointer params[]);
	RtVoid (*Exposure)(RtFloat gain, RtFloat gamma);
	RtVoid (*FrameAspectRatio)(RtFloat aspect);
	RtVoid (*ScreenWindow)( RtFloat left, RtFloat right, RtFloat bottom, RtFloat top);
	RtVoid (*Clipping)(RtFloat hither, RtFloat yon);
	RtVoid (*ClippingPlane)(
		RtFloat x, RtFloat y, RtFloat z,
		RtFloat nx, RtFloat ny, RtFloat nz );
	RtVoid (*DepthOfField)(
		RtFloat fstop, RtFloat focallength, RtFloat focaldistance);
	RtVoid (*Shutter)(RtFloat min, RtFloat max);
	RtVoid (*ProjectionV)(
		RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]);
	RtVoid (*CameraV)(
		RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]);
	RtVoid (*PixelFilter)(RtFilterFunc filterfunc, RtFloat xwidth, RtFloat ywidth);
	RtVoid (*PixelSamples)(RtFloat xsamples, RtFloat ysamples);
	RtVoid (*PixelVariance)(RtFloat variation);
	RtVoid (*Quantize)(RtToken type, RtInt one, RtInt min, RtInt max, RtFloat ampl);
	RtVoid (*CropWindow)(
		RtFloat left, RtFloat right, RtFloat top, RtFloat bottom );

	RtVoid (*Format)( RtInt xres, RtInt yres, RtFloat aspect );
	RtVoid (*ColorSamples)(RtInt n, RtFloat nRGB[], RtFloat RGBn[]);

	/* Procedurals */
	RtVoid (*ProcDelayedReadArchive)( RtPointer data, RtFloat detail);
	RtVoid (*ProcDynamicLoad)(RtPointer data, RtFloat detail);
	RtVoid (*ProcRunProgram)(RtPointer data, RtFloat detail);
	RtVoid (*ProcFree)(RtPointer data);
	union {
	RtVoid (*Procedural)(
		RtPointer i_data, RtBound i_bound,
		RtVoid (*i_Subdivfunc)(RtPointer, RtFloat),
		RtVoid (*i_Freefunc)(RtPointer));
	RtVoid (*ProceduralV)(
		RtPointer i_data, RtBound i_bound,
		RtVoid (*i_Subdivfunc)(RtPointer, RtFloat),
		RtVoid (*i_Freefunc)(RtPointer),
		RtInt n, RtToken tokens[], RtPointer parms[]);
	};
	/* Geometry */
	RtVoid (*GeometryV)(RtToken type, RtInt n, RtToken tokens[], RtPointer parms[]);
	RtVoid (*PatchV)(RtToken type, RtInt n,
		RtToken tokens[], RtPointer parms[]);
	RtVoid (*PatchMeshV)(RtToken type, RtInt nu, RtToken uwrap,
		RtInt nv, RtToken vwrap, RtInt n,
		RtToken tokens[], RtPointer parms[]);
	RtVoid (*PointsV)(RtInt npoints, RtInt n,
		RtToken tokens[], RtPointer parms[]);
	RtVoid (*CurvesV)(RtToken type, RtInt ncurves,
		RtInt nvertices[], RtToken wrap,
		RtInt n, RtToken tokens[],
		RtPointer parms[]);
	RtVoid (*NuCurvesV)(
		RtInt ncurves, RtInt nvertices[],
		RtInt order[], RtFloat knot[],
		RtFloat min[], RtFloat max[],
		RtInt n, RtToken tokens[],
		RtPointer params[]);
	RtVoid (*NuPatchV)(
		RtInt nu, RtInt uorder, RtFloat uknot[],
		RtFloat umin, RtFloat umax,
		RtInt nv, RtInt vorder, RtFloat vknot[],
		RtFloat vmin, RtFloat vmax, RtInt n,
		RtToken tokens[], RtPointer parms[]);
	RtVoid (*TrimCurve)(
		RtInt nloops, RtInt ncurves[],
		RtInt order[], RtFloat knot[],
		RtFloat min[], RtFloat max[], RtInt n[],
		RtFloat u[], RtFloat v[], RtFloat w[]);
	RtVoid (*SubdivisionMeshV)(RtToken scheme,
		RtInt nfaces, RtInt nvertices[], RtInt vertices[],
		RtInt ntags, RtToken tags[], RtInt nargs[],
		RtInt intargs[], RtFloat floatargs[],
		RtInt n, RtToken tokens[], RtPointer parms[]);

	RtVoid (*HierarchicalSubdivisionMeshV)(
		RtToken scheme,
		RtInt nfaces, RtInt nvertices[], RtInt vertices[],
		RtInt ntags, RtToken tags[], RtInt nargs[],
		RtInt intargs[], RtFloat floatargs[], RtToken stringargs[],
		RtInt n, RtToken tokens[], RtPointer params[]);

	RtVoid (*ConeV)(RtFloat height, RtFloat radius,
		RtFloat thetamax, RtInt n,
		RtToken tokens[], RtPointer parms[]);
	RtVoid (*CylinderV)(RtFloat radius,RtFloat zmin,RtFloat zmax,
		RtFloat thetamax, RtInt n,
		RtToken tokens[], RtPointer parms[]);
	RtVoid (*DiskV)(RtFloat height, RtFloat radius,
		RtFloat thetamax, RtInt n,
		RtToken tokens[], RtPointer parms[]);
	RtVoid (*HyperboloidV)(RtPoint point1, RtPoint point2,
		RtFloat thetamax, RtInt n,
		RtToken tokens[], RtPointer parms[]);
	RtVoid (*ParaboloidV)(RtFloat rmax,RtFloat zmin,RtFloat zmax,
		RtFloat thetamax, RtInt n,
		RtToken tokens[], RtPointer parms[]);
	RtVoid (*SphereV)(RtFloat radius,RtFloat zmin,RtFloat zmax,
		RtFloat thetamax, RtInt n,
		RtToken tokens[], RtPointer parms[]);
	RtVoid (*TorusV)(RtFloat majorradius, RtFloat minorradius,
		RtFloat phimin, RtFloat phimax,
		RtFloat thetamax, RtInt n,
		RtToken tokens[], RtPointer parms[]);
	RtVoid (*GeneralPolygonV)(RtInt nloops, RtInt nvertices[],
		RtInt n, RtToken tokens[],
		RtPointer parms[]);
	RtVoid (*BlobbyV)(
		RtInt nleaf,
		RtInt nentry, RtInt entry[],
		RtInt nfloat, RtFloat floats[],
		RtInt nstring, RtString strings[],
		RtInt n, RtToken tokens[], RtPointer parms[]);
	RtVoid (*PointsGeneralPolygonsV)(RtInt npolys, RtInt nloops[],
		RtInt nvertices[],
		RtInt vertices[],
		RtInt n, RtToken tokens[],
		RtPointer parms[]);
	RtVoid (*PointsPolygonsV)(RtInt npolys, RtInt nvertices[],
		RtInt vertices[],
		RtInt n, RtToken tokens[],
		RtPointer parms[]);
	RtVoid (*PolygonV)(RtInt nvertices,
		RtInt n, RtToken tokens[],
		RtPointer parms[]);
	RtVoid (*ObjectInstance)(RtObjectHandle handle);

	/* Blocks */
	RtVoid (*WorldBegin)(void);
	RtVoid (*WorldEnd)(void);
	RtVoid (*Begin)(RtToken name);
	RtVoid (*End)(void);
	RtVoid (*Context)(RtContextHandle handle);
	RtVoid (*FrameBegin)(RtInt frame);
	RtVoid (*FrameEnd)(void);
	RtVoid (*MotionBeginV)(RtInt n, RtFloat times[]);
	RtVoid (*MotionEnd)(void);
	RtVoid (*SolidBegin)(RtToken operation);
	RtVoid (*SolidEnd)(void);
	union
	{
		/*
			ObjectBeginV should be used as it receives the handle read from the
			RIB in a "__handleid" string parameter. This must be the handle
			used by the object (and recognized later by ObjectInstance).

			ObjectBegin generates its own handle which will not match what the
			RIB parser will later pass to ObjectInstance.
		*/
		RtObjectHandle (*ObjectBegin)( void );
		RtObjectHandle (*ObjectBeginV)(
			RtInt n, __RI_CONST RtToken tokens[], RtPointer params[]);
	};
	RtVoid (*ObjectEnd)(void);
	RtVoid (*ResourceBegin)(void);
	RtVoid (*ResourceEnd)(void);
	RtArchiveHandle (*ArchiveBeginV)(
		RtToken archivename, RtInt n,
		RtToken tokens[], RtPointer params[]);
	RtVoid (*ArchiveEnd)(void);

	/* Map making */
	RtVoid (*MakeShadowV)(
		char *i_picturename, char *i_texturename,
		RtInt n, RtToken tokens[], RtPointer parms[] );
	RtVoid (*MakeTextureV)(
		char *i_picturename, char *i_texturename, RtToken i_swrap,
		RtToken i_twrap, RtFilterFunc i_filterfunc,
		RtFloat i_swidth, RtFloat i_twidth,
		RtInt i_n, RtToken i_tokens[], RtPointer i_parms[] );
	RtVoid (*MakeCubeFaceEnvironmentV)(
		char *i_px, char *i_nx,
		char *i_py, char *i_ny,
		char *i_pz, char *i_nz,
		char *i_texturename,
		RtFloat i_fov,
		RtFilterFunc i_filterfunc,
		RtFloat i_swidth, RtFloat i_twidth,
		RtInt i_n, RtToken i_tokens[], RtPointer i_parms[] );
	RtVoid (*MakeLatLongEnvironmentV)(
		char *i_picturename, char *i_texturename,
		RtFilterFunc i_filterfunc, RtFloat i_swidth, RtFloat i_twidth,
		RtInt i_n, RtToken i_tokens[], RtPointer i_parms[] );
	RtVoid (*MakeBrickMapV)(
		RtInt nptc, char **ptcnames, char *bkmname,
		RtInt n, RtToken tokens[], RtPointer params[] );
	RtVoid (*MakeBumpV)(
		char *picturename, char *texturename,
		RtToken swrap, RtToken twrap,
		RtFilterFunc filterfunc,
		RtFloat swidth, RtFloat twidth,
		RtInt n, RtToken tokens[],
		RtPointer parms[] );

	/* Other */
	RtFloat (*BoxFilter)(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth);
	RtFloat (*TriangleFilter)(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth);
	RtFloat (*CatmullRomFilter)(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth);
	RtFloat (*BesselFilter)(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth);
	RtFloat (*GaussianFilter)(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth);
	RtFloat (*SincFilter)(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth);
	RtFloat (*BlackmanHarrisFilter)(
		RtFloat i_x, RtFloat i_y, RtFloat i_filterXWidth, RtFloat i_filteryWidth);
	RtFloat (*MitchellFilter)(
		RtFloat i_x, RtFloat i_y, RtFloat i_filterXWidth, RtFloat i_filteryWidth);

	RtVoid (*ReadArchiveV)(
		RtToken name, RtVoid (*callback)(RtToken, const char*, ...),
		RtInt n, RtToken tokens[], RtPointer parms[]);
	RtContextHandle (*GetContext)(void);
	RtVoid (*ResourceV)(
		RtToken handle, RtToken type,
		RtInt n, RtToken tokens[], RtPointer params[]);

	/* A special form for ArchiveRecord ... */
	RtVoid (*VArchiveRecord)( RtToken i_type, __RI_CONST char *format, va_list v);
};

/*
	This abstract class defines one Rif Filter. The renderer is able to chain
	many such filters.
*/
class RifPlugin
{
public:

	virtual ~RifPlugin() {}
	
	/*
		GetFilter
		
		Returns the RifFilter associated with this plugin. A RifFilters defines
		which Ri calls are 
	*/
	virtual RifFilter &GetFilter() = 0;
};

#endif
