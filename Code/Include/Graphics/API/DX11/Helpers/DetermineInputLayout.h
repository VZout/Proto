#pragma once

#include "Graphics/API/DX11/DX11Includes.h"
#include "Graphics/API/DX11/DX11Structs.h"

#if defined(GFX_API_DX11)

void DetermineInputLayout(ID3D11ShaderReflection *a_ReflectionInterface, D3D11_INPUT_ELEMENT_DESC **a_InputLayoutDesc, uint32_t *a_DataByteSize);

#endif