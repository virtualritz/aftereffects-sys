#ifndef __nsi_hpp
#define __nsi_hpp

#include "nsi.h"

#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>

namespace NSI
{

/* Interface which provides the C API. */
class CAPI
{
public:
	virtual ~CAPI() {}

	virtual NSIContext_t NSIBegin(
		int nparams,
		const NSIParam_t *params ) const = 0;

	virtual void NSIEnd(
		NSIContext_t ctx ) const = 0;

	virtual void NSICreate(
		NSIContext_t ctx,
		NSIHandle_t handle,
		const char *type,
		int nparams,
		const NSIParam_t *params ) const = 0;

	virtual void NSIDelete(
		NSIContext_t ctx,
		NSIHandle_t handle,
		int nparams,
		const NSIParam_t *params ) const = 0;

	virtual void NSISetAttribute(
		NSIContext_t ctx,
		NSIHandle_t object,
		int nparams,
		const NSIParam_t *params ) const = 0;

	virtual void NSISetAttributeAtTime(
		NSIContext_t ctx,
		NSIHandle_t object,
		double time,
		int nparams,
		const NSIParam_t *params ) const = 0;

	virtual void NSIDeleteAttribute(
		NSIContext_t ctx,
		NSIHandle_t object,
		const char *name ) const = 0;

	virtual void NSIConnect(
		NSIContext_t ctx,
		NSIHandle_t from,
		const char *from_attr,
		NSIHandle_t to,
		const char *to_attr,
		int nparams,
		const NSIParam_t *params ) const = 0;

	virtual void NSIDisconnect(
		NSIContext_t ctx,
		NSIHandle_t from,
		const char *from_attr,
		NSIHandle_t to,
		const char *to_attr ) const = 0;

	virtual void NSIEvaluate(
		NSIContext_t ctx,
		int nparams,
		const NSIParam_t *params ) const = 0;

	virtual void NSIRenderControl(
		NSIContext_t ctx,
		int nparams,
		const NSIParam_t *params ) const = 0;
};

/* Default API provider, used when linking directly with the renderer. */
class LinkedAPI : public CAPI
{
public:
	static CAPI& Instance() { static LinkedAPI api; return api; }

	virtual NSIContext_t NSIBegin(
		int nparams,
		const NSIParam_t *params ) const
	{
		return ::NSIBegin( nparams, params );
	}

	virtual void NSIEnd(
		NSIContext_t ctx ) const
	{
		::NSIEnd( ctx );
	}

	virtual void NSICreate(
		NSIContext_t ctx,
		NSIHandle_t handle,
		const char *type,
		int nparams,
		const NSIParam_t *params ) const
	{
		::NSICreate( ctx, handle, type, nparams, params );
	}

	virtual void NSIDelete(
		NSIContext_t ctx,
		NSIHandle_t handle,
		int nparams,
		const NSIParam_t *params ) const
	{
		::NSIDelete( ctx, handle, nparams, params );
	}

	virtual void NSISetAttribute(
		NSIContext_t ctx,
		NSIHandle_t object,
		int nparams,
		const NSIParam_t *params ) const
	{
		::NSISetAttribute( ctx, object, nparams, params );
	}

	virtual void NSISetAttributeAtTime(
		NSIContext_t ctx,
		NSIHandle_t object,
		double time,
		int nparams,
		const NSIParam_t *params ) const
	{
		::NSISetAttributeAtTime( ctx, object, time, nparams, params );
	}

	virtual void NSIDeleteAttribute(
		NSIContext_t ctx,
		NSIHandle_t object,
		const char *name ) const
	{
		::NSIDeleteAttribute( ctx, object, name );
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
		::NSIConnect( ctx, from, from_attr, to, to_attr, nparams, params );
	}

	virtual void NSIDisconnect(
		NSIContext_t ctx,
		NSIHandle_t from,
		const char *from_attr,
		NSIHandle_t to,
		const char *to_attr ) const
	{
		::NSIDisconnect( ctx, from, from_attr, to, to_attr );
	}

	virtual void NSIEvaluate(
		NSIContext_t ctx,
		int nparams,
		const NSIParam_t *params ) const
	{
		::NSIEvaluate( ctx, nparams, params );
	}

