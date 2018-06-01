#pragma once

#include "Graphics/API/DX11/DX11Includes.h"
#include "Graphics/API/DX11/DX11Structs.h"

#if defined(GFX_API_DX11)

void InspectVertexShader(ID3DBlob *a_ByteCode, D3D11_INPUT_ELEMENT_DESC **inputLayoutDesc, uint32_t *a_InputLayoutDataByteSize, D3D11_BUFFER_DESC **a_ConstantBufferDesc, uint32_t *a_NumConstantBuffers);

#endif
