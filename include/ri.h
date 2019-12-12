/******************************************************************************/
/*                                                                            */
/*    Copyright (c)The 3Delight Developers.                                   */
/*    All Rights Reserved.                                                    */
/*                                                                            */
/******************************************************************************/

/*
	The RenderMan (R) Interface Procedures and RIB Protocol are:
	Copyright 1988, 1989, Pixar.  All rights reserved.
	RenderMan (R) is a registered trademark of Pixar.
*/
#ifndef __ri_h
#define __ri_h

#include "dlInterface.h"

#define __RI_ANSI 1

/* Define to nothing if you have issues with our use of const. */
#ifndef __RI_CONST
#define __RI_CONST const
#endif

#ifdef  __cplusplus
extern "C" {
#endif

/* ===========================================================================
    Type definitions
   =========================================================================*/

typedef short RtBoolean;
typedef float RtFloat;

/* Define RtInt as a 32 bit signed integer */
typedef int RtInt;

typedef __RI_CONST char *RtToken;

typedef RtFloat RtColor[3];
typedef RtFloat RtPoint[3];
typedef RtFloat RtVector[3];
typedef RtFloat RtNormal[3];
typedef RtFloat RtHpoint[4];
typedef RtFloat RtMatrix[4][4];
typedef RtFloat RtBasis[4][4];
typedef RtFloat RtBound[6];          /* [xmin xmax ymin ymax zmin zmax] */
typedef RtFloat RtInterval[2];
typedef __RI_CONST char *RtString;

typedef void *RtPointer;

#define RtVoid void

typedef RtFloat (*RtFilterFunc)(RtFloat, RtFloat, RtFloat, RtFloat);
typedef RtVoid  (*RtErrorHandler)(RtInt, RtInt, __RI_CONST char *);

typedef RtVoid (*RtProcSubdivFunc)(RtPointer, RtFloat);
typedef RtVoid (*RtProcFreeFunc)(RtPointer);
typedef RtVoid (*RtArchiveCallback)(RtToken, __RI_CONST char *, ...);

typedef RtPointer RtObjectHandle;
typedef RtPointer RtLightHandle;
typedef RtPointer RtContextHandle;
typedef RtPointer RtArchiveHandle;
typedef RtPointer RtVolumeHandle;


/* ===========================================================================
    Constant definitions
   =========================================================================*/

#define RI_FALSE        0
#define RI_TRUE         (!RI_FALSE)
#define RI_INFINITY     1.0e38f
#define RI_EPSILON      1.0e-10f
#define RI_NULL         ((char*)0)


/* ===========================================================================
    Standard token definitions
   =========================================================================*/

extern DL_INTERFACE RtToken RI_FRAMEBUFFER;
extern DL_INTERFACE RtToken RI_FILE;
extern DL_INTERFACE RtToken RI_ZFILE;

extern DL_INTERFACE RtToken RI_RGB;
extern DL_INTERFACE RtToken RI_RGBA;
extern DL_INTERFACE RtToken RI_RGBZ;
extern DL_INTERFACE RtToken RI_RGBAZ;
extern DL_INTERFACE RtToken RI_A;
extern DL_INTERFACE RtToken RI_Z;
extern DL_INTERFACE RtToken RI_AZ;

extern DL_INTERFACE RtToken RI_PERSPECTIVE;
extern DL_INTERFACE RtToken RI_ORTHOGRAPHIC;

extern DL_INTERFACE RtToken RI_HIDDEN;
extern DL_INTERFACE RtToken RI_PAINT;
extern DL_INTERFACE RtToken RI_RAYTRACE;
extern DL_INTERFACE RtToken RI_PHOTON;

extern DL_INTERFACE RtToken RI_CONSTANT;
extern DL_INTERFACE RtToken RI_SMOOTH;

extern DL_INTERFACE RtToken RI_FLATNESS;
extern DL_INTERFACE RtToken RI_FOV;

extern DL_INTERFACE RtToken RI_AMBIENTLIGHT;
extern DL_INTERFACE RtToken RI_POINTLIGHT;
extern DL_INTERFACE RtToken RI_DISTANTLIGHT;
extern DL_INTERFACE RtToken RI_SPOTLIGHT;

extern DL_INTERFACE RtToken RI_INTENSITY;
extern DL_INTERFACE RtToken RI_LIGHTCOLOR;
extern DL_INTERFACE RtToken RI_FROM;
extern DL_INTERFACE RtToken RI_TO;
extern DL_INTERFACE RtToken RI_CONEANGLE;
extern DL_INTERFACE RtToken RI_CONEDELTAANGLE;
extern DL_INTERFACE RtToken RI_BEAMDISTRIBUTION;

extern DL_INTERFACE RtToken RI_MATTE;
extern DL_INTERFACE RtToken RI_METAL;
extern DL_INTERFACE RtToken RI_SHINYMETAL;
extern DL_INTERFACE RtToken RI_PLASTIC;
extern DL_INTERFACE RtToken RI_PAINTEDPLASTIC;

extern DL_INTERFACE RtToken RI_KA;
extern DL_INTERFACE RtToken RI_KD;
extern DL_INTERFACE RtToken RI_KS;
extern DL_INTERFACE RtToken RI_ROUGHNESS;
extern DL_INTERFACE RtToken RI_KR;
extern DL_INTERFACE RtToken RI_TEXTURENAME;
extern DL_INTERFACE RtToken RI_SPECULARCOLOR;

extern DL_INTERFACE RtToken RI_DEPTHCUE;
extern DL_INTERFACE RtToken RI_FOG;
extern DL_INTERFACE RtToken RI_BUMPY;

extern DL_INTERFACE RtToken RI_MINDISTANCE;
extern DL_INTERFACE RtToken RI_MAXDISTANCE;
extern DL_INTERFACE RtToken RI_BACKGROUND;
extern DL_INTERFACE RtToken RI_DISTANCE;
extern DL_INTERFACE RtToken RI_AMPLITUDE;

extern DL_INTERFACE RtToken RI_RASTER;
extern DL_INTERFACE RtToken RI_SCREEN;
extern DL_INTERFACE RtToken RI_CAMERA;
extern DL_INTERFACE RtToken RI_WORLD;
extern DL_INTERFACE RtToken RI_OBJECT;

extern DL_INTERFACE RtToken RI_INSIDE;
extern DL_INTERFACE RtToken RI_OUTSIDE;
extern DL_INTERFACE RtToken RI_LH;
extern DL_INTERFACE RtToken RI_RH;

extern DL_INTERFACE RtToken RI_P;
extern DL_INTERFACE RtToken RI_PZ;
extern DL_INTERFACE RtToken RI_PW;
extern DL_INTERFACE RtToken RI_N;
extern DL_INTERFACE RtToken RI_NP;
extern DL_INTERFACE RtToken RI_CS;
extern DL_INTERFACE RtToken RI_OS;
extern DL_INTERFACE RtToken RI_S;
extern DL_INTERFACE RtToken RI_T;
extern DL_INTERFACE RtToken RI_ST;

extern DL_INTERFACE RtToken RI_BILINEAR;
extern DL_INTERFACE RtToken RI_BICUBIC;

extern DL_INTERFACE RtToken RI_PRIMITIVE;
extern DL_INTERFACE RtToken RI_INTERSECTION;
extern DL_INTERFACE RtToken RI_UNION;
extern DL_INTERFACE RtToken RI_DIFFERENCE;

extern DL_INTERFACE RtToken RI_PERIODIC;
extern DL_INTERFACE RtToken RI_NONPERIODIC;
extern DL_INTERFACE RtToken RI_CLAMP;
extern DL_INTERFACE RtToken RI_BLACK;

extern DL_INTERFACE RtToken RI_IGNORE;
extern DL_INTERFACE RtToken RI_PRINT;
extern DL_INTERFACE RtToken RI_ABORT;
extern DL_INTERFACE RtToken RI_HANDLER;

extern DL_INTERFACE RtToken RI_BOUNDS;

extern DL_INTERFACE RtToken RI_LIMITS;
extern DL_INTERFACE RtToken RI_SHADOW;
extern DL_INTERFACE RtToken RI_BIAS0;
extern DL_INTERFACE RtToken RI_BIAS1;
extern DL_INTERFACE RtToken RI_SAMPLE;

extern DL_INTERFACE RtToken RI_SEARCHPATH;
extern DL_INTERFACE RtToken RI_SHADER;
extern DL_INTERFACE RtToken RI_TEXTURE;
extern DL_INTERFACE RtToken RI_DISPLAY;

extern DL_INTERFACE RtToken RI_WIDTH, RI_CONSTANTWIDTH;

extern DL_INTERFACE RtToken RI_COMMENT;
extern DL_INTERFACE RtToken RI_STRUCTURE;
extern DL_INTERFACE RtToken RI_VERBATIM;

extern DL_INTERFACE RtToken RI_IDENTIFIER;
extern DL_INTERFACE RtToken RI_NAME;
extern DL_INTERFACE RtToken RI_SHADINGGROUP;

extern DL_INTERFACE RtToken RI_SEARCHPATH;
extern DL_INTERFACE RtToken RI_SHADER;
extern DL_INTERFACE RtToken RI_TEXTURE;

/* ===========================================================================
    Curves
   =========================================================================*/

extern DL_INTERFACE RtToken RI_LINEAR;
extern DL_INTERFACE RtToken RI_CUBIC;

/* ===========================================================================
    3delight tokens declaration
   =========================================================================*/

extern DL_INTERFACE RtToken RI_BUCKETSENDER;
extern DL_INTERFACE RtToken RI_FUNCTION;

extern DL_INTERFACE RtToken RI_THRESHOLD;
extern DL_INTERFACE RtToken RI___THRESHOLD;

extern DL_INTERFACE RtToken RI_HANDLEID;
extern DL_INTERFACE RtToken RI___HANDLEID;

/* ===========================================================================
    Standard display parameters
   =========================================================================*/

extern DL_INTERFACE RtToken RI_QUANTIZE;
extern DL_INTERFACE RtToken RI_DITHER;
extern DL_INTERFACE RtToken RI_EXPOSURE;
extern DL_INTERFACE RtToken RI_FILTER;
extern DL_INTERFACE RtToken RI_FILTERWIDTH;

/* ===========================================================================
    Patch basis stuff
   =========================================================================*/

extern DL_INTERFACE RtBasis RiBezierBasis;
extern DL_INTERFACE RtBasis RiBSplineBasis;
extern DL_INTERFACE RtBasis RiCatmullRomBasis;
extern DL_INTERFACE RtBasis RiHermiteBasis;
extern DL_INTERFACE RtBasis RiPowerBasis;

extern DL_INTERFACE RtInt RI_BEZIERSTEP;
extern DL_INTERFACE RtInt RI_BSPLINESTEP;
extern DL_INTERFACE RtInt RI_CATMULLROMSTEP;
extern DL_INTERFACE RtInt RI_HERMITESTEP;
extern DL_INTERFACE RtInt RI_POWERSTEP;


/* ===========================================================================
    Renderman Interface calls
   =========================================================================*/

DL_INTERFACE RtVoid RiBegin(RtToken name);
DL_INTERFACE RtVoid RiEnd(void);
DL_INTERFACE RtContextHandle RiGetContext(void);
DL_INTERFACE RtVoid RiContext(RtContextHandle handle);
DL_INTERFACE RtVoid RiFrameBegin(RtInt frame);
DL_INTERFACE RtVoid RiFrameEnd(void);
DL_INTERFACE RtVoid RiMotionBegin(RtInt n, ...);
DL_INTERFACE RtVoid RiMotionBeginV(RtInt n, RtFloat times[]);
DL_INTERFACE RtVoid RiMotionEnd(void);
DL_INTERFACE RtVoid RiSolidBegin(RtToken operation);
DL_INTERFACE RtVoid RiSolidEnd(void);
DL_INTERFACE RtVoid RiWorldBegin(void);
DL_INTERFACE RtVoid RiWorldEnd(void);
DL_INTERFACE RtObjectHandle RiObjectBegin( void );
DL_INTERFACE RtObjectHandle RiObjectBeginV(
	RtInt n, __RI_CONST RtToken tokens[], RtPointer params[] );
DL_INTERFACE RtVoid RiObjectEnd(void);
DL_INTERFACE RtVoid RiObjectInstance(RtObjectHandle handle);

DL_INTERFACE RtVoid RiResource(RtToken handle, RtToken type, ...);
DL_INTERFACE RtVoid RiResourceV(
		RtToken handle, RtToken type,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer params[]);
DL_INTERFACE RtVoid RiResourceBegin(void);
DL_INTERFACE RtVoid RiResourceEnd(void);

DL_INTERFACE RtVoid RiFormat(RtInt xres, RtInt yres, RtFloat aspect);
DL_INTERFACE RtVoid RiFrameAspectRatio(RtFloat aspect);
DL_INTERFACE RtVoid RiScreenWindow(RtFloat left, RtFloat right,
								RtFloat bottom, RtFloat top);
DL_INTERFACE RtVoid RiClipping(RtFloat hither, RtFloat yon);
DL_INTERFACE RtVoid RiClippingPlane(
	RtFloat x, RtFloat y, RtFloat z, RtFloat nx, RtFloat ny, RtFloat nz );

DL_INTERFACE RtVoid RiCropWindow(RtFloat xmin, RtFloat xmax,
							  RtFloat ymin, RtFloat ymax);
DL_INTERFACE RtVoid RiDepthOfField(RtFloat fstop, RtFloat focallength,
								RtFloat focaldistance);
DL_INTERFACE RtVoid RiProjection(RtToken name, ...);
DL_INTERFACE RtVoid RiProjectionV(
		RtToken name,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);
DL_INTERFACE RtVoid RiShutter(RtFloat min, RtFloat max);

DL_INTERFACE RtVoid RiCamera(RtToken camera, ...);
DL_INTERFACE RtVoid RiCameraV(
		RtToken camera,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);

DL_INTERFACE RtVoid RiDisplay(
		const char *name, RtToken type, RtToken mode, ...);
DL_INTERFACE RtVoid RiDisplayV(
		const char *name, RtToken type, RtToken mode,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);
DL_INTERFACE RtVoid RiDisplayChannel(const char *channel, ...);
DL_INTERFACE RtVoid RiDisplayChannelV(
		const char *channel,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer params[]);
DL_INTERFACE RtVoid RiExposure(RtFloat gain, RtFloat gamma);
DL_INTERFACE RtVoid RiImager(RtToken name, ...);
DL_INTERFACE RtVoid RiImagerV(
		RtToken name,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);
DL_INTERFACE RtVoid RiPixelFilter(RtFilterFunc filterfunc,
							   RtFloat xwidth, RtFloat ywidth);
DL_INTERFACE RtVoid RiPixelSamples(RtFloat xsamples, RtFloat ysamples);
DL_INTERFACE RtVoid RiPixelVariance(RtFloat variation);
DL_INTERFACE RtVoid RiQuantize(RtToken type, RtInt one, RtInt min,
							RtInt max, RtFloat ampl);

DL_INTERFACE RtVoid RiConcatTransform(RtMatrix transform);
DL_INTERFACE RtVoid RiCoordinateSystem(RtToken space);
DL_INTERFACE RtVoid RiScopedCoordinateSystem(RtToken space);
DL_INTERFACE RtVoid RiCoordSysTransform(RtToken space);
DL_INTERFACE RtVoid RiIdentity(void);
DL_INTERFACE RtVoid RiPerspective(RtFloat fov);
DL_INTERFACE RtVoid RiRotate(RtFloat angle,
						  RtFloat dx, RtFloat dy, RtFloat dz);
DL_INTERFACE RtVoid RiScale(RtFloat dx, RtFloat dy, RtFloat dz);
DL_INTERFACE RtVoid RiSkew(RtFloat angle,
						RtFloat dx1, RtFloat dy1, RtFloat dz1,
						RtFloat dx2, RtFloat dy2, RtFloat dz2);
DL_INTERFACE RtVoid RiTransform(RtMatrix transform);
DL_INTERFACE RtVoid RiTransformBegin(void);
DL_INTERFACE RtVoid RiTransformEnd(void);
DL_INTERFACE RtVoid RiTranslate(RtFloat dx, RtFloat dy, RtFloat dz);
DL_INTERFACE RtPoint* RiTransformPoints(RtToken fromspace,
									 RtToken tospace,
									 RtInt n, RtPoint points[]);

DL_INTERFACE RtVoid RiAtmosphere(RtToken name, ...);
DL_INTERFACE RtVoid RiAtmosphereV(
		RtToken name, RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);
DL_INTERFACE RtVoid RiDeformation(RtToken name, ...);
DL_INTERFACE RtVoid RiDeformationV(
		RtToken name,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);
DL_INTERFACE RtVoid RiDisplacement(RtToken name, ...);
DL_INTERFACE RtVoid RiDisplacementV(
		RtToken name,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);
DL_INTERFACE RtVoid RiExterior(RtToken name, ...);
DL_INTERFACE RtVoid RiExteriorV(
		RtToken name,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);
DL_INTERFACE RtVoid RiIlluminate(RtLightHandle light, RtBoolean onoff);
DL_INTERFACE RtVoid RiInterior(RtToken name, ...);
DL_INTERFACE RtVoid RiInteriorV(
		RtToken name,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);

DL_INTERFACE RtVoid RiShader(RtToken name, RtToken handle, ...);
DL_INTERFACE RtVoid RiShaderV( RtToken name, RtToken handle,
	RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);

DL_INTERFACE RtVoid RiMatte(RtBoolean onoff);
DL_INTERFACE RtVoid RiMultiplyShadingRate(RtFloat ratemultiplier);
DL_INTERFACE RtVoid RiShadingRate(RtFloat size);
DL_INTERFACE RtVoid RiShadingInterpolation(RtToken type);
DL_INTERFACE RtVoid RiSurface(RtToken name, ...);
DL_INTERFACE RtVoid RiSurfaceV(
		RtToken name,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);

DL_INTERFACE RtVoid RiArchiveRecord(RtToken type, __RI_CONST char *format, ...);
DL_INTERFACE RtVoid RiReadArchive(
		RtToken name, RtArchiveCallback callback, ...);
DL_INTERFACE RtVoid RiReadArchiveV(
		RtToken name, RtArchiveCallback callback,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);

DL_INTERFACE RtArchiveHandle RiArchiveBegin(RtToken archivename, ...);
DL_INTERFACE RtArchiveHandle RiArchiveBeginV(
		RtToken archivename,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer params[]);
DL_INTERFACE RtVoid RiArchiveEnd(void);

DL_INTERFACE RtVoid RiIfBegin(RtToken expression, ...);
DL_INTERFACE RtVoid RiIfBeginV(
		RtToken expression,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer params[]);
DL_INTERFACE RtVoid RiElseIf(RtToken expression, ...);
DL_INTERFACE RtVoid RiElseIfV(
		RtToken expression,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer params[]);
DL_INTERFACE RtVoid RiElse(void);
DL_INTERFACE RtVoid RiIfEnd(void);

DL_INTERFACE RtVoid RiAttribute(RtToken name, ...);
DL_INTERFACE RtVoid RiAttributeV(
		RtToken name,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);
DL_INTERFACE RtVoid RiAttributeBegin(void);
DL_INTERFACE RtVoid RiAttributeEnd(void);
DL_INTERFACE RtVoid RiBound( RtBound bound );
DL_INTERFACE RtVoid RiColor( RtColor color );
DL_INTERFACE RtVoid RiOpacity(RtColor color);
DL_INTERFACE RtVoid RiOption(RtToken name, ...);
DL_INTERFACE RtVoid RiOptionV(
		RtToken name,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);
DL_INTERFACE RtVoid RiReverseOrientation(void);
DL_INTERFACE RtVoid RiTextureCoordinates(RtFloat s1, RtFloat t1,
									  RtFloat s2, RtFloat t2,
									  RtFloat s3, RtFloat t3,
									  RtFloat s4, RtFloat t4);
DL_INTERFACE RtVoid RiSides(RtInt sides);

DL_INTERFACE RtToken RiDeclare(const char *name, const char *declaration);

DL_INTERFACE RtLightHandle RiLightSource(RtToken name, ...);
DL_INTERFACE RtLightHandle RiLightSourceV(
		RtToken name,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);

DL_INTERFACE RtLightHandle RiAreaLightSource(RtToken name, ...);
DL_INTERFACE RtLightHandle RiAreaLightSourceV(
		RtToken name,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);

DL_INTERFACE RtVoid RiBasis(RtBasis ubasis, RtInt ustep,
						 RtBasis vbasis, RtInt vstep);
DL_INTERFACE RtVoid RiPatch(RtToken type, ...);
DL_INTERFACE RtVoid RiPatchMesh(RtToken type, RtInt nu, RtToken uwrap,
							 RtInt nv, RtToken vwrap, ...);
DL_INTERFACE RtVoid RiPatchV(
		RtToken type,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);
DL_INTERFACE RtVoid RiPatchMeshV(
		RtToken type,
		RtInt nu, RtToken uwrap,
		RtInt nv, RtToken vwrap,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);
DL_INTERFACE RtVoid RiPoints(RtInt npoints, ...);
DL_INTERFACE RtVoid RiPointsV(
		RtInt npoints,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);
DL_INTERFACE RtVoid RiCurves(RtToken type, RtInt ncurves,
						  RtInt nvertices[], RtToken wrap, ...);
DL_INTERFACE RtVoid RiCurvesV(
		RtToken type, RtInt ncurves,
		RtInt nvertices[], RtToken wrap,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);
DL_INTERFACE RtVoid RiNuCurves(
		RtInt ncurves, RtInt nvertices[],
		RtInt order[], RtFloat knot[],
		RtFloat min[], RtFloat max[], ...);
DL_INTERFACE RtVoid RiNuCurvesV(
		RtInt ncurves, RtInt nvertices[],
		RtInt order[], RtFloat knot[],
		RtFloat min[], RtFloat max[],
		RtInt n, __RI_CONST RtToken tokens[],
		RtPointer params[]);

DL_INTERFACE RtVoid RiNuPatch(RtInt nu, RtInt uorder, RtFloat uknot[],
						   RtFloat umin, RtFloat umax,
						   RtInt nv, RtInt vorder, RtFloat vknot[],
						   RtFloat vmin, double vmax, ...);
DL_INTERFACE RtVoid RiNuPatchV(RtInt nu, RtInt uorder, RtFloat uknot[],
							RtFloat umin, RtFloat umax,
							RtInt nv, RtInt vorder, RtFloat vknot[],
							RtFloat vmin, RtFloat vmax, RtInt n,
							__RI_CONST RtToken tokens[], RtPointer parms[]);
DL_INTERFACE RtVoid RiTrimCurve(RtInt nloops, RtInt ncurves[],
							 RtInt order[], RtFloat knot[],
							 RtFloat min[], RtFloat max[], RtInt n[],
							 RtFloat u[], RtFloat v[], RtFloat w[]);

DL_INTERFACE RtVoid RiSubdivisionMesh(
		RtToken scheme,
		RtInt nfaces, RtInt nvertices[], RtInt vertices[],
		RtInt ntags, __RI_CONST RtToken tags[], RtInt nargs[],
		RtInt intargs[], RtFloat floatargs[],
		...);
DL_INTERFACE RtVoid RiSubdivisionMeshV(
		RtToken scheme,
		RtInt nfaces, RtInt nvertices[], RtInt vertices[],
		RtInt ntags, __RI_CONST RtToken tags[], RtInt nargs[],
		RtInt intargs[], RtFloat floatargs[],
		RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);

DL_INTERFACE RtVoid RiHierarchicalSubdivisionMesh(
		RtToken scheme,
		RtInt nfaces, RtInt nvertices[], RtInt vertices[],
		RtInt ntags, __RI_CONST RtToken tags[], RtInt nargs[],
		RtInt intargs[], RtFloat floatargs[], __RI_CONST RtToken stringargs[],
		...);
DL_INTERFACE RtVoid RiHierarchicalSubdivisionMeshV(
		RtToken scheme,
		RtInt nfaces, RtInt nvertices[], RtInt vertices[],
		RtInt ntags, __RI_CONST RtToken tags[], RtInt nargs[],
		RtInt intargs[], RtFloat floatargs[], __RI_CONST RtToken stringargs[],
		RtInt n, __RI_CONST RtToken tokens[], RtPointer params[]);

DL_INTERFACE RtVoid RiCone(RtFloat height, RtFloat radius,
						double thetamax, ...);
DL_INTERFACE RtVoid RiConeV(
		RtFloat height, RtFloat radius,
		RtFloat thetamax, RtInt n,
		__RI_CONST RtToken tokens[], RtPointer parms[]);
DL_INTERFACE RtVoid RiCylinder(RtFloat radius,RtFloat zmin,RtFloat zmax,
							double thetamax,...);
DL_INTERFACE RtVoid RiCylinderV(
		RtFloat radius,RtFloat zmin,RtFloat zmax,
		RtFloat thetamax, RtInt n,
		__RI_CONST RtToken tokens[], RtPointer parms[]);
DL_INTERFACE RtVoid RiDisk(RtFloat height, RtFloat radius,
						double thetamax, ...);
DL_INTERFACE RtVoid RiDiskV(
		RtFloat height, RtFloat radius,
		RtFloat thetamax, RtInt n,
		__RI_CONST RtToken tokens[], RtPointer parms[]);
DL_INTERFACE RtVoid RiHyperboloid(RtPoint point1, RtPoint point2,
							   double thetamax, ...);
DL_INTERFACE RtVoid RiHyperboloidV(
		RtPoint point1, RtPoint point2,
		RtFloat thetamax, RtInt n,
		__RI_CONST RtToken tokens[], RtPointer parms[]);
DL_INTERFACE RtVoid RiParaboloid(RtFloat rmax,RtFloat zmin,RtFloat zmax,
							  double thetamax,...);
DL_INTERFACE RtVoid RiParaboloidV(
		RtFloat rmax,RtFloat zmin,RtFloat zmax,
		RtFloat thetamax, RtInt n,
		__RI_CONST RtToken tokens[], RtPointer parms[]);
DL_INTERFACE RtVoid RiSphere(RtFloat radius,RtFloat zmin,RtFloat zmax,
						  double thetamax, ...);
DL_INTERFACE RtVoid RiSphereV(
		RtFloat radius,RtFloat zmin,RtFloat zmax,
		RtFloat thetamax, RtInt n,
		__RI_CONST RtToken tokens[], RtPointer parms[]);
DL_INTERFACE RtVoid RiTorus(RtFloat majorradius, RtFloat minorradius,
						 RtFloat phimin, RtFloat phimax,
						 double thetamax, ...);
DL_INTERFACE RtVoid RiTorusV(
		RtFloat majorradius, RtFloat minorradius,
		RtFloat phimin, RtFloat phimax,
		RtFloat thetamax, RtInt n,
		__RI_CONST RtToken tokens[], RtPointer parms[]);

DL_INTERFACE RtVoid RiGeneralPolygon(RtInt nloops,
								  RtInt nvertices[], ...);
DL_INTERFACE RtVoid RiGeneralPolygonV(
		RtInt nloops, RtInt nvertices[],
		RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);

DL_INTERFACE RtVoid RiBlobby(
	RtInt nleaf,
	RtInt nentry, RtInt entry[],
	RtInt nfloat, RtFloat floats[],
	RtInt nstring, RtString strings[], ...);
DL_INTERFACE RtVoid RiBlobbyV(
	RtInt nleaf,
	RtInt nentry, RtInt entry[],
	RtInt nfloat, RtFloat floats[],
	RtInt nstring, RtString strings[],
	RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);

DL_INTERFACE RtVoid RiPointsGeneralPolygons(RtInt npolys, RtInt nloops[],
										 RtInt nvertices[],
										 RtInt vertices[], ...);
DL_INTERFACE RtVoid RiPointsGeneralPolygonsV(
		RtInt npolys, RtInt nloops[],
		RtInt nvertices[],
		RtInt vertices[],
		RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);
DL_INTERFACE RtVoid RiPointsPolygons(RtInt npolys, RtInt nvertices[],
								  RtInt vertices[], ...);
DL_INTERFACE RtVoid RiPointsPolygonsV(
		RtInt npolys, RtInt nvertices[],
		RtInt vertices[],
		RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);
DL_INTERFACE RtVoid RiPolygon(RtInt nvertices, ...);
DL_INTERFACE RtVoid RiPolygonV(
		RtInt nvertices,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);

DL_INTERFACE RtVoid RiColorSamples(RtInt n, RtFloat nRGB[],
								RtFloat RGBn[]);
DL_INTERFACE RtVoid RiHider(RtToken type, ...);
DL_INTERFACE RtVoid RiHiderV(
		RtToken type,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);
DL_INTERFACE RtVoid RiDetail(RtBound bound);
DL_INTERFACE RtVoid RiDetailRange(RtFloat minvisible,
							   RtFloat lowertransition,
							   RtFloat uppertransition,
							   RtFloat maxvisible);
DL_INTERFACE RtVoid RiGeometricApproximation(RtToken type, RtFloat value);
DL_INTERFACE RtVoid RiGeometry(RtToken type, ...);
DL_INTERFACE RtVoid RiGeometryV(
		RtToken type,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer parms[]);
DL_INTERFACE RtVoid RiOrientation(RtToken orientation);
DL_INTERFACE RtVoid RiProcedural(
	RtPointer i_data, RtBound i_bound,
	RtVoid (*i_Subdivfunc)(RtPointer, RtFloat),
	RtVoid (*i_Freefunc)(RtPointer) );
DL_INTERFACE RtVoid RiProceduralV(
	RtPointer i_data, RtBound i_bound,
	RtVoid (*i_Subdivfunc)(RtPointer, RtFloat),
	RtVoid (*i_Freefunc)(RtPointer),
	RtInt n, __RI_CONST RtToken tokens[], RtPointer params[] );
DL_INTERFACE RtVoid RiRelativeDetail(RtFloat relativedetail);
DL_INTERFACE RtVoid RiProcDelayedReadArchive(RtPointer data,
										  RtFloat detail);
DL_INTERFACE RtVoid RiProcDynamicLoad(RtPointer data, RtFloat detail);
DL_INTERFACE RtVoid RiProcRunProgram(RtPointer data, RtFloat detail);
/*
	WARNING: On windows, you should provide your own RiProcFree if you allocate
	the memory yourself. It is not safe to allocate in a module (exe or dll)
	and free in another.
*/
DL_INTERFACE RtVoid RiProcFree(RtPointer data);

DL_INTERFACE RtVoid RiMakeBump(
		const char *picturename, const char *texturename,
		RtToken swrap, RtToken twrap,
		RtFilterFunc filterfunc,
		RtFloat swidth, RtFloat twidth, ... );
DL_INTERFACE RtVoid RiMakeBumpV(
		const char *picturename, const char *texturename,
		RtToken swrap, RtToken twrap,
		RtFilterFunc filterfunc,
		RtFloat swidth, RtFloat twidth,
		RtInt n, __RI_CONST RtToken tokens[],
		RtPointer parms[] );
DL_INTERFACE RtVoid RiMakeCubeFaceEnvironment(
		const char *px, const char *nx,
		const char *py, const char *ny,
		const char *pz, const char *nz,
		const char *texturename,
		RtFloat fov,
		RtFilterFunc filterfunc,
		RtFloat swidth,
		double twidth, ... );
DL_INTERFACE RtVoid RiMakeCubeFaceEnvironmentV(
		const char *px, const char *nx,
		const char *py, const char *ny,
		const char *pz, const char *nz,
		const char *texturename,
		RtFloat fov,
		RtFilterFunc filterfunc,
		RtFloat swidth,
		RtFloat twidth,
		RtInt n,
		__RI_CONST RtToken tokens[],
		RtPointer parms[] );
DL_INTERFACE RtVoid RiMakeLatLongEnvironment(
		const char *picturename,
		const char *texturename,
		RtFilterFunc filterfunc,
		RtFloat swidth,
		double twidth, ... );
DL_INTERFACE RtVoid RiMakeLatLongEnvironmentV(
		const char *picturename,
		const char *texturename,
		RtFilterFunc filterfunc,
		RtFloat swidth,
		RtFloat twidth,
		RtInt n,
		__RI_CONST RtToken tokens[],
		RtPointer parms[] );
DL_INTERFACE RtVoid RiMakeShadow(
		const char *picturename,
		const char *texturename, ... );
DL_INTERFACE RtVoid RiMakeShadowV(
		const char *picturename,
		const char *texturename,
		RtInt n,
		__RI_CONST RtToken tokens[],
		RtPointer parms[] );
DL_INTERFACE RtVoid RiMakeTexture(
		const char *picturename, const char *texturename,
		RtToken swrap, RtToken twrap,
		RtFilterFunc filterfunc,
		RtFloat swidth, double twidth, ... );
DL_INTERFACE RtVoid RiMakeTextureV(
		const char *picturename, const char *texturename,
		RtToken swrap, RtToken twrap,
		RtFilterFunc filterfunc,
		RtFloat swidth, RtFloat twidth,
		RtInt n, __RI_CONST RtToken tokens[],
		RtPointer parms[] );

DL_INTERFACE RtVoid RiMakeBrickMap(
		RtInt nptc, const char *const *ptcnames, const char *bkmname, ...);
DL_INTERFACE RtVoid RiMakeBrickMapV(
		RtInt nptc, const char *const *ptcnames, const char *bkmname,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer params[]);

DL_INTERFACE RtFloat RiBoxFilter(RtFloat x, RtFloat y,
							  RtFloat xwidth, RtFloat ywidth);
DL_INTERFACE RtFloat RiTriangleFilter(RtFloat x, RtFloat y,
								   RtFloat xwidth, RtFloat ywidth);
DL_INTERFACE RtFloat RiCatmullRomFilter(RtFloat x, RtFloat y,
									 RtFloat xwidth, RtFloat ywidth);
DL_INTERFACE RtFloat RiSeparableCatmullRomFilter(RtFloat x, RtFloat y,
									 RtFloat xwidth, RtFloat ywidth);
DL_INTERFACE RtFloat RiBesselFilter(RtFloat x, RtFloat y,
								 RtFloat xwidth, RtFloat ywidth);
DL_INTERFACE RtFloat RiGaussianFilter(RtFloat x, RtFloat y,
								   RtFloat xwidth, RtFloat ywidth);
DL_INTERFACE RtFloat RiSincFilter(RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth);
DL_INTERFACE RtFloat RiBlackmanHarrisFilter(RtFloat i_x, RtFloat i_y, RtFloat i_filterXWidth, RtFloat i_filteryWidth);
DL_INTERFACE RtFloat RiMitchellFilter(RtFloat i_x, RtFloat i_y, RtFloat i_filterXWidth, RtFloat i_filteryWidth);
DL_INTERFACE RtFloat RiDiskFilter(RtFloat i_x, RtFloat i_y, RtFloat i_filterXWidth, RtFloat i_filteryWidth);


DL_INTERFACE RtVoid RiErrorHandler( RtErrorHandler handler);
DL_INTERFACE RtVoid RiErrorIgnore(RtInt code, RtInt severity, __RI_CONST char *msg);
DL_INTERFACE RtVoid RiErrorPrint(RtInt code, RtInt severity, __RI_CONST char *msg);
DL_INTERFACE RtVoid RiErrorAbort(RtInt code, RtInt severity, __RI_CONST char *msg);

DL_INTERFACE RtVoid RiSynchronize(RtToken);


DL_INTERFACE RtVoid RiEditBegin( RtToken name, ... );
DL_INTERFACE RtVoid RiEditBeginV(
		RtToken name,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer params[] );
DL_INTERFACE RtVoid RiEditEnd();

DL_INTERFACE RtVoid RiEditWorldBegin( RtToken name, ... );
DL_INTERFACE RtVoid RiEditWorldBeginV(
		RtToken name,
		RtInt n, __RI_CONST RtToken tokens[], RtPointer params[] );
DL_INTERFACE RtVoid RiEditWorldEnd();


/* ===========================================================================
    Error codes
   ===========================================================================

	 1 - 10		System and File Errors
	11 - 20		Program Limitations
	21 - 40		State Errors
	41 - 60		Parameter and Protocol Errors
	61 - 80		Execution Errors
   =========================================================================*/

#define RIE_NOERROR     ((RtInt)0)

#define RIE_NOMEM       ((RtInt)1)	 /* Out of memory */
#define RIE_SYSTEM      ((RtInt)2)	 /* Miscellaneous system error */
#define RIE_NOFILE      ((RtInt)3)	 /* File nonexistent */
#define RIE_BADFILE     ((RtInt)4)	 /* Bad file format */
#define RIE_VERSION     ((RtInt)5)	 /* File version mismatch */
#define RIE_DISKFULL    ((RtInt)6)	 /* Target disk is full */

#define RIE_INCAPABLE   ((RtInt)11)	 /* Optional RI feature */
#define RIE_UNIMPLEMENT ((RtInt)12)	 /* Unimplemented feature */
#define RIE_LIMIT       ((RtInt)13)	 /* Arbitrary program limit */
#define RIE_BUG         ((RtInt)14)	 /* Probably a bug in renderer */

#define RIE_NOTSTARTED  ((RtInt)23)	 /* RiBegin not called */
#define RIE_NESTING     ((RtInt)24)	 /* Bad begin-end nesting */
#define RIE_NOTOPTIONS  ((RtInt)25)	 /* Invalid state for options */
#define RIE_NOTATTRIBS  ((RtInt)26)	 /* Invalid state for attribs */
#define RIE_NOTPRIMS    ((RtInt)27)	 /* Invalid state for primitives */
#define RIE_ILLSTATE    ((RtInt)28)	 /* Other invalid state */
#define RIE_BADMOTION   ((RtInt)29)	 /* Badly formed motion block */
#define RIE_BADSOLID    ((RtInt)30)	 /* Badly formed solid block */

#define RIE_BADTOKEN    ((RtInt)41)	 /* Invalid token for request */
#define RIE_RANGE       ((RtInt)42)	 /* Parameter out of range */
#define RIE_CONSISTENCY ((RtInt)43)	 /* Parameters inconsistent */
#define RIE_BADHANDLE   ((RtInt)44)	 /* Bad object/light handle */
#define RIE_NOSHADER    ((RtInt)45)	 /* Can't load requested shader */
#define RIE_MISSINGDATA ((RtInt)46)	 /* Required parameters not provided */
#define RIE_SYNTAX      ((RtInt)47)	 /* Declare type syntax error */
#define RIE_TOKENREDECLARED ((RtInt)48)	 /* Redeclaration of token */

#define RIE_MATH        ((RtInt)61)	 /* Zerodivide, noninvert matrix, etc. */


#define RIE_BADATTRIB	((RtInt)140)	/* Unsupported attribute */
#define RIE_BADOPTION	((RtInt)141)	/* Unsupported option */
#define RIE_SPACEREDECLARED ((RtInt)142)/* Redeclaration of space */
#define RIE_NODISPLAY   ((RtInt)143)	/* Can't load requested display server */
#define RIE_ERRRERTOOBID  ((RtInt)144)	/* Image resolution too big */
#define RIE_ERRBADSHADERPARAM ((RtInt145)           /* Parameter is not in shader param list */
#define RIE_ERRSHADERPARAMMISMATCH ((RtInt)146)     /* Value for parameter does not match declaration */
#define RIE_ERRBADARRAYACCESSINSHADER ((RtInt)147)  /* Invalid array index done in a shader */

#define RIE_SHADER_PRINTF ((RtInt)199)  /* output of a shader's printf() */

/* ===========================================================================
    Error severity levels
   =========================================================================*/

#define RIE_INFO        ((RtInt)0) /* Rendering stats and other info */
#define RIE_WARNING     ((RtInt)1) /* Something seems wrong, maybe okay */
#define RIE_ERROR       ((RtInt)2) /* Problem. Results may be wrong */
#define RIE_SEVERE      ((RtInt)3) /* So bad you should probably abort */


#ifdef __cplusplus
}
#endif

#endif
