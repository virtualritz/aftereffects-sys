#ifndef __nsicallbacks_h
#define __nsicallbacks_h

/**
	\brief callbacks provide a way to trap NSI calls in a give NSI stream.

	Pass in your callbacks to NSIBegin(). Return true if you want the execution
	to continue in the original context, false otherwise.

	Each call will provide you with the nsicallbacks struct you passed to
	NSIBegin. This allows you to append your variables at the end of an
	extended struct.
*/
struct nsicallbacks
{
	int version;

	bool (*Create)(
		const nsicallbacks *,
		NSIHandle_t handle,
		const char *type,
		int nparams,
		const NSIParam_t *params );

	bool (*Delete)(
		const nsicallbacks *,
		NSIHandle_t handle,
		int nparams,
		const NSIParam_t *params );

	bool (*SetAttribute)(
		const nsicallbacks *,
		NSIHandle_t object,
		int nparams,
		const NSIParam_t *params );

	bool (*SetAttributeAtTime)(
		const nsicallbacks *,
		NSIHandle_t object,
		double time,
		int nparams,
		const NSIParam_t *params );

	bool (*DeleteAttribute)(
		const nsicallbacks *,
		NSIHandle_t object,
		const char *name );

	bool (*Connect)(
		const nsicallbacks *,
		NSIHandle_t from,
		const char *from_attr,
		NSIHandle_t to,
		const char *to_attr,
		int nparams,
		const NSIParam_t *params );

	bool (*Disconnect)(
		const nsicallbacks *,
		NSIHandle_t from,
		const char *from_attr,
		NSIHandle_t to,
		const char *to_attr );

	bool (*Evaluate)(
		const nsicallbacks *,
		int nparams,
		const NSIParam_t *params );

	bool (*RenderControl)(
		const nsicallbacks *,
		int nparams,
		const NSIParam_t *params );
};

#endif
