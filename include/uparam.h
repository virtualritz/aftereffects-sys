
#ifndef __uparam_h
#define __uparam_h

typedef struct uparam {

	const char *name;
	char valueType, valueCount;
	const void *value;
	int nbytes;

} UserParameter;

#endif
