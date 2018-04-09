#include "OpenGLTranslators.h"

#include "Graphics/API/GFX.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(GFX_API_OPENGL)

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

const char* TranslateVertexAttribute(GFXVertexAttribute a_VertexAttribute)
{
	char *vertexAttribute = 0;
	switch (a_VertexAttribute)
	{
	case VertexAttribute_Position:
		{
			vertexAttribute = "in_Position";
			break;
		}
	case VertexAttribute_Color:
		{
			vertexAttribute = "in_FillColor";
			break;
		}
	case VertexAttribute_TexCoord0:
		{
			vertexAttribute = "in_TexCoord0";
			break;
		}
	case VertexAttribute_Normal:
		{
			vertexAttribute = "in_Normal";
			break;
		}
	default:
		{
			fprintf(stderr, "Invalid vertex attribute encountered!");
			assert(false);
			break;
		}
	}
	return vertexAttribute;
}

GLuint GetVertexAttributeLocation(GFXVertexAttribute a_VertexAttribute)
{
	GLuint location = (GLuint)-1;
	switch (a_VertexAttribute)
	{
	case VertexAttribute_Position:
		{
			location = 0;
			break;
		}
	case VertexAttribute_TexCoord0:
		{
			location = 1;
			break;
		}
	case VertexAttribute_Normal:
	{
		location = 2;
		break;
	}
	default:
		{
			fprintf(stderr, "Invalid vertex attribute encountered!");
			assert(false);
			break;
		}
	}
	return location;
}

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
	/*
	GL_RED, 
	GL_RG, 
	GL_RGB, 
	GL_BGR, 
	GL_RGBA, 
	GL_BGRA, 
	GL_RED_INTEGER, 
	GL_RG_INTEGER, 
	GL_RGB_INTEGER, 
	GL_BGR_INTEGER, 
	GL_RGBA_INTEGER, 
	GL_BGRA_INTEGER, 
	GL_STENCIL_INDEX, 
	GL_DEPTH_COMPONENT, 
	GL_DEPTH_STENCIL
	*/

	GLenum format = GL_INVALID_ENUM;
	switch (a_TextureFormat)
	{
	case TextureFormat_R32G32B32Float:
	{
		//format = GL_RGBA32F;
		break;
	}
	case TextureFormat_R32G32B32A32Float:
	{
		//format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		break;
	}
	case TextureFormat_R8G8B8A8Uint32Normalized:
	{
		format = GL_RGBA;
		break;
	}
	case TextureFormat_DepthStencilR16Typeless:
	{
		//format = DXGI_FORMAT_R16_TYPELESS;
		break;
	}
	case TextureFormat_DepthStencilR16:
	{
		//format = DXGI_FORMAT_R16_FLOAT;
		break;
	}
	case TextureFormat_DepthStencilR32Typeless:
	{
		//format = DXGI_FORMAT_R32_TYPELESS;
		break;
	}
	case TextureFormat_DepthStencilR32:
	{
		//format = DXGI_FORMAT_R32_FLOAT;
		break;
	}
	case TextureFormat_DepthStencilR24G8Typeless:
	{
		//format = DXGI_FORMAT_R24G8_TYPELESS;
		break;
	}
	case TextureFormat_DepthStencilR24G8:
	{
		//format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		break;
	}
	case TextureFormat_DepthStencilR32G8X24Typeless:
	{
		//format = DXGI_FORMAT_R32G8X24_TYPELESS;
		break;
	}
	case TextureFormat_DepthStencilR32G8X24:
	{
		//format = DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
		break;
	}
	case TextureFormat_Invalid:
	default:
		{
			fprintf(stderr, "Invalid usage encountered!");
			assert(false);
			break;
		}
	}
	return format;
}

GLenum TranslateTextureDataType(uint32_t a_DataByteSize)
{
	GFX_UNUSED(a_DataByteSize);

	GLenum textureDataType = GL_INVALID_ENUM;
	textureDataType = GL_UNSIGNED_BYTE;
// 	GL_UNSIGNED_BYTE
// 	GL_BYTE
// 	GL_UNSIGNED_SHORT
// 	GL_SHORT
// 	GL_UNSIGNED_INT
// 	GL_INT
// 	GL_FLOAT
// 	GL_UNSIGNED_BYTE_3_3_2
// 	GL_UNSIGNED_BYTE_2_3_3_REV
// 	GL_UNSIGNED_SHORT_5_6_5
// 	GL_UNSIGNED_SHORT_5_6_5_REV
// 	GL_UNSIGNED_SHORT_4_4_4_4
// 	GL_UNSIGNED_SHORT_4_4_4_4_REV
// 	GL_UNSIGNED_SHORT_5_5_5_1
// 	GL_UNSIGNED_SHORT_1_5_5_5_REV
// 	GL_UNSIGNED_INT_8_8_8_8
// 	GL_UNSIGNED_INT_8_8_8_8_REV
// 	GL_UNSIGNED_INT_10_10_10_2
// 	GL_UNSIGNED_INT_2_10_10_10_REV
	return textureDataType;
}

#endif
