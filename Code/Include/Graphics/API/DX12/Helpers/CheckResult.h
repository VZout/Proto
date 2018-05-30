#pragma once

#include "Graphics/API/DX12/DX12Includes.h"

#include <assert.h>

#if defined(GFX_API_DX12)

void CheckResult(HRESULT a_Result)
{
#if !defined(NDEBUG)
	assert(S_OK == a_Result);
#else
	GFX_UNUSED(a_Result);
#endif
}

#endif
