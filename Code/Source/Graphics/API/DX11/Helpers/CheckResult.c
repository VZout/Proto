#include "CheckResult.h"

#include <assert.h>

void CheckResult(HRESULT a_Result)
{
#if !defined(NDEBUG)
	assert(S_OK == a_Result);
#else
	GFX_UNUSED(a_Result);
#endif
}
