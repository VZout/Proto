#include "DetermineInputLayout.h"

#include <assert.h>

#if defined(GFX_API_DX11)

uint32_t GetParameterByteSize(DXGI_FORMAT a_Format)
{
	uint32_t parameterByteSize = 0;
	switch (a_Format)
	{
		case DXGI_FORMAT_R32_FLOAT:
		{
			parameterByteSize = sizeof(float);
			break;
		}
	case DXGI_FORMAT_R32_UINT:
		{
			parameterByteSize = sizeof(uint32_t);
			break;
		}
	case DXGI_FORMAT_R32_SINT:
		{
			parameterByteSize = sizeof(int32_t);
			break;
		}
	case DXGI_FORMAT_R32G32_FLOAT:
		{
			parameterByteSize = 2 * sizeof(float);
			break;
		}
	case DXGI_FORMAT_R32G32_UINT:
		{
			parameterByteSize = 2 * sizeof(uint32_t);
			break;
		}
	case DXGI_FORMAT_R32G32_SINT:
		{
			parameterByteSize = 2 * sizeof(int32_t);
			break;
		}
	case DXGI_FORMAT_R32G32B32_FLOAT:
		{
			parameterByteSize = 3 * sizeof(float);
			break;
		}
	case DXGI_FORMAT_R32G32B32_UINT:
		{
			parameterByteSize = 3 * sizeof(uint32_t);
			break;
		}
	case DXGI_FORMAT_R32G32B32_SINT:
		{
			parameterByteSize = 3 * sizeof(int32_t);
			break;
		}
	case DXGI_FORMAT_R32G32B32A32_FLOAT:
		{
			parameterByteSize = 4 * sizeof(float);
			break;
		}
	case DXGI_FORMAT_R32G32B32A32_UINT:
		{
			parameterByteSize = 4 * sizeof(uint32_t);
			break;
		}
	case DXGI_FORMAT_R32G32B32A32_SINT:
		{
			parameterByteSize = 4 * sizeof(int32_t);
			break;
		}

	case DXGI_FORMAT_UNKNOWN:
	case DXGI_FORMAT_R32G32B32A32_TYPELESS:
	case DXGI_FORMAT_R32G32B32_TYPELESS:
	case DXGI_FORMAT_R16G16B16A16_TYPELESS:
	case DXGI_FORMAT_R16G16B16A16_FLOAT:
	case DXGI_FORMAT_R16G16B16A16_UNORM:
	case DXGI_FORMAT_R16G16B16A16_UINT:
	case DXGI_FORMAT_R16G16B16A16_SNORM:
	case DXGI_FORMAT_R16G16B16A16_SINT:
	case DXGI_FORMAT_R32G32_TYPELESS:
	case DXGI_FORMAT_R32G8X24_TYPELESS:
	case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
	case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
	case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
	case DXGI_FORMAT_R10G10B10A2_TYPELESS:
	case DXGI_FORMAT_R10G10B10A2_UNORM:
	case DXGI_FORMAT_R10G10B10A2_UINT:
	case DXGI_FORMAT_R11G11B10_FLOAT:
	case DXGI_FORMAT_R8G8B8A8_TYPELESS:
	case DXGI_FORMAT_R8G8B8A8_UNORM:
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_R8G8B8A8_UINT:
	case DXGI_FORMAT_R8G8B8A8_SNORM:
	case DXGI_FORMAT_R8G8B8A8_SINT:
	case DXGI_FORMAT_R16G16_TYPELESS:
	case DXGI_FORMAT_R16G16_FLOAT:
	case DXGI_FORMAT_R16G16_UNORM:
	case DXGI_FORMAT_R16G16_UINT:
	case DXGI_FORMAT_R16G16_SNORM:
	case DXGI_FORMAT_R16G16_SINT:
	case DXGI_FORMAT_R32_TYPELESS:
	case DXGI_FORMAT_D32_FLOAT:
	case DXGI_FORMAT_R24G8_TYPELESS:
	case DXGI_FORMAT_D24_UNORM_S8_UINT:
	case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
	case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
	case DXGI_FORMAT_R8G8_TYPELESS:
	case DXGI_FORMAT_R8G8_UNORM:
	case DXGI_FORMAT_R8G8_UINT:
	case DXGI_FORMAT_R8G8_SNORM:
	case DXGI_FORMAT_R8G8_SINT:
	case DXGI_FORMAT_R16_TYPELESS:
	case DXGI_FORMAT_R16_FLOAT:
	case DXGI_FORMAT_D16_UNORM:
	case DXGI_FORMAT_R16_UNORM:
	case DXGI_FORMAT_R16_UINT:
	case DXGI_FORMAT_R16_SNORM:
	case DXGI_FORMAT_R16_SINT:
	case DXGI_FORMAT_R8_TYPELESS:
	case DXGI_FORMAT_R8_UNORM:
	case DXGI_FORMAT_R8_UINT:
	case DXGI_FORMAT_R8_SNORM:
	case DXGI_FORMAT_R8_SINT:
	case DXGI_FORMAT_A8_UNORM:
	case DXGI_FORMAT_R1_UNORM:
	case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
	case DXGI_FORMAT_R8G8_B8G8_UNORM:
	case DXGI_FORMAT_G8R8_G8B8_UNORM:
	case DXGI_FORMAT_BC1_TYPELESS:
	case DXGI_FORMAT_BC1_UNORM:
	case DXGI_FORMAT_BC1_UNORM_SRGB:
	case DXGI_FORMAT_BC2_TYPELESS:
	case DXGI_FORMAT_BC2_UNORM:
	case DXGI_FORMAT_BC2_UNORM_SRGB:
	case DXGI_FORMAT_BC3_TYPELESS:
	case DXGI_FORMAT_BC3_UNORM:
	case DXGI_FORMAT_BC3_UNORM_SRGB:
	case DXGI_FORMAT_BC4_TYPELESS:
	case DXGI_FORMAT_BC4_UNORM:
	case DXGI_FORMAT_BC4_SNORM:
	case DXGI_FORMAT_BC5_TYPELESS:
	case DXGI_FORMAT_BC5_UNORM:
	case DXGI_FORMAT_BC5_SNORM:
	case DXGI_FORMAT_B5G6R5_UNORM:
	case DXGI_FORMAT_B5G5R5A1_UNORM:
	case DXGI_FORMAT_B8G8R8A8_UNORM:
	case DXGI_FORMAT_B8G8R8X8_UNORM:
	case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
	case DXGI_FORMAT_B8G8R8A8_TYPELESS:
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
	case DXGI_FORMAT_B8G8R8X8_TYPELESS:
	case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
	case DXGI_FORMAT_BC6H_TYPELESS:
	case DXGI_FORMAT_BC6H_UF16:
	case DXGI_FORMAT_BC6H_SF16:
	case DXGI_FORMAT_BC7_TYPELESS:
	case DXGI_FORMAT_BC7_UNORM:
	case DXGI_FORMAT_BC7_UNORM_SRGB:
	case DXGI_FORMAT_AYUV:
	case DXGI_FORMAT_Y410:
	case DXGI_FORMAT_Y416:
	case DXGI_FORMAT_NV12:
	case DXGI_FORMAT_P010:
	case DXGI_FORMAT_P016:
	case DXGI_FORMAT_420_OPAQUE:
	case DXGI_FORMAT_YUY2:
	case DXGI_FORMAT_Y210:
	case DXGI_FORMAT_Y216:
	case DXGI_FORMAT_NV11:
	case DXGI_FORMAT_AI44:
	case DXGI_FORMAT_IA44:
	case DXGI_FORMAT_P8:
	case DXGI_FORMAT_A8P8:
	case DXGI_FORMAT_B4G4R4A4_UNORM:
	case DXGI_FORMAT_P208:
	case DXGI_FORMAT_V208:
	case DXGI_FORMAT_V408:
	default:
		{
			assert(false);
			break;
		}
	}
	return parameterByteSize;
}

void DetermineInputLayout(ID3D11ShaderReflection *a_ReflectionInterface, D3D11_INPUT_ELEMENT_DESC **a_InputLayoutDesc, uint32_t *a_DataByteSize)
{
	D3D11_SHADER_DESC description;
	a_ReflectionInterface->lpVtbl->GetDesc(a_ReflectionInterface, &description);

	*a_InputLayoutDesc = ALLOCATEARRAY(D3D11_INPUT_ELEMENT_DESC, description.InputParameters);
	*a_DataByteSize = 0;
	for (UINT index = 0; index < description.InputParameters; ++index)
	{
		D3D11_SIGNATURE_PARAMETER_DESC parameterDesc;
		a_ReflectionInterface->lpVtbl->GetInputParameterDesc(a_ReflectionInterface, index, &parameterDesc);

		(*a_InputLayoutDesc)[index].SemanticName = parameterDesc.SemanticName;
		(*a_InputLayoutDesc)[index].SemanticIndex = parameterDesc.SemanticIndex;
		(*a_InputLayoutDesc)[index].InputSlot = 0;
		(*a_InputLayoutDesc)[index].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		(*a_InputLayoutDesc)[index].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		(*a_InputLayoutDesc)[index].InstanceDataStepRate = 0;

		if (parameterDesc.Mask == 1)
		{
			if (parameterDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) (*a_InputLayoutDesc)[index].Format = DXGI_FORMAT_R32_UINT;
			else if (parameterDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) (*a_InputLayoutDesc)[index].Format = DXGI_FORMAT_R32_SINT;
			else if (parameterDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) (*a_InputLayoutDesc)[index].Format = DXGI_FORMAT_R32_FLOAT;
		}
		else if (parameterDesc.Mask <= 3)
		{
			if (parameterDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) (*a_InputLayoutDesc)[index].Format = DXGI_FORMAT_R32G32_UINT;
			else if (parameterDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) (*a_InputLayoutDesc)[index].Format = DXGI_FORMAT_R32G32_SINT;
			else if (parameterDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) (*a_InputLayoutDesc)[index].Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if (parameterDesc.Mask <= 7)
		{
			if (parameterDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) (*a_InputLayoutDesc)[index].Format = DXGI_FORMAT_R32G32B32_UINT;
			else if (parameterDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) (*a_InputLayoutDesc)[index].Format = DXGI_FORMAT_R32G32B32_SINT;
			else if (parameterDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) (*a_InputLayoutDesc)[index].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		}
		else if (parameterDesc.Mask <= 15)
		{
			if (parameterDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) (*a_InputLayoutDesc)[index].Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if (parameterDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) (*a_InputLayoutDesc)[index].Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if (parameterDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) (*a_InputLayoutDesc)[index].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}

		*a_DataByteSize += GetParameterByteSize((*a_InputLayoutDesc)[index].Format);
	}
}

#endif
