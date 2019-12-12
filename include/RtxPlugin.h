#ifndef RTXPLUGIN_H
#define RTXPLUGIN_H

#include "ri.h"

class RixContext;

class RtxPlugin
{
public:
	RtxPlugin() {}
	virtual ~RtxPlugin() {}

	/* 2D Coordinates. */
	struct Int2D
	{
		int X;
		int Y;
	};

	/* 2D Region. */
	struct Tile2D
	{
		Int2D offset;
		Int2D size;
	};

	/*
		This is given to the plugin's Open() method with the arguments from the
		URI string parsed into argc and argv by the renderer. The plugin should
		fill the rest of the structure with the details about the texture it
		will generate.

		The TextureCtx object will then be given to FillRequest() calls and
		eventually to Close() when the texture is no longer needed.
	*/
	struct TextureCtx
	{
		/* Total number of channels available in the texture. */
		int numChannels;

		/* Number of layers in the texture. */
		unsigned int numLayers;

		/* Name and number of channels for each layer. The memory for the
		   layers array is owned by the plugin. */
		struct layerSpec
		{
			const char *name;
			unsigned numChannels;
		} **layers;

		/*
			The minimum and maximum resolution that the renderer can request
			for this texture. In practice, the rendered will pick mipmap
			resolutions from maxRes, making them smaller until minRes is
			reached. Note that a large minRes may result in slow or poor
			filtering.
		*/
		Int2D minRes, maxRes;

		/* Texture edge wrap mode. */
		enum WrapMode
		{
			k_Black = 0,
			k_Clamp,
			k_Periodic
		} sWrap, tWrap;

		/* Texture data type. */
		enum DataType
		{
			k_Byte = 0, /* 8-bit unsigned */
			k_Float     /* RtFloat */
		} dataType;

		/* The kind of mipmapping that the plugin provides. */
		enum PyramidType
		{
			k_Single = 0,
			k_MIP,
			k_RIP
		} pyramidType;

		/* Unused. */
		bool isLocked;

		/* The arguments in the URI given to texture(). They are name-value
		   pairs so argc will always be an even number. This is owned by the
		   renderer. */
		unsigned int argc;
		const char **argv;

		/* Reserved for use by the plugin. */
		void *userData;
	};

	/*
		Open() is called for every unique texture URI this plugin must handle.
		It should return 0 on success and some other value on error.
		FillRequest() and Close() will not be called with tCtx if an error is
		reported.

		RETURNS
			0 on success, another value on error.
	*/
	virtual int Open( TextureCtx &tCtx ) = 0;

	struct FillRequest
	{
		/* The resolution of the image at the requested mipmap level. */
		Int2D imgRes;

		/* Position (0 based, in tiles) of the requested tile and tile size. */
		Tile2D tile;

		/* Channel selection string. May be null. */
		const char *channelRefExpr;

		/* Offset of the first channel requested. */
		int channelOffset;

		/* The number of channels requested. */
		int numChannels;

		/* Pointer to the buffer to be filled with requested data (all
		   requested channels interleaved). */
		RtPointer tileData;
	};

	/*
		The plugin must fill fillReq.tileData with the requested texture data.

		RETURNS
			0 on success, another value on error.
	*/
    virtual int Fill( TextureCtx &tCtx, FillRequest &fillReq ) = 0;

	/*
		The given texture will no longer be needed by the renderer. The plugin
		should free associated resources.
	*/
    virtual int Close( TextureCtx &tCtx ) = 0;
};

/*
	This helps define a C function for the creation of a C++ plugin object. It
	also defines a corresponding function for safely deleting it in the correct
	module. Use like this in your plugin source code:

	RTXPLUGINCREATE
	{
		return new myRtxPlugin();
	}
*/
#define RTXPLUGINCREATE \
	extern "C" _3DL_ALWAYS_EXPORT const int RtxPluginVersion = 1; \
	extern "C" _3DL_ALWAYS_EXPORT void RtxPluginDelete( RtxPlugin *plugin ) { delete plugin; } \
	extern "C" _3DL_ALWAYS_EXPORT RtxPlugin *RtxPluginNew( RixContext *rixCtx, const char *pluginName )
#endif
