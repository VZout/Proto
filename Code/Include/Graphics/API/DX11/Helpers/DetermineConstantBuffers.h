#pragma once

#include "Graphics/API/DX11/DX11Includes.h"
#include "Graphics/API/DX11/DX11Structs.h"

#if defined(GFX_API_DX11)

void DetermineConstantBuffers(ID3D11ShaderReflection *a_Reflection, D3D11_BUFFER_DESC **a_ConstantBufferDesc, uint32_t *a_NumConstantBuffers);

#endif
