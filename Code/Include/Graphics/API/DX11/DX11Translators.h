#pragma once

#include "Graphics/API/Enums.h"
#include "Graphics/API/DX11/DX11Includes.h"

#include <stdint.h>

#if defined(GFX_API_DX11)

D3D11_FILL_MODE TranslateFillMode(GFXFillMode a_FillMode);
// GLint TranslateShaderType(GFXShaderType a_ShaderType);
// 
// const char* TranslateVertexAttribute(GFXVertexAttribute a_VertexAttribute);
// GLuint GetVertexAttributeLocation(GFXVertexAttribute a_VertexAttribute);
// 
// GLenum TranslateDataType(GFXDataType a_DataType);
D3D11_PRIMITIVE_TOPOLOGY TranslateRenderMode(GFXRenderMode a_RenderMode);
D3D11_USAGE TranslateUsage(GFXUsage a_Usage);
DXGI_FORMAT TranslateTextureFormat(GFXTextureFormat a_TextureFormat);

LPCSTR TranslateSemantic(const char *a_Name);
DXGI_FORMAT TranslateFormat(GFXDataType a_Type, uint32_t a_Size);

#endif