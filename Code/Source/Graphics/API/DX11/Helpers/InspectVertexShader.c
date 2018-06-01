#include "InspectVertexShader.h"

#include "CheckResult.h"
#include "DetermineConstantBuffers.h"
#include "DetermineInputLayout.h"
#include "Graphics/API/DX11/DX11Structs.h"
#include "SafeRelease.h"

#include <assert.h>

#if defined(GFX_API_DX11)

void InspectVertexShader(ID3DBlob *a_ByteCode, D3D11_INPUT_ELEMENT_DESC **a_InputLayoutDesc, uint32_t *a_InputLayoutDataByteSize, D3D11_BUFFER_DESC **a_ConstantBufferDesc, uint32_t *a_NumConstantBuffers)
{
	GFX_UNUSED(a_InputLayoutDesc);
	ID3D11ShaderReflection *reflection = 0;
	CheckResult(D3DReflect(a_ByteCode->lpVtbl->GetBufferPointer(a_ByteCode), a_ByteCode->lpVtbl->GetBufferSize(a_ByteCode), &IID_ID3D11ShaderReflection, &reflection));

	DetermineInputLayout(reflection, a_InputLayoutDesc, a_InputLayoutDataByteSize);
	DetermineConstantBuffers(reflection, a_ConstantBufferDesc, a_NumConstantBuffers);

	SAFERELEASE(reflection);
}

#endif
