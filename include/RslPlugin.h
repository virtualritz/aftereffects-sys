#ifndef RSLPLUGIN_H
#define RSLPLUGIN_H

#include "ri.h"
#include "RixInterfaces.h"

#define RSLEXPORT _3DL_ALWAYS_EXPORT

#define RSL_PLUGIN_VERSION 3

typedef unsigned RslRunFlag;
typedef int RslIncrType;

class RslContext : public RixContext
{
public:
	virtual ~RslContext() {}

	virtual const RslRunFlag* GetRunFlags( unsigned *length ) const = 0;

	virtual RixInterface* GetRixInterface( RixInterfaceId id ) const = 0;

	RixStorage* GetGlobalStorage() const
	{
		return (RixStorage*) GetRixInterface( k_RixGlobalData );
	}

	RixStorage* GetThreadStorage() const
	{
		return (RixStorage*) GetRixInterface( k_RixThreadData );
	}

	RixStorage* GetLocalStorage() const
	{
		return (RixStorage*) GetRixInterface( k_RixLocalData );
	}

	void SetThreadData(void* data, RixCleanupFunc cleanup = 0L)
	{
		GetThreadStorage()->Set( GetPluginName(), data, cleanup );
	}

	void* GetThreadData() const
	{
		return GetThreadStorage()->Get( GetPluginName() );
	}

	void SetLocalData(void* data, RixCleanupFunc cleanup = 0L)
	{
		GetLocalStorage()->Set( GetPluginName(), data, cleanup );
	}

	void* GetLocalData() const
	{
		return GetLocalStorage()->Get( GetPluginName() );
	}

	/* Wrapper for easy use of k_RixGlobalTokenData interface. */
	const char* GetToken( const char *input ) const
	{
		return ((RixTokenStorage*) GetRixInterface( k_RixGlobalTokenData ))->
			GetToken( input );
	}

	virtual const char* GetPluginName() const = 0;

private:
	template<typename T> friend class RslIter;
	template<typename T> friend class RslArrayIter;
	friend class RslPatternIter;

	/* Returns an increment list for data with requested stride. */
	virtual const RslIncrType* getIncrList( unsigned stride ) const = 0;
};

class RslArg;

class RslArg_v2
{
public:
	virtual ~RslArg_v2() {}

	virtual bool IsFloat() const = 0;
	virtual bool IsPoint() const = 0;
	virtual bool IsVector() const = 0;
	virtual bool IsColor() const = 0;
	virtual bool IsString() const = 0;
	virtual bool IsMatrix() const = 0;
	virtual bool IsArray() const = 0;
	virtual bool IsVarying() const = 0;

	virtual int GetArrayLength() const = 0;

	virtual unsigned NumValues() const = 0;

	static unsigned NumValues(int argc, const RslArg* const* argv);

	/* Use this at your own risk; it will not always work. */
	virtual void GetData(float** data, int* stride) const = 0;

private:

	/* Stuff used to build iterators. */
	template<typename T> friend class RslIter;
	template<typename T> friend class RslArrayIter;

	virtual void getInfo(
		float** data, const RslIncrType** incrList, bool* isVarying ) const = 0;

	virtual void getArrayInfo(
		float** data, const RslIncrType** incrList,
		int* arrayLength, bool* isVarying ) const = 0;
};

class RslArg : public RslArg_v2
{
public:
	virtual bool IsNormal() const = 0;
	virtual bool IsWriteable() const = 0;

	virtual ~RslArg() {}
};

inline unsigned RslArg_v2::NumValues(int argc, const RslArg* const* argv)
{
	int m = 1;
	for( int i = 0; i < argc; ++i )
	{
		int n = argv[i]->NumValues();
		if( n > m )
			m = n;
	}

	return m;
}

template<typename T>
class RslIter
{
public:
	RslIter(const RslArg* arg)
	{
		arg->getInfo(&m_data, &m_incrList, &m_isVarying);
	}

	RslIter(const T* data, const RslContext* ctx)
	:
		m_data((float*) data),
		m_incrList(ctx->getIncrList(0)),
		m_isVarying(false)
	{
	}

	T& operator*() { return *((T*) m_data); }

	const T& operator*() const { return *((T*) m_data); }

	RslIter<T>& operator++() 
	{
		m_data += *m_incrList;
		++m_incrList;
		return *this;
	};
 
	RslIter<T> operator++(int) 
	{
		RslIter<T> temp = *this;
		++*this;
		return temp;
	};

	bool IsVarying() const { return m_isVarying; }

private:
	/* Pointer to current data element (not necessarily a float). */
	float* m_data;

