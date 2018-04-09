#pragma once

#if defined(GFX_API_DX11)

#define SETDEBUGNAME(a_Resource, a_Name)																			\
	assert(0 != a_Resource);																						\
	assert(0 != &a_Name);																							\
    if(0 != a_Resource)																								\
	{																												\
        a_Resource->lpVtbl->SetPrivateData(a_Resource, &WKPDID_D3DDebugObjectName, (UINT)(strlen(a_Name)), a_Name);	\
	}
#endif