	virtual void NSIRenderControl(
		NSIContext_t ctx,
		int nparams,
		const NSIParam_t *params ) const
	{
		::NSIRenderControl( ctx, nparams, params );
	}
};

class ArgBase;

/*
	StaticArgumentListProxy is a linked list of ArgBase references which is
	eventually flattened into an array of NSIParam_t.

	What it allows is convenient syntax to build a list of static length
	inline:

	ctx.SetAttribute( "handle",
		(
			NSI::IntegerArg( "arg1", 1 ),
			NSI::StringArg( "arg2", "2" )
		) );
*/
template<unsigned N>
class StaticArgumentListProxy
{
public:
	StaticArgumentListProxy(
		const ArgBase &a,
		const StaticArgumentListProxy<N-1> &prev )
	:
		m_arg( a ), m_prev( prev )
	{
	}

	/* Write the list to a contiguous NSIParam_t array, from the end. */
	inline void FlattenList( NSIParam_t *p ) const;

	/* This appends an argument to an existing list. */
	StaticArgumentListProxy<N+1> operator,( const ArgBase &a ) const
	{
		return StaticArgumentListProxy<N+1>( a, *this );
	}

private:
	const ArgBase &m_arg;
	const StaticArgumentListProxy<N-1> &m_prev;
};


/*
	This template specialization exists so the object can be built directly
	from ArgBase's operator, without using any temporaries.

	It also ends the recursive list. The the reason above is why it does not
	end with a <0> specialization which would have been much simpler.
*/
template<>
class StaticArgumentListProxy<2>
{
public:
	StaticArgumentListProxy(
		const ArgBase &a0,
		const ArgBase &a1 )
	:
		m_arg0( a0 ), m_arg1( a1 )
	{
	}

	/* Write the list to a contiguous NSIParam_t array, from the end. */
	inline void FlattenList( NSIParam_t *p ) const;

	/* This appends an argument to an existing list. */
	StaticArgumentListProxy<3> operator,( const ArgBase &a ) const
	{
		return StaticArgumentListProxy<3>( a, *this );
	}

private:
	const ArgBase &m_arg0;
	const ArgBase &m_arg1;
};


class ArgBase
{
	/* Arguments are not meant to be copied around. */
	ArgBase( const ArgBase& );
	void operator=( const ArgBase& );

public:
	/*
		It is a convention that argument names provided as C strings are not
		copied (caller must keep the string valid) while the names provided as
		C++ string are copied. This should fit with the general behavior of C
		vs C++ strings.
	*/
	ArgBase( const char *name )
	:
		m_name( name ), m_name_buf( 0 )
	{
	}

	ArgBase( const std::string &name )
	:
		m_name_buf( new char[name.size() + 1u] )
	{
		m_name = m_name_buf;
		m_name_buf[ name.copy( m_name_buf, std::string::npos ) ] = 0;
	}

	virtual ~ArgBase()
	{
		if( m_name_buf )
			delete[] m_name_buf;
	}

	/* This starts building a list from (arg, arg). */
	StaticArgumentListProxy<2> operator,( const ArgBase &arg )
	{
		return StaticArgumentListProxy<2>( *this, arg );
	}

	virtual void FillNSIParam( NSIParam_t &p ) const = 0;

protected:
	const char *m_name;
	/* When we own the name string, this points to it. Otherwise 0. */
	char *m_name_buf;
};


template<unsigned N>
void StaticArgumentListProxy<N>::FlattenList( NSIParam_t *p ) const
{
	m_arg.FillNSIParam( *p );
	m_prev.FlattenList( p - 1 );
}

void StaticArgumentListProxy<2>::FlattenList( NSIParam_t *p ) const
{
	m_arg1.FillNSIParam( p[0] );
	m_arg0.FillNSIParam( p[-1] );
}


/*
	Generic argument class to handle what is not easily done with the more
	specific classes.
*/
class Argument : public ArgBase
{
public:
	Argument( const char *name )
	:
		ArgBase( name ),
		m_data_buffer( 0 )
	{
		m_param.name = m_name;
		m_param.data = 0;
		m_param.type = NSITypeInvalid;
		m_param.arraylength = 0;
		m_param.count = 1;
		m_param.flags = 0;
	}

	Argument( const std::string &name )
	:
		ArgBase( name ),
		m_data_buffer( 0 )
	{
		m_param.name = m_name;
		m_param.data = 0;
		m_param.type = NSITypeInvalid;
		m_param.arraylength = 0;
		m_param.count = 1;
		m_param.flags = 0;
	}

	virtual ~Argument()
	{
		if( m_data_buffer )
			std::free( m_data_buffer );
	}

