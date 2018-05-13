#include "InspectVertexShader.h"

#include "DetermineConstantBuffers.h"
#include "Graphics/API/DX11/DX11Structs.h"

#include <assert.h>

#if defined(GFX_API_DX11)

void InspectVertexShader(ID3DBlob *a_ByteCode, DX11ConstantBuffer **a_ConstantBufferDescs)
{
	ID3D11ShaderReflection *reflection = 0;
	HRESULT result = D3DReflect(a_ByteCode->lpVtbl->GetBufferPointer(a_ByteCode), a_ByteCode->lpVtbl->GetBufferSize(a_ByteCode), &IID_ID3D11ShaderReflection, &reflection);
#if !defined(NDEBUG)
	assert(S_OK == result);
#else
	GFX_UNUSED(result);
#endif

	DetermineConstantBuffers(reflection, a_ConstantBufferDescs);
}

#endif
