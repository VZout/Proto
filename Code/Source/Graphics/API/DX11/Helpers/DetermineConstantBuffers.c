#include "DetermineConstantBuffers.h"

#include "CheckResult.h"
#include "Graphics/API/DX11/DX11Structs.h"

#include <assert.h>

#if defined(GFX_API_DX11)

void DetermineConstantBuffers(ID3D11ShaderReflection *a_ReflectionInterface, DX11ConstantBuffer **a_ConstantBuffers)
{
	D3D11_SHADER_DESC description;
	a_ReflectionInterface->lpVtbl->GetDesc(a_ReflectionInterface, &description);

	if (0 != description.ConstantBuffers)
	{
		*a_ConstantBuffers = ALLOCATEARRAY(DX11ConstantBuffer, description.ConstantBuffers);
		assert(0 != a_ConstantBuffers);

		ID3D11ShaderReflectionConstantBuffer *constantBuffer = 0;
		for (UINT index = 0; index < description.ConstantBuffers; ++index)
		{
			constantBuffer = a_ReflectionInterface->lpVtbl->GetConstantBufferByIndex(a_ReflectionInterface, index);
			assert(0 != constantBuffer);

			D3D11_SHADER_BUFFER_DESC bufferDesc;
			CheckResult(constantBuffer->lpVtbl->GetDesc(constantBuffer, &bufferDesc));
			a_ConstantBuffers[index]->m_Size = bufferDesc.Size;

			size_t stringLength;
#if !defined(NDEBUG)
			stringLength = strlen(bufferDesc.Name) + 1;
			a_ConstantBuffers[index]->m_Name = (char*)malloc(stringLength);
			strcpy_s(a_ConstantBuffers[index]->m_Name, stringLength, bufferDesc.Name);
#endif

			a_ConstantBuffers[index]->m_NumElements = bufferDesc.Variables;
			size_t byteSize = bufferDesc.Variables * sizeof(DX11ConstantBufferElement);
			a_ConstantBuffers[index]->m_Elements = (DX11ConstantBufferElement*)malloc(byteSize);
			memset(a_ConstantBuffers[index]->m_Elements, 0, byteSize);

			for (UINT variableIndex = 0; variableIndex < bufferDesc.Variables; ++variableIndex)
			{
				ID3D11ShaderReflectionVariable *constantBufferVariable = constantBuffer->lpVtbl->GetVariableByIndex(constantBuffer, variableIndex);
				D3D11_SHADER_VARIABLE_DESC variableDesc;
				constantBufferVariable->lpVtbl->GetDesc(constantBufferVariable, &variableDesc);

				stringLength = strlen(variableDesc.Name) + 1;
				a_ConstantBuffers[index]->m_Elements[variableIndex].m_Name = (char*)malloc(stringLength);
				strcpy_s(a_ConstantBuffers[index]->m_Elements[variableIndex].m_Name, stringLength, variableDesc.Name);
				a_ConstantBuffers[index]->m_Elements[variableIndex].m_Size = variableDesc.Size;
				a_ConstantBuffers[index]->m_Elements[variableIndex].m_Offset = variableDesc.StartOffset;
			}
		}
	}
}

#endif