	/*
		Those two, along with the SetXX returning this, are to support adding
		arguments to an ArgumentList without using a variable to hold the
		pointer. eg.

		argument_list.Add(
			Argument::New( "attributename" )
			->SetType( NSITypeInteger )
			->SetCount( 4 )
			->CopyValue( att_value, 4*sizeof(int) ) );
	*/
	static Argument* New( const char *name )
		{ return new Argument( name ); }
	static Argument* New( const std::string &name )
		{ return new Argument( name ); }

	virtual void FillNSIParam( NSIParam_t &p ) const
	{
		p = m_param;
	}

	Argument* SetType( NSIType_t type )
	{
		m_param.type = type;
		m_param.flags &= ~int(NSIParamIsArray);
		return this;
	}

	Argument* SetArrayType( NSIType_t type, size_t arraylength )
	{
		m_param.type = type;
		m_param.arraylength = int(arraylength);
		m_param.flags |= NSIParamIsArray;
		return this;
	}

	Argument* SetCount( size_t count ) { m_param.count = count; return this; }

	void* AllocValue( size_t value_size )
	{
		if( m_data_buffer )
			std::free( m_data_buffer );
		m_data_buffer = std::malloc( value_size );
		m_param.data = m_data_buffer;
		return m_data_buffer;
	}

	Argument* CopyValue( const void *value, size_t value_size )
	{
		std::memcpy( AllocValue( value_size ), value, value_size );
		return this;
	}

	Argument* SetValuePointer( const void *value )
	{
		m_param.data = value;
		return this;
	}

	Argument* SetFlags( int flags )
	{
		m_param.flags |= flags;
		return this;
	}

	Argument* ResetFlags( int flags )
	{
		m_param.flags &= ~flags;
		return this;
	}

private:
	NSIParam_t m_param;
	void *m_data_buffer;
};

class IntegerArg : public ArgBase
{
public:
	IntegerArg( const char *name, int v )
	:
		ArgBase( name ), m_v( v )
	{
	}

	IntegerArg( const std::string &name, int v )
	:
		ArgBase( name ), m_v( v )
	{
	}

	virtual void FillNSIParam( NSIParam_t &p ) const
	{
		p.name = m_name;
		p.data = &m_v;
		p.type = NSITypeInteger;
		p.count = 1;
		p.flags = 0;
	}

private:
	int m_v;
};

class FloatArg : public ArgBase
{
public:
	FloatArg( const char *name, float v )
	:
		ArgBase( name ), m_v( v )
	{
	}

	FloatArg( const std::string &name, float v )
	:
		ArgBase( name ), m_v( v )
	{
	}

	virtual void FillNSIParam( NSIParam_t &p ) const
	{
		p.name = m_name;
		p.data = &m_v;
		p.type = NSITypeFloat;
		p.count = 1;
		p.flags = 0;
	}

private:
	float m_v;
};

class DoubleArg : public ArgBase
{
public:
	DoubleArg( const char *name, double v )
	:
		ArgBase( name ), m_v( v )
	{
	}

	DoubleArg( const std::string &name, double v )
	:
		ArgBase( name ), m_v( v )
	{
	}

	virtual void FillNSIParam( NSIParam_t &p ) const
	{
		p.name = m_name;
		p.data = &m_v;
		p.type = NSITypeDouble;
		p.count = 1;
		p.flags = 0;
	}

private:
	double m_v;
};

class ColorArg : public ArgBase
{
public:
	ColorArg( const char *name, const float *v )
	:
		ArgBase( name )
	{
		m_v[0] = v[0];
		m_v[1] = v[1];
		m_v[2] = v[2];
	}

	ColorArg( const std::string &name, const float *v )
	:
		ArgBase( name )
	{
		m_v[0] = v[0];
		m_v[1] = v[1];
		m_v[2] = v[2];
	}

	virtual void FillNSIParam( NSIParam_t &p ) const
	{
		p.name = m_name;
		p.data = &m_v[0];
		p.type = NSITypeColor;
		p.count = 1;
		p.flags = 0;
	}

private:
	float m_v[3];
};

class DoubleMatrixArg : public ArgBase
{
public:
	DoubleMatrixArg( const char *name, const double *v )
	:
		ArgBase( name )
	{
		for( int i=0; i<16; i++ )
			m_v[i] = v[i];
	}

	DoubleMatrixArg( const std::string &name, const double *v )
	:
		ArgBase( name )
	{
		for( int i=0; i<16; i++ )
			m_v[i] = v[i];
	}

