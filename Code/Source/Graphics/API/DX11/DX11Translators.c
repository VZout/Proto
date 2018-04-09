#include "DX11Translators.h"

#include "Graphics/API/GFX.h"

#include <assert.h>
#include <stdio.h>

#if defined(GFX_API_DX11)

D3D11_FILL_MODE TranslateFillMode(GFXFillMode a_FillMode)
{
	D3D11_FILL_MODE fillMode = 0;
	
	switch (a_FillMode)
	{
	case FillMode_Solid:
		{
			fillMode = D3D11_FILL_SOLID;
			break;
		}
	case FillMode_Wireframe:
		{
			fillMode = D3D11_FILL_WIREFRAME;
			break;
		}
	case FillMode_Invalid:
	default:
		{
			fprintf(stderr, "Invalid shader type encountered!");
			assert(false);
			break;
		}
	}

	return fillMode;
}

D3D11_PRIMITIVE_TOPOLOGY TranslateRenderMode(GFXRenderMode a_RenderMode)
{
	D3D11_PRIMITIVE_TOPOLOGY renderMode = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
	switch (a_RenderMode)
	{
	case RenderMode_Triangles:
		{
			renderMode = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			break;
		}
	case RenderMode_Invalid:
	default:
		{
			fprintf(stderr, "Invalid render mode encountered!");
			assert(false);
			break;
		}
	}
	return renderMode;
}

D3D11_USAGE TranslateUsage(GFXUsage a_Usage)
{
	D3D11_USAGE usage = D3D11_USAGE_DEFAULT;
	switch (a_Usage)
	{
	case Usage_Default:
		{
			usage = D3D11_USAGE_DEFAULT;
			break;
		}
	case Usage_Immutable:
		{
			usage = D3D11_USAGE_IMMUTABLE;
			break;
		}
	case Usage_Dynamic:
		{
			usage = D3D11_USAGE_DYNAMIC;
			break;
		}
	case Usage_Staging:
		{
			usage = D3D11_USAGE_STAGING;
			break;
		}
	default:
		{
			fprintf(stderr, "Invalid render mode encountered!");
			assert(false);
			break;
		}
	}
	return usage;
}

DXGI_FORMAT TranslateTextureFormat(GFXTextureFormat a_TextureFormat)
{
	DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;
	switch (a_TextureFormat)
	{
	case TextureFormat_R32G32B32Float:
		{
			format = DXGI_FORMAT_R32G32B32_FLOAT;
			break;
		}
	case TextureFormat_R32G32B32A32Float:
		{
			format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			break;
		}
	case TextureFormat_R8G8B8A8Uint32Normalized:
		{
			format = DXGI_FORMAT_R8G8B8A8_UNORM;
			break;
		}
	case TextureFormat_DepthStencilR16Typeless:
		{
			format = DXGI_FORMAT_R16_TYPELESS;
			break;
		}
	case TextureFormat_DepthStencilR16:
		{
			format = DXGI_FORMAT_R16_FLOAT;
			break;
		}
	case TextureFormat_DepthStencilR32Typeless:
		{
			format = DXGI_FORMAT_R32_TYPELESS;
			break;
		}
	case TextureFormat_DepthStencilR32:
		{
			format = DXGI_FORMAT_R32_FLOAT;
			break;
		}
	case TextureFormat_DepthStencilR24G8Typeless:
		{
			format = DXGI_FORMAT_R24G8_TYPELESS;
			break;
		}
	case TextureFormat_DepthStencilR24G8:
		{
			format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
			break;
		}
	case TextureFormat_DepthStencilR32G8X24Typeless:
		{
			format = DXGI_FORMAT_R32G8X24_TYPELESS;
			break;
		}
	case TextureFormat_DepthStencilR32G8X24:
		{
			format = DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
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

LPCSTR TranslateSemantic(const char *a_Name)
{
	char *semanticeName = "UNKNOWN";
	if (0 == strcmp(a_Name, "in_Position"))
	{
		semanticeName = "POSITION";
	}
	else if (0 == strcmp(a_Name, "in_TexCoord0"))
	{
		semanticeName = "TEXCOORD";
	}
	else if (0 == strcmp(a_Name, "in_Normal"))
	{
		semanticeName = "NORMAL";
	}
	else if (0 == strcmp(a_Name, "in_Tangent"))
	{
		semanticeName = "TANGENT";
	}
	else if (0 == strcmp(a_Name, "in_Bitangent"))
	{
		semanticeName = "BINORMAL";
	}
	assert(0 != strcmp(semanticeName, "UNKNOWN"));
	return semanticeName;
}

DXGI_FORMAT TranslateFormat(GFXDataType a_Type, uint32_t a_Size)
{
	DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;
	if (DataType_Float == a_Type)
	{
		switch (a_Size)
		{
		case 1:
			{
				format = DXGI_FORMAT_R32_FLOAT;
				break;
			}
		case 2:
			{
				format = DXGI_FORMAT_R32G32_FLOAT;
				break;
			}
		case 3:
			{
				format = DXGI_FORMAT_R32G32B32_FLOAT;
				break;
			}
		case 4:
			{
				format = DXGI_FORMAT_R32G32B32A32_FLOAT;
				break;
			}
		default:
			{
				fprintf(stderr, "Invalid shader type encountered!");
				assert(false);
				break;
			}
		}
	}
	assert(DXGI_FORMAT_UNKNOWN != format);
	return format;
}

#endif
