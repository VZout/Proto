#include "OpenGLESTranslators.h"

#include "Graphics/API/GFX.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(GFX_API_OPENGLES)

void TranslateFillMode(GFXFillMode a_FillMode)
{
	GFX_UNUSED(a_FillMode);
}

GLint TranslateShaderType(GFXShaderType a_ShaderType)
{
	GLint shaderType = 0;
	switch (a_ShaderType)
	{
	case ShaderType_VertexShader:
		{
			shaderType = GL_VERTEX_SHADER;
			break;
		}
	case ShaderType_FragmentShader:
		{
			shaderType = GL_FRAGMENT_SHADER;
			break;
		}
	case ShaderType_ComputeShader:
	case ShaderType_Geometry:
	case ShaderType_Tesselation:
	default:
		{
			fprintf(stderr, "Invalid shader type encountered!");
			assert(false);
			break;
		}
	}
	return shaderType;
}

// const char* TranslateVertexAttribute(GFXVertexAttribute a_VertexAttribute)
// {
// 	char *vertexAttribute = 0;
// 	switch (a_VertexAttribute)
// 	{
// 	case VertexAttribute_Position:
// 		{
// 			vertexAttribute = "in_Position";
// 			break;
// 		}
// 	case VertexAttribute_Color:
// 		{
// 			vertexAttribute = "in_Color";
// 			break;
// 		}
// 	case VertexAttribute_TexCoord0:
// 		{
// 			vertexAttribute = "in_TexCoord0";
// 			break;
// 		}
// 	case VertexAttribute_Normal:
// 		{
// 			vertexAttribute = "in_Normal";
// 			break;
// 		}
// 	default:
// 		{
// 			fprintf(stderr, "Invalid vertex attribute encountered!");
// 			assert(false);
// 			break;
// 		}
// 	}
// 	return vertexAttribute;
// }
// 
// GLuint GetVertexAttributeLocation(GFXVertexAttribute a_VertexAttribute)
// {
// 	GLuint location = (GLuint)-1;
// 	switch (a_VertexAttribute)
// 	{
// 	case VertexAttribute_Position:
// 		{
// 			location = 0;
// 			break;
// 		}
// 	case VertexAttribute_TexCoord0:
// 		{
// 			location = 1;
// 			break;
// 		}
// 	case VertexAttribute_Normal:
// 		{
// 			location = 2;
// 			break;
// 		}
// 	default:
// 		{
// 			fprintf(stderr, "Invalid vertex attribute encountered!");
// 			assert(false);
// 			break;
// 		}
// 	}
// 	return location;
// }

GLenum TranslateDataType(GFXDataType a_DataType)
{
	GLenum datatype = GL_INVALID_ENUM;
	switch (a_DataType)
	{
	case DataType_Byte:
		{
			datatype = GL_BYTE;
			break;
		}
	case DataType_UnsignedByte:
		{
			datatype = GL_UNSIGNED_BYTE;
			break;
		}
	case DataType_Short:
		{
			datatype = GL_SHORT;
			break;
		}
	case DataType_UnsignedShort:
		{
			datatype = GL_UNSIGNED_SHORT;
			break;
		}
	case DataType_Int32:
		{
			datatype = GL_INT;
			break;
		}
	case DataType_UnsignedInt32:
		{
			datatype = GL_UNSIGNED_INT;
			break;
		}
	case DataType_Float:
		{
			datatype = GL_FLOAT;
			break;
		}
	case DataType_Fixed:
		{
			datatype = GL_FIXED;
			break;
		}
	case DataType_Invalid:
	default:
		{
			fprintf(stderr, "Invalid data type encountered!");
			assert(false);
			break;
		}
	}
	return datatype;
}

GLenum TranslateRenderMode(GFXRenderMode a_RenderMode)
{
	GLenum renderMode = GL_INVALID_ENUM;
	switch (a_RenderMode)
	{
	case RenderMode_Triangles:
		{
			renderMode = GL_TRIANGLES;
			break;
		}
	case RenderMode_Invalid:
	default:
		{
			fprintf(stderr, "Invalid usage encountered!");
			assert(false);
			break;
		}
	}
	return renderMode;
}

GLenum TranslateUsage(GFXUsage a_Usage)
{
	GLenum usage = GL_INVALID_ENUM;
	switch (a_Usage)
	{
	case Usage_Default:
	case Usage_Immutable:
		{
			usage = GL_STATIC_DRAW;
			break;
		}
	case Usage_Dynamic:
		{
			usage = GL_STREAM_DRAW;
			break;
		}
	case Usage_Staging:
		{
			usage = GL_DYNAMIC_DRAW;
			break;
		}
	case Usage_Invalid:
	default:
		{
			fprintf(stderr, "Invalid usage encountered!");
			assert(false);
			break;
		}
	}
	return usage;
}

GLenum TranslateTextureFormat(GFXTextureFormat a_TextureFormat)
{
	GLenum format = GL_INVALID_ENUM;
	switch (a_TextureFormat)
	{
	case TextureFormat_R32G32B32Float:
		{
			format = GL_RGB;
			break;
		}
	case TextureFormat_R32G32B32A32Float:
		{
			format = GL_RGBA;
			break;
		}
	case TextureFormat_R8G8B8A8Uint32Normalized:
		{
			format = GL_RGBA;
			break;
		}
	case TextureFormat_Invalid:
	default:
		{
			fprintf(stderr, "Invalid texture format encountered!");
			assert(false);
			break;
		}
	}
	return format;
}

#endif