	virtual void FillNSIParam( NSIParam_t &p ) const
	{
		p.name = m_name;
		p.data = &m_v[0];
		p.type = NSITypeDoubleMatrix;
		p.count = 1;
		p.flags = 0;
	}

private:
	double m_v[16];
};

/*
	This does not make a copy of the given string. Use StringArg if that string
	is shorter lived than the argument list.
*/
class CStringPArg : public ArgBase
{
public:
	CStringPArg( const char *name, const char *v )
	:
		ArgBase( name ), m_v( v )
	{
	}

	CStringPArg( const std::string &name, const char *v )
	:
		ArgBase( name ), m_v( v )
	{
	}

	virtual void FillNSIParam( NSIParam_t &p ) const
	{
		p.name = m_name;
		p.data = &m_v;
		p.type = NSITypeString;
		p.count = 1;
		p.flags = 0;
	}

private:
	const char *m_v;
};

class StringArg : public ArgBase
{
public:
	StringArg( const char *name, const char *v )
	:
		ArgBase( name ), m_s( v )
	{
	}

	StringArg( const std::string &name, const char *v )
	:
		ArgBase( name ), m_s( v )
	{
	}

	StringArg( const char *name, const std::string &v )
	:
		ArgBase( name ), m_s( v )
	{
	}

	StringArg( const std::string &name, const std::string &v )
	:
		ArgBase( name ), m_s( v )
	{
	}

	virtual void FillNSIParam( NSIParam_t &p ) const
	{
		m_v = m_s.c_str();
		p.name = m_name;
		p.data = &m_v;
		p.type = NSITypeString;
		p.count = 1;
		p.flags = 0;
	}

private:
	std::string m_s;
	mutable const char *m_v;
};


class PointerArg : public ArgBase
{
public:
	PointerArg( const char *name, const void *v )
	:
		ArgBase( name ), m_v( v )
	{
	}

	PointerArg( const std::string &name, const void *v )
	:
		ArgBase( name ), m_v( v )
	{
	}

	virtual void FillNSIParam( NSIParam_t &p ) const
	{
		p.name = m_name;
		p.data = &m_v;
		p.type = NSITypePointer;
		p.count = 1;
		p.flags = 0;
	}

private:
	const void *m_v;
};


class ArgumentList
{
	ArgumentList( const ArgumentList& );
	void operator=( const ArgumentList& );
public:
	ArgumentList() {}

	~ArgumentList() { clear(); }

	void clear()
	{
		while( !m_args.empty() )
		{
			delete m_args.back();
			m_args.pop_back();
		}
	}

	bool empty() const { return m_args.empty(); }

	size_t size() const { return m_args.size(); }
	const ArgBase* operator[]( size_t i ) const { return m_args[i]; }

	void Add( ArgBase *arg )
	{
		m_args.push_back( arg );
	}

	void push( ArgBase *arg )
	{
		m_args.push_back( arg );
	}

	void push_back( ArgBase *arg )
	{
		m_args.push_back( arg );
	}


private:
	std::vector<ArgBase*> m_args;
};
typedef ArgumentList DynamicArgumentList; /* backward compatibility */




class Context
{
	/*
		Don't allow copying because ownership semantics get really messy. If
		you really know what you're doing, use the Handle() method and build
		another context from it.
	*/
	Context( const Context& );
	void operator=( const Context& );

private:
	class FlatArgumentList
	{
		void operator=( const FlatArgumentList& );
#if __cplusplus < 201103L
	/* Stupid rule with old C++ requires this to be visible. */
	public:
#endif
		FlatArgumentList( const FlatArgumentList& );

	public:
		/* Empty list. */
		FlatArgumentList()
		:
			m_nsi_params( 0 ),
			m_size_nsi_params( 0 )
		{
		}

		/* From dynamically built argument list. */
		FlatArgumentList( const ArgumentList &arglist )
		{
			m_size_nsi_params = arglist.size();
			m_nsi_params = new NSIParam_t[ m_size_nsi_params ];
			for( unsigned i = 0; i < m_size_nsi_params; ++i )
			{
				arglist[i]->FillNSIParam( m_nsi_params[i] );
			}
		}

		/* From a static argument list. */
		template<unsigned N>
		FlatArgumentList( const StaticArgumentListProxy<N> &arglist )
		{
			m_size_nsi_params = N;
			m_nsi_params = new NSIParam_t[ m_size_nsi_params ];
			arglist.FlattenList( m_nsi_params + N - 1u );
		}

