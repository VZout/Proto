#pragma once

#include "Graphics/API/Enums.h"
#include "Graphics/API/OpenGL/OpenGLIncludes.h"

#include <stdint.h>

#if defined(GFX_API_OPENGL)

void TranslateFillMode(GFXFillMode a_FillMode);
GLint TranslateShaderType(GFXShaderType a_ShaderType);

const char* TranslateVertexAttribute(GFXVertexAttribute a_VertexAttribute);
GLuint GetVertexAttributeLocation(GFXVertexAttribute a_VertexAttribute);

GLenum TranslateDataType(GFXDataType a_DataType);
GLenum TranslateRenderMode(GFXRenderMode a_RenderMode);
GLenum TranslateUsage(GFXUsage a_Usage);
GLenum TranslateTextureFormat(GFXTextureFormat a_TextureFormat);
GLenum TranslateTextureDataType(uint32_t a_DataByteSize);

uint32_t DataTypeByteSize(GFXDataType a_Type);

#endif