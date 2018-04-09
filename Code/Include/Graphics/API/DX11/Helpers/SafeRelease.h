#pragma once

#if defined(GFX_API_DX11)

#define SAFERELEASE(a_Resource)					\
    if(a_Resource)								\
        a_Resource->lpVtbl->Release(a_Resource);

#endif