		/* From a single argument. */
		FlatArgumentList( const ArgBase &arg )
		{
			m_size_nsi_params = 1;
			m_nsi_params = new NSIParam_t[ m_size_nsi_params ];
			arg.FillNSIParam( m_nsi_params[0] );
		}

		~FlatArgumentList()
		{
			delete[] m_nsi_params;
		}

		int size() const { return int(m_size_nsi_params); }
		const NSIParam_t* list() const { return m_nsi_params; }

	private:
		mutable NSIParam_t *m_nsi_params;
		mutable size_t m_size_nsi_params;
	};

public:
	/* Deprecated. */
	explicit Context( NSIContext_t ctx )
	:
		m_ctx( ctx ),
		m_owns_context( false ),
		m_api( LinkedAPI::Instance() )
	{
	}

	Context( const CAPI &api = LinkedAPI::Instance() )
	:
		m_ctx( NSI_BAD_CONTEXT ),
		m_owns_context( false ),
		m_api( api )
	{
	}

	/* Destroys the context, if owned by this object. */
	~Context()
	{
		if( m_owns_context )
			End();
	}

	/*
		Use an existing C API handle. The context will not be destroyed with
		this object but End() may be called explicitly to destroy it.
	*/
	void SetHandle( NSIContext_t ctx )
	{
		if( m_owns_context && m_ctx != NSI_BAD_CONTEXT )
			End();

		m_ctx = ctx;
		m_owns_context = false;
	}

	/* Retrieve the C API handle. */
	NSIContext_t Handle() const { return m_ctx; }

	/* Create a new context. */
	void Begin( const FlatArgumentList &params = FlatArgumentList() )
	{
		if( m_owns_context && m_ctx != NSI_BAD_CONTEXT )
			End();

		m_ctx = m_api.NSIBegin( params.size(), params.list() );
		m_owns_context = true;
	}

	/* Destroy the context. */
	void End()
	{
		m_api.NSIEnd( m_ctx );
		m_ctx = NSI_BAD_CONTEXT;
		m_owns_context = false;
	}

	void Create(
		const std::string &handle,
		const std::string &type,
		const FlatArgumentList &params = FlatArgumentList() )
	{
		m_api.NSICreate(
			m_ctx,
			handle.c_str(),
			type.c_str(),
			params.size(), params.list() );
	}

	void Delete(
		const std::string &handle,
		const FlatArgumentList &params = FlatArgumentList() )
	{
		m_api.NSIDelete(
			m_ctx,
			handle.c_str(),
			params.size(), params.list() );
	}

	void SetAttribute(
		const std::string &object,
		const FlatArgumentList &params = FlatArgumentList() )
	{
		m_api.NSISetAttribute(
			m_ctx,
			object.c_str(),
			params.size(), params.list() );
	}

	void SetAttributeAtTime(
		const std::string &object,
		double time,
		const FlatArgumentList &params = FlatArgumentList() )
	{
		m_api.NSISetAttributeAtTime(
			m_ctx,
			object.c_str(),
			time,
			params.size(), params.list() );
	}

	void DeleteAttribute(
		const std::string &object,
		const std::string &name )
	{
		m_api.NSIDeleteAttribute(
			m_ctx,
			object.c_str(),
			name.c_str() );
	}

	void Connect(
		const std::string &from,
		const std::string &from_attr,
		const std::string &to,
		const std::string &to_attr,
		const FlatArgumentList &params = FlatArgumentList() )
	{
		m_api.NSIConnect(
			m_ctx,
			from.c_str(),
			from_attr.c_str(),
			to.c_str(),
			to_attr.c_str(),
			params.size(), params.list() );
	}

	void Disconnect(
		const std::string &from,
		const std::string &from_attr,
		const std::string &to,
		const std::string &to_attr,
		const FlatArgumentList &params = FlatArgumentList() )
	{
		m_api.NSIDisconnect(
			m_ctx,
			from.c_str(),
			from_attr.c_str(),
			to.c_str(),
			to_attr.c_str() );
	}

	void Evaluate(
		const FlatArgumentList &params = FlatArgumentList() )
	{
		m_api.NSIEvaluate(
			m_ctx,
			params.size(), params.list() );
	}

	void RenderControl(
		const FlatArgumentList &params = FlatArgumentList() )
	{
		m_api.NSIRenderControl(
			m_ctx,
			params.size(), params.list() );
	}

private:
	NSIContext_t m_ctx;
	bool m_owns_context;
	const CAPI &m_api;
};

};

#endif
