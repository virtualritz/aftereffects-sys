#ifndef RIX_INTERFACE_H
#define RIX_INTERFACE_H

#include <stddef.h>

enum RixInterfaceId
{
	k_RixThreadUtils = 0,
	k_RixMessages,
	k_RixStats,
	k_RixGlobalData,
	k_RixThreadData,
	k_RixLocalData,
	k_RixGlobalTokenData,
	k_RixSamplingPattern = 1000
};

class RixInterface
{
public:
	virtual int GetVersion() const { return m_version; }

protected:
	int m_version;

	RixInterface( int version ) : m_version(version) {}

	virtual ~RixInterface() {}
};

class RixContext
{
public:
	virtual RixInterface* GetRixInterface(RixInterfaceId id) const;

	virtual ~RixContext();
};

class RixMutex
{
public:
	virtual ~RixMutex() {}

	virtual void Lock() = 0;
	virtual void Unlock() = 0;
};

class RixConditionVariable
{
public:
	virtual ~RixConditionVariable() {}

	virtual void Wait( RixMutex *mutex ) = 0;
	virtual void Signal() = 0;
	virtual void Broadcast() = 0;
};

class RixThreadUtils : public RixInterface
{
public:
	virtual RixMutex* NewMutex() const = 0;
	virtual RixConditionVariable* NewConditionVariable() const = 0;

protected:
	RixThreadUtils() : RixInterface(1) { }
};


class RixMessages : public RixInterface
{
public:
	virtual void Error( const char* format, ... ) = 0;
	virtual void ErrorAlways( const char* format, ... ) = 0;

	virtual void Warning( const char* format, ... ) = 0;
	virtual void WarningAlways( const char* format, ... ) = 0;

	virtual void Info( const char* format, ... ) = 0;
	virtual void InfoAlways( const char* format, ... ) = 0;

protected:
    RixMessages() : RixInterface(1) {}
};


class RixStats : public RixInterface
{
public:
	virtual void AddTimerStat(
		float* seconds, const char* name, const char* description ) = 0;

	virtual void AddMemoryStat(
		size_t* bytes, const char* name, const char* description ) = 0;

	typedef void (*Reporter)(class RixXmlFile* file);

	virtual void AddReporter( Reporter func ) = 0;

protected:
    RixStats() : RixInterface(1) {}
};


class RixXmlFile
{
public:
	virtual ~RixXmlFile() = 0;

    virtual void WriteXml( const char* format, ... ) = 0;
    virtual void WriteText( const char* format, ... ) = 0;
};

typedef void (*RixCleanupFunc)(RixContext* context, void* data);

class RixStorage : public RixInterface
{
public:
	virtual void* Get( const char* key ) = 0;

	virtual void Set(
		const char* key, void* data, RixCleanupFunc cleanup = NULL ) = 0;

	virtual void Clear( const char* key ) = 0;

	virtual void Lock() = 0;
	virtual void Unlock() = 0;

protected:
    RixStorage() : RixInterface(1) {}
};

/*
	RixTokenStorage

	Use this interface to store strings inside 3Delight in a way which is safe
	for use as returned values from Rsl plug-ins. This interface is currently
	only available from a RslContext (if you need it elsewhere, ask nicely
	enough).
*/
class RixTokenStorage : public RixInterface
{
public:
	/*
		Get a stored token for the given string. The returned string should not
		be freed manually.
	*/
	virtual const char* GetToken( const char *input ) = 0;

protected:
    RixTokenStorage() : RixInterface(1) {}
};

/*
	RixSamplingPattern

	Provides access to the sampling patterns for the RslPatternIter. Should
	probably not be used directly.
*/
class RixSamplingPattern : public RixInterface
{
public:
	virtual void AddSeed(
		int *state, const void *data, size_t datasize ) const = 0;

	virtual float Pattern( const int *state, int dimension ) const = 0;

protected:
	RixSamplingPattern() : RixInterface(1) {}
};

#endif

