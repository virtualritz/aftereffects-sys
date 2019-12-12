/*
	This file contains the code required to load NSI at runtime instead of
	linking with it at build time. To use, simply give an instance to the
	context constructor:

	NSI::DynamicAPI api;
	NSI::Context ctx( api );

	ctx.Begin();
	ctx.Create( "myhandle", "mesh" );
	...

	The DynamicAPI class loads and unloads the library so at least one instance
	must be kept active while the renderer is in use.
*/

#ifndef __nsi_dynamic_hpp
#define __nsi_dynamic_hpp

#include "nsi.hpp"

#if defined(__linux__) || defined(__APPLE__)
#	include <dlfcn.h>
#elif defined(_WIN32)
#	include <windows.h>
#endif

namespace NSI
{

/* API provider which dynamically loads the renderer. */
class DynamicAPI : public CAPI
{
#if defined(__linux__) || defined(__APPLE__)
	void *m_lib;

	template<typename T>
	void LoadFunction( T &function, const char *name )
	{
		if( m_lib )
			function = (T) dlsym( m_lib, name );
		else
			function = (T)0;
	}
#elif defined(_WIN32)
	HMODULE m_lib;

	template<typename T>
	void LoadFunction( T &function, const char *name )
	{
		if( m_lib )
			function = (T) GetProcAddress( m_lib, name );
		else
			function = (T)0;
	}
#else
	template<typename T>
	void LoadFunction( T &function, const char *name )
	{
		function = (T)0;
	}
#endif

public:
	DynamicAPI()
	{
#if defined(__linux__)
		m_lib = dlopen( "lib3delight.so", RTLD_NOW );
#elif defined(__APPLE__)
		m_lib = dlopen( "lib3delight.dylib", RTLD_NOW );
#elif defined(_WIN32)
		m_lib = LoadLibrary( "3Delight.dll" );
#endif
		LoadFunction( Begin, "NSIBegin" );
		LoadFunction( End, "NSIEnd" );
		LoadFunction( Create, "NSICreate" );
		LoadFunction( Delete, "NSIDelete" );
		LoadFunction( SetAttribute, "NSISetAttribute" );
		LoadFunction( SetAttributeAtTime, "NSISetAttributeAtTime" );
		LoadFunction( DeleteAttribute, "NSIDeleteAttribute" );
		LoadFunction( Connect, "NSIConnect" );
		LoadFunction( Disconnect, "NSIDisconnect" );
		LoadFunction( Evaluate, "NSIEvaluate" );
		LoadFunction( RenderControl, "NSIRenderControl" );
	}

	virtual ~DynamicAPI()
	{
#if defined(__linux__) || defined(__APPLE__)
		if( m_lib != 0 )
			dlclose( m_lib );
#elif defined(_WIN32)
		if( m_lib != 0 )
			FreeLibrary( m_lib );
#endif
	}

	virtual NSIContext_t NSIBegin(
		int nparams,
		const NSIParam_t *params ) const
	{
		if( Begin )
			return Begin( nparams, params );
		else
			return NSI_BAD_CONTEXT;
	}

	virtual void NSIEnd(
		NSIContext_t ctx ) const
	{
		if( End )
			End( ctx );
	}

	virtual void NSICreate(
		NSIContext_t ctx,
		NSIHandle_t handle,
		const char *type,
		int nparams,
		const NSIParam_t *params ) const
	{
		if( Create )
			Create( ctx, handle, type, nparams, params );
	}

	virtual void NSIDelete(
		NSIContext_t ctx,
		NSIHandle_t handle,
		int nparams,
		const NSIParam_t *params ) const
	{
		if( Delete )
			Delete( ctx, handle, nparams, params );
	}

	virtual void NSISetAttribute(
		NSIContext_t ctx,
		NSIHandle_t object,
		int nparams,
		const NSIParam_t *params ) const
	{
		if( SetAttribute )
			SetAttribute( ctx, object, nparams, params );
	}

	virtual void NSISetAttributeAtTime(
		NSIContext_t ctx,
		NSIHandle_t object,
		double time,
		int nparams,
		const NSIParam_t *params ) const
	{
		if( SetAttributeAtTime )
			SetAttributeAtTime( ctx, object, time, nparams, params );
	}

	virtual void NSIDeleteAttribute(
		NSIContext_t ctx,
		NSIHandle_t object,
		const char *name ) const
	{
		if( DeleteAttribute )
			DeleteAttribute( ctx, object, name );
	}

	virtual void NSIConnect(
		NSIContext_t ctx,
		NSIHandle_t from,
		const char *from_attr,
		NSIHandle_t to,
		const char *to_attr,
		int nparams,
		const NSIParam_t *params ) const
	{
		if( Connect )
			Connect( ctx, from, from_attr, to, to_attr, nparams, params );
	}

	virtual void NSIDisconnect(
		NSIContext_t ctx,
		NSIHandle_t from,
		const char *from_attr,
		NSIHandle_t to,
		const char *to_attr ) const
	{
		if( Disconnect )
			Disconnect( ctx, from, from_attr, to, to_attr );
	}

	virtual void NSIEvaluate(
		NSIContext_t ctx,
		int nparams,
		const NSIParam_t *params ) const
	{
		if( Evaluate )
			Evaluate( ctx, nparams, params );
	}

	virtual void NSIRenderControl(
		NSIContext_t ctx,
		int nparams,
		const NSIParam_t *params ) const
	{
		if( RenderControl )
			RenderControl( ctx, nparams, params );
	}

private:
	/* API function pointers. */
	NSIContext_t (*Begin)(
		int nparams,
		const NSIParam_t *params );

	void (*End)(
		NSIContext_t ctx );

	void (*Create)(
		NSIContext_t ctx,
		NSIHandle_t handle,
		const char *type,
		int nparams,
		const NSIParam_t *params );

	void (*Delete)(
		NSIContext_t ctx,
		NSIHandle_t handle,
		int nparams,
		const NSIParam_t *params );

	void (*SetAttribute)(
		NSIContext_t ctx,
		NSIHandle_t object,
		int nparams,
		const NSIParam_t *params );

	void (*SetAttributeAtTime)(
		NSIContext_t ctx,
		NSIHandle_t object,
		double time,
		int nparams,
		const NSIParam_t *params );

	void (*DeleteAttribute)(
		NSIContext_t ctx,
		NSIHandle_t object,
		const char *name );

	void (*Connect)(
		NSIContext_t ctx,
		NSIHandle_t from,
		const char *from_attr,
		NSIHandle_t to,
		const char *to_attr,
		int nparams,
		const NSIParam_t *params );

	void (*Disconnect)(
		NSIContext_t ctx,
		NSIHandle_t from,
		const char *from_attr,
		NSIHandle_t to,
		const char *to_attr );

	void (*Evaluate)(
		NSIContext_t ctx,
		int nparams,
		const NSIParam_t *params );

	void (*RenderControl)(
		NSIContext_t ctx,
		int nparams,
		const NSIParam_t *params );
};

}

#endif
