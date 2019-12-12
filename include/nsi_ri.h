#ifndef __nsi_ri_h
#define __nsi_ri_h

#include "nsi.h"
#include "ri.h"

#ifdef  __cplusplus
extern "C" {
#endif

DL_INTERFACE NSIContext_t RiToNSIContext( RtContextHandle handle );
DL_INTERFACE RtContextHandle RiFromNSIContext( NSIContext_t handle );

#ifdef __cplusplus
}
#endif

#endif