	/* Pointer to the next value to use in the increment list. */
	const RslIncrType* m_incrList;

	/*
		For IsVarying(), true if the underlying data is varying (or an access
		to a uniform array using a varying index).
	*/
	bool m_isVarying;
};

template<typename T>
class RslArrayIter
{
public:
	RslArrayIter(const RslArg* arg)
	{
		arg->getArrayInfo( &m_data, &m_incrList, &m_length, &m_isVarying );
	}

	RslArrayIter(const T* data, int length, const RslContext* ctx)
	:
		m_data((float*) data),
		m_incrList(ctx->getIncrList(0)),
		m_length(length),
		m_isVarying(false)
	{
	}

	T* operator*() { return (T*) m_data; }
	T&  operator[](int x) { return ((T*)m_data)[x]; }

	RslArrayIter<T>& operator++() 
	{
		m_data += *m_incrList * m_length;
		++m_incrList;
		return *this;
	};

	RslArrayIter<T> operator++(int) 
	{
		RslArrayIter<T> temp = *this;
		++*this;
		return temp;
	};

	bool IsVarying() const { return m_isVarying; }

	int GetLength() const { return m_length; }

private:

	/* Pointer to current data element (not necessarily a float). */
	float* m_data;

	/* Pointer to the next value to use in the increment list. */
	const RslIncrType* m_incrList;

	/*
		Array length. For dynamically sized arrays with a varying size, this is
		the maximum length of all data elements.
	*/
	int m_length;

	/* For IsVarying(), true if the underlying data is varying.	*/
	bool m_isVarying;
};


typedef RslIter<RtFloat>        RslFloatIter;        
typedef RslIter<RtString>       RslStringIter;       
typedef RslIter<RtColor>        RslColorIter;        
typedef RslIter<RtVector>       RslVectorIter;       
typedef RslIter<RtNormal>       RslNormalIter;       
typedef RslIter<RtPoint>        RslPointIter;        
typedef RslIter<RtMatrix>       RslMatrixIter;       

typedef RslArrayIter<RtFloat>   RslFloatArrayIter;   
typedef RslArrayIter<RtString>  RslStringArrayIter;  
typedef RslArrayIter<RtColor>   RslColorArrayIter;   
typedef RslArrayIter<RtVector>  RslVectorArrayIter;  
typedef RslArrayIter<RtNormal>  RslNormalArrayIter;  
typedef RslArrayIter<RtPoint>   RslPointArrayIter;    
typedef RslArrayIter<RtMatrix>  RslMatrixArrayIter;   


class RslPatternIter
{
public:
	RslPatternIter( const RslContext *ctx )
	{
		m_patternInterface =
			(RixSamplingPattern*) ctx->GetRixInterface( k_RixSamplingPattern );
		m_incrList = ctx->getIncrList( 1 );
		m_state[0] = *m_incrList;
		m_state[1] = -1;
		m_state[2] = 0;
		m_state[3] = 0;
		++m_incrList;
	}

	void operator++()
	{
		m_state[0] += *m_incrList;
		m_state[3] += 1;
		++m_incrList;
	}

	template <typename T>
	void AddSeed( RslIter<T> &it )
	{
		m_patternInterface->AddSeed( m_state, &*it, sizeof(T) );
	}

	float value( int dimension ) const
	{
		return m_patternInterface->Pattern( m_state, dimension );
	}

private:
	/* Internal state. */
	RtInt m_state[4];

	/* Sampling pattern interface. Where the work is actually done. */
	const RixSamplingPattern *m_patternInterface;

	/* Pointer to the next value to use in the increment list. */
	const RslIncrType* m_incrList;

};

typedef int (*RslEntryFunc)( RslContext* ctx, int argc, const RslArg** argv );
typedef void (*RslVoidFunc)( RixContext* context );

struct RslFunction
{
	const char *m_prototype;
	RslEntryFunc m_entry;
	RslVoidFunc m_initFunc;
	RslVoidFunc m_cleanupFunc;
};

struct RslFunctionTable
{
	const RslFunction* m_functions;
	const char m_version;
	RslVoidFunc m_initFunc;
	RslVoidFunc m_cleanupFunc;

	RslFunctionTable(
		const RslFunction* functions,
		RslVoidFunc init = NULL,
		RslVoidFunc cleanup = NULL)
	:
		m_functions(functions),
		m_version(RSL_PLUGIN_VERSION),
		m_initFunc(init),
		m_cleanupFunc(cleanup)
	{
	}
};

#endif

