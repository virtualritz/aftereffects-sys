
#ifndef ndspy_h
#define ndspy_h

#include <stdio.h>
#include <stdlib.h>
#include <uparam.h>
#include "dlInterface.h"


#define PkDspyMaxMsgSize 32760

#define PkDspyServerMsgOpen  (65 + 1)
#define PkDspyServerMsgImage (65 + 2)
#define PkDspyServerMsgData  (65 + 3)
#define PkDspyServerMsgQuery (65 + 4)
#define PkDspyServerMsgClose (65 + 5)

/*
PtDspyUnsigned64
PtDspySigned64
*/
typedef double PtDspyFloat64;
typedef float PtDspyFloat32;

#if defined(__mips)
#define PkDspyByteOrderNative	PkDspyByteOrderHiLo
#elif defined(__mips64)
#define PkDspyByteOrderNative	PkDspyByteOrderHiLo
#elif defined(__sparc)
#define PkDspyByteOrderNative	PkDspyByteOrderHiLo
#elif defined(__alpha)
#define PkDspyByteOrderNative	PkDspyByteOrderLoHi
#else
#define PkDspyByteOrderNative	PkDspyByteOrderLoHi
#endif

#if defined(__mips64) || defined(__alpha)
typedef unsigned int PtDspyUnsigned32;
typedef int PtDspySigned32;
#else
typedef unsigned long PtDspyUnsigned32;
typedef long PtDspySigned32;
#endif

typedef unsigned short PtDspyUnsigned16;
typedef short PtDspySigned16;

typedef unsigned char PtDspyUnsigned8;
typedef char PtDspySigned8;

typedef PtDspyUnsigned32 PtDspyMsgLen;
typedef PtDspyUnsigned32 PtDspyServerMessage;

#define PkDspyClassFloat 1
#define PkDspyClassInt 2

#define PkDspyNone          0

#define PkDspyFloat32		1
#define PkDspyFloat16       12  /* 3Delight addition */
#define PkDspyUnsigned32	2
#define PkDspySigned32		3
#define PkDspyUnsigned16	4
#define PkDspySigned16		5
#define PkDspyUnsigned8		6
#define PkDspySigned8		7

#define PkDspyString		8
#define PkDspyMatrix		9
#define PkDspyArrayBegin	10
#define PkDspyArrayEnd      11

#define PkDspyMaskType		8191

#define PkDspyMaskOrder (PkDspyByteOrderHiLo | PkDspyByteOrderLoHi)
#define PkDspyShiftOrder	13
#define PkDspyByteOrderHiLo	8192
#define PkDspyByteOrderLoHi	16384

/* #define PkDspyOpenPortCount 8 */

/* Added by Aghiles Kheffache for row data displays >>>> */

typedef struct PtDspyFragment_s
{
	/* WARNING, if DlFragment changes in DlSampler, change this structure too!
	 */

	/* Fragment color & opacity */
	float *color;
	float thickness;
	unsigned filler;

	/* depth of this fragment */
	float depth;

	/* u/v */
	float u, v;
	
	/* fragment opacity */
	float opacity[3];

	/* Next fragment on the list (in the subsample) */
	struct PtDspyFragment_s *next;

} PtDspyFragment;

typedef struct
{
	char ID[4];

	/* Samples per pixel in x & y */
	unsigned sppx, sppy;

	/* Data width & height in pixels */
	int width, height;

	/* Array of fragment lists. NumLists = width*height*sppx*sppy */
	PtDspyFragment **fragments;

} PtDspyRawData;

/* <<<< Added by Aghiles Kheffache for row data displays */

/* Convenient struct to access the channels of deep samples. */
struct PtDspyDeepSample
{
	/* front and back depth */
	float Z, ZBack;
	/* opacity RGB */
	float A[3];
	/* user channels (actual number is variable) */
	float U[1];

#ifdef  __cplusplus
private:
	PtDspyDeepSample();
	PtDspyDeepSample( const PtDspyDeepSample& );
	void operator=( const PtDspyDeepSample& );
#endif
};

typedef struct
{
	/* "DEEP0". To validate struct version. */
	char ID[8];

	/* Subpixels per pixel in x and y. */
	int xSPP, ySPP;

	/*
		Coordinates of the bucket, in pixels. After filtering, the bucket
		covers [xBegin,xEnd) x [yBegin,yEnd) .
	*/
	int xBegin, yBegin;
	int xEnd, yEnd;

	/*
		Extra pixels given for filtering around the bucket. Always whole extra
		pixels even if only half a pixel's samples are needed. However, the
		unused samples may be left empty by the renderer.
	*/
	int xFilterExtraPixels, yFilterExtraPixels;

	/*
		Filter coefficients. There are (1 + 2 * xFilterExtraPixels) * xSPP
		values in xFilterCoefficients. Same for y.
	*/
	float *xFilterCoefficients, *yFilterCoefficients;

	/*
		Includes mandatory Z, ZBack, AR, AG, RB followed by user channels.
		See PtDspyDeepSample.
	*/
	unsigned numChannels;

	/*
		Total number of deep pixels sent. Extra data is sent around the display
		area for filtering so this is always equal to:
		((xEnd - xBegin) + 2 * xFilterExtraPixels) * xSPP *
		((yEnd - yBegin) + 2 * yFilterExtraPixels) * ySPP
	*/
	unsigned numDeepPixels;

	/* numDeepPixels + 1 offsets (in samples) for the deep pixels. */
	unsigned *deepPixelOffsets;

	/*
		Packed deep pixel data in row-major order. Pixel i starts at:
		deepData + deepPixelOffsets[i] * numChannels
		It ends where pixel i+1 starts.
	*/
	float *deepData;
} PtDspyDeepData;

typedef struct
{
   const char *name;
   unsigned type;
} PtDspyDevFormat;


typedef struct
{
	PtDspyUnsigned32 width;
	PtDspyUnsigned32 height;
	PtDspyFloat32 aspectRatio;
} PtDspySizeInfo;

typedef struct
{
  PtDspyUnsigned8 overwrite;
  PtDspyUnsigned8 unused; /* 'interactive' in prman */
} PtDspyOverwriteInfo;

typedef struct
{
  PtDspyUnsigned8 redraw;
} PtDspyRedrawInfo;

/* added by AK */
typedef struct
{
	/* See PtDspyCookedQueryValue below. */
	PtDspyUnsigned8 cooked;
} PtDspyCookedInfo;

typedef enum
{
	/* 1 = default behavior (filtered pixel data) */
	PkDspyCQDefault = 1,
	/* 3 = Deep data (PtDspyDeepData) */
	PkDspyCQDeep = 3
} PtDspyCookedQueryValue;

/* added by OP */
typedef struct
{
	PtDspyUnsigned8 multithread;
} PtDspyThreadInfo;

/* added by OP */
typedef struct
{
	PtDspyUnsigned8 acceptProgressive;
} PtDspyProgressiveInfo;

typedef enum
{
	PkSizeQuery,
	PkOverwriteQuery,
	PkNextDataQuery,
	PkRedrawQuery,
	PkCookedQuery = 100, /* this one is not a standard prman query, AK */
	PkThreadQuery,       /* another 3Delight extension, PtDspyThreadInfo */
	PkProgressiveQuery,  /* same, PtDspyProgressiveInfo */
	PkStopQuery,         /* no infos, simply return ErrorNone or ErrorStop */
	PkPreBucketFunctionQuery,  /* returns pointer to PtDspyPreBucketFuncPtr */
	PkRenderStatistics, /* returns pointer to PtDspyRenderStatisticsFuncPtr */
	PkRenderProgress,    /* returns pointer to PtDspyRenderProgressFuncPtr */
	PkBucketVersion, /* returns pointer to PtDspyVersionFuncPtr */
	PkPreRenderProgress,    /* returns pointer to PtDspyRenderProgressFuncPtr */
	PkPreRenderAutoProgress /* returns pointer to PtDspyRenderAutoProgressFuncPtr */
} PtDspyQueryType;

typedef enum
{
	PkDspyErrorNone = 0,
	PkDspyErrorNoMemory,
	PkDspyErrorUnsupported,
	PkDspyErrorBadParams,
	PkDspyErrorNoResource,
	PkDspyErrorUndefined,
	PkDspyErrorStop
} PtDspyError;

#define PkDspyFlagsWantsScanLineOrder 1
#define PkDspyFlagsWantsEmptyBuckets 2
#define PkDspyFlagsWantsNullEmptyBuckets 4

typedef struct
{
	int flags;
} PtFlagStuff;

typedef void * PtDspyImageHandle;
typedef void * PtDspyChannel;
typedef void * PtDspyOutput;

#ifndef UTILITIES_DLLIMPORT
#	define UTILITIES_DLLIMPORT _3DL_EXTERN_C _3DL_ALWAYS_IMPORT
#endif

_3DL_EXTERN_C _3DL_ALWAYS_EXPORT PtDspyError
DspyImageOpen(PtDspyImageHandle * image,
		const char *drivername,
		const char *filename,
		int width,
		int height,
		int paramCount,
		const UserParameter *parameters,
		int iFormatCount,
		PtDspyDevFormat *format,
		PtFlagStuff *flagstuff);

_3DL_EXTERN_C _3DL_ALWAYS_EXPORT PtDspyError
DspyImageData(PtDspyImageHandle image,
		int xmin,
		int xmax,
		int ymin,
		int ymax,
		int entrysize,
		const unsigned char *data);
 
_3DL_EXTERN_C _3DL_ALWAYS_EXPORT PtDspyError
DspyImageClose(PtDspyImageHandle);

_3DL_EXTERN_C _3DL_ALWAYS_EXPORT  PtDspyError
DspyImageReopen(PtDspyImageHandle image,
		const char *drivername,
		const char *filename,
		int width,
		int height,
		int paramCount,
		const UserParameter *parameters,
		int iFormatCount,
		PtDspyDevFormat *format,
		PtFlagStuff *flagstuff);

_3DL_EXTERN_C _3DL_ALWAYS_EXPORT PtDspyError
DspyImageDelayClose(PtDspyImageHandle);

_3DL_EXTERN_C _3DL_ALWAYS_EXPORT PtDspyError
DspyImageQuery(PtDspyImageHandle,
	   PtDspyQueryType,
	   int,
	   void *);


typedef PtDspyError
	(*PtDspyOpenFuncPtr)(
		PtDspyImageHandle * image,
		const char *drivername,
		const char *filename,
		int width,
		int height,
		int paramCount,
		const UserParameter *parameters,
		int iFormatCount,
		PtDspyDevFormat *format,
		PtFlagStuff *flagstuff);

typedef PtDspyError
	(*PtDspyWriteFuncPtr)(
		PtDspyImageHandle image,
		int xmin,
		int xmax_plus_one,
		int ymin,
		int ymax_plus_one,
		int entrysize,
		const unsigned char *data);

typedef PtDspyError
	(*PtDspyCloseFuncPtr)(PtDspyImageHandle);
typedef PtDspyError
	(*PtDspyFlushFuncPtr)(PtDspyImageHandle);

typedef PtDspyError
	(*PtDspyReopenFuncPtr)(
		PtDspyImageHandle image,
		const char *drivername,
		const char *filename,
		int width,
		int height,
		int paramCount,
		const UserParameter *parameters,
		int iFormatCount,
		PtDspyDevFormat *format,
		PtFlagStuff *flagstuff);

typedef PtDspyError
	(*PtDspyDelayCloseFuncPtr)(PtDspyImageHandle);

typedef PtDspyError
	(*PtDspyQueryFuncPtr)(
		PtDspyImageHandle,
		PtDspyQueryType,
		int ,
		void * );

typedef PtDspyError
	(*PtDspyActiveRegionFuncPtr)(PtDspyImageHandle image,
		int xmin,
		int xmax_plus_one,
		int ymin,
		int ymax_plus_one );

typedef PtDspyError
	(*PtDspyPreBucketFuncPtr)(PtDspyImageHandle image,
		int xmin,
		int xmax_plus_one,
		int ymin,
		int ymax_plus_one,
		int pass,
		int flags );

typedef PtDspyError (*PtDspyVersionFuncPtr)(PtDspyImageHandle, int);

typedef PtDspyError
	(*PtDspyRenderStatisticsFuncPtr)(PtDspyImageHandle image, void * );

typedef PtDspyError
	(*PtDspyRenderProgressFuncPtr)(PtDspyImageHandle image, float progress);

typedef PtDspyError
	(*PtDspyRenderAutoProgressFuncPtr)(
		PtDspyImageHandle image,
		float progress_from,
		float progress_to,
		float duration,
		const char* step);


typedef enum
{
	k_PtDriverUnknownVersion = 0,
	k_PtDriverCurrentVersion = 1
} PtDriverVersion;

typedef struct
{
	int Version;
	PtDspyOpenFuncPtr pOpen;
	PtDspyWriteFuncPtr pWrite;
	PtDspyCloseFuncPtr pClose;
	PtDspyQueryFuncPtr pQuery;
	PtDspyActiveRegionFuncPtr pActiveRegion;
} PtDspyDriverFunctionTable;

/* Utilities, for PrMan compatibility. */

UTILITIES_DLLIMPORT void
DspyMemReverseCopy(
	unsigned char *t,
	const unsigned char *s,
	int len );

UTILITIES_DLLIMPORT void
DspyMemReverse(
	unsigned char *t,
	int len );

UTILITIES_DLLIMPORT PtDspyError
DspyFindStringInParamList(
	const char *name,
	char **result,
	int paramCount,
	const UserParameter *parameters );

UTILITIES_DLLIMPORT PtDspyError
DspyFindMatrixInParamList(
	const char *name,
	float *result,
	int paramCount,
	const UserParameter *parameters );

UTILITIES_DLLIMPORT PtDspyError
DspyFindFloatInParamList(
	const char *name,
	float *result,
	int paramCount,
	const UserParameter *parameters );

UTILITIES_DLLIMPORT PtDspyError
DspyFindFloatsInParamList(
	const char *name,
	int *resultCount,
	float *result,
	int paramCount,
	const UserParameter *parameters );

UTILITIES_DLLIMPORT PtDspyError
DspyFindIntInParamList(
	const char *name,
	int *result,
	int paramCount,
	const UserParameter *parameters );

UTILITIES_DLLIMPORT PtDspyError
DspyFindIntsInParamList(
	const char *name,
	int *resultCount,
	int *result,
	int paramCount,
	const UserParameter *parameters );

UTILITIES_DLLIMPORT PtDspyError
DspyReorderFormatting(
	int formatCount,
	PtDspyDevFormat *format,
	int outFormatCount,
	const PtDspyDevFormat *outFormat );

UTILITIES_DLLIMPORT void
DspyError(
	const char *module,
	const char *fmt,
	... );

/* Deprecated. Use DspyRegisterDriverTable instead. */
UTILITIES_DLLIMPORT PtDspyError
DspyRegisterDriver(
	const char *driver_name,
	const PtDspyOpenFuncPtr pOpen,
	const PtDspyWriteFuncPtr pWrite,
	const PtDspyCloseFuncPtr pClose,
	const PtDspyQueryFuncPtr pQuery );

/*
	Registers a display driver by giving pointers to the entry points directly.

	NOTES
	- If pTable is null, the driver is unregistered.
*/
UTILITIES_DLLIMPORT PtDspyError
DspyRegisterDriverTable(
	const char *driver_name,
	const PtDspyDriverFunctionTable *pTable );

#endif /* ifdef ndspy_h */





