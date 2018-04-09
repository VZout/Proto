#pragma once

#include "Graphics/API/Enums.h"
#include "Graphics/API/OpenGLES/OpenGLESIncludes.h"

#if defined(GFX_API_OPENGLES)

void TranslateFillMode(GFXFillMode a_FillMode);
GLint TranslateShaderType(GFXShaderType a_ShaderType);

const char* TranslateVertexAttribute(GFXVertexAttribute a_VertexAttribute);
GLuint GetVertexAttributeLocation(GFXVertexAttribute a_VertexAttribute);

GLenum TranslateDataType(GFXDataType a_DataType);
GLenum TranslateRenderMode(GFXRenderMode a_RenderMode);
GLenum TranslateUsage(GFXUsage a_Usage);
GLenum TranslateTextureFormat(GFXTextureFormat a_TextureFormat);

#endif