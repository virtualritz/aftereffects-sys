/*
	Copyright (c) 2011 DNA Research.
*/

#ifndef __dtex_h
#define __dtex_h

#include "dlInterface.h"

#ifdef  __cplusplus
extern "C" {
#endif

/* The following struct types aren't exported; users may only
   access members through the API calls defined below. */
typedef struct DtexFile DtexFile;
typedef struct DtexImage DtexImage;
typedef struct DtexPixel DtexPixel;
typedef struct DtexCache DtexCache;
typedef struct DtexAccessor DtexAccessor; /* unsupported */

/* Tile compression type.
   DTEX_COMPRESSION_NONE is only supported at the moment */
typedef enum DtexCompression
{
    DTEX_COMPRESSION_NONE = 0,
    DTEX_COMPRESSION_RLE = 2,
    DTEX_COMPRESSION_LZW = 3,
    DTEX_COMPRESSION_HUFFMAN = 5,
    DTEX_COMPRESSION_ZIP = 6
} DtexCompression; 

/* Type of data stored with each pixel.
   DTEX_TYPE_FLOAT is only supported at the moment */
typedef enum DtexDataType
{
    DTEX_TYPE_BYTE = 1,
    DTEX_TYPE_SHORT = 2,
    DTEX_TYPE_WORD = 3,
    DTEX_TYPE_FLOAT = 4
} DtexDataType;

/* Volume interpretation mode */
typedef enum DtexVolumeInterpretation
{
    DTEX_VOLUME_DISCRETE = 0,
    DTEX_VOLUME_CONTINUOUS = 1,
    DTEX_VOLUME_DEEPPREVDISTTOTAL = 2
} DtexVolumeInterpretation;

/* Error codes: */
enum{
    DTEX_TILECOMPRESSION = -10,
    DTEX_UNFINISHED = -9,
    DTEX_RANGE = -8,
    DTEX_NOMEM = -7,
    DTEX_EMPTY = -6,
    DTEX_NOIMAGE = -5,
    DTEX_UNSUPPORTED = -4,
    DTEX_BADFILE = -3,
    DTEX_NOFILE = -2,
    DTEX_ERR = -1,
    DTEX_NOERR = 0
};

/* Dtex attributes tokens declaration */
extern DL_INTERFACE const char* DTEX_VOLUME_INTERPRETATION;
extern DL_INTERFACE const char* DTEX_NEAR_CLIPPING_PLANE;
extern DL_INTERFACE const char* DTEX_FAR_CLIPPING_PLANE;

/* Cache functions */
DL_INTERFACE DtexCache* DtexCreateCache(
	int i_numTiles,
	DtexAccessor *i_accessor);
DL_INTERFACE int DtexDestroyCache(DtexCache *io_c);

/* File opening/closing functions */

DL_INTERFACE int DtexOpenFile(
	const char *i_name,
	const char *i_mode,		/* Must be "rb" */
	DtexCache *io_cache,	/* Must be NULL */
	DtexFile **o_result);
DL_INTERFACE int DtexCreateFile(
	const char *i_name,
	DtexCache *io_cache,
	DtexFile **o_result);
DL_INTERFACE int DtexAddImage(
	DtexFile *i_f,
	const char *i_name,
	int i_numChan,
	int i_w, int i_h,
	int i_tw, int i_th,		/* tile width and height */
	float *i_NP,
	float *i_Nl,
	enum DtexCompression i_compression,
	enum DtexDataType i_datatype,
	DtexImage **o_result);

DL_INTERFACE int DtexCountImages(DtexFile *i_f);

DL_INTERFACE int DtexGetImageByIndex(
	DtexFile *i_f,
	int i_index,
	DtexImage **o_result);

DL_INTERFACE int DtexClose(DtexFile *i_ds);

/* File access functions */

DL_INTERFACE int DtexWidth(DtexImage *i_i);
DL_INTERFACE int DtexHeight(DtexImage *i_i);
DL_INTERFACE char *DtexImageName(DtexImage *i);

DL_INTERFACE int DtexNumChan(DtexImage *i_i);

DL_INTERFACE int DtexTileWidth(DtexImage *i_i);
DL_INTERFACE int DtexTileHeight(DtexImage *i_i);

DL_INTERFACE int DtexNP(DtexImage *i_i, float *o_NP);
DL_INTERFACE int DtexNl(DtexImage *i_i, float *o_Nl);
DL_INTERFACE DtexCompression DtexGetCompression(DtexImage *i);
DL_INTERFACE DtexDataType DtexGetDataType(DtexImage *i);
DL_INTERFACE int DtexSetPixel(
	DtexImage *io_img,
	int i_x, int i_y,
	DtexPixel *i_pix);
DL_INTERFACE int DtexGetPixel(
	DtexImage *io_img,
	int i_x, int i_y,
	DtexPixel *o_pix);

DL_INTERFACE int DtexEval(
	DtexImage *i_img,
	int i_x, int i_y,
	float i_z,
	int i_n,
	float *o_data);

DL_INTERFACE int DtexGetZRange(
	DtexImage *i_img,
	int i_x, int i_y,
	float *o_min,
	float *o_max);

DL_INTERFACE int DtexGetAttribute(
	DtexImage *i_img,
	const char *i_name,
	void *o_value);
DL_INTERFACE int DtexSetAttribute(
	DtexImage *i_img,
	const char *i_name,
	void *i_value);

/* Pixel structure functions */

DL_INTERFACE DtexPixel * DtexMakePixel(int i_numChan);

DL_INTERFACE void DtexDestroyPixel(DtexPixel *io_pix);
DL_INTERFACE int DtexClearPixel(DtexPixel *io_pix, int i_numChan);

DL_INTERFACE int DtexPixelGetNumPoints(DtexPixel *i_pix);
DL_INTERFACE int DtexPixelGetPoint(DtexPixel *pix, int i, float *z, float *data);
DL_INTERFACE int DtexFinishPixel(DtexPixel *dest);
DL_INTERFACE int DtexAppendPixel(
	DtexPixel *io_pix,
	float i_z,
	int i_numChan,
	float *i_data,
	float i_error);
			   
DL_INTERFACE int DtexEvalPixel(
	DtexPixel *i_pix,
	float i_z,
	int i_n,
	float *o_data);
DL_INTERFACE int DtexGetPixelZRange(
	DtexPixel *i_pix,
	float *o_min,
	float *o_max);

#ifdef __cplusplus
}
#endif

#endif /* DTEX_H */
