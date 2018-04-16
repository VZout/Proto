#include "ResourceLoading.h"

#include "Platform/Debug/AssertMessage.h"

#pragma warning(push)
#pragma warning(disable: 4100)
#pragma warning(disable: 4244)
#pragma warning(disable: 4267)
#pragma warning(disable: 4311)
#pragma warning(disable: 4312)
#pragma warning(disable: 4302)
#pragma warning(disable: 4456)
#pragma warning(disable: 4477)
#pragma warning(disable: 4838)
#pragma warning(disable: 4996)

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#pragma warning(pop)

#include <fstream>

USING_NAMESPACE(Platform)

BEGIN_UNNAMEDNAMESPACE()

GFXTextureFormat GetTextureFormatFromComponents(int a_DataSize, int a_NumComponents)
{
	GFXTextureFormat format = TextureFormat_Invalid;

	switch (a_NumComponents)
	{
	case 3:
	{
		if (sizeof(float) == a_DataSize)
		{
			format = TextureFormat_R32G32B32Float;
		}
		break;
	}
	case 4:
	{
		if (sizeof(uint32_t) == a_DataSize)
		{
			format = TextureFormat_R8G8B8A8Uint32Normalized;
		}
		else if (sizeof(float) == a_DataSize)
		{
			format = TextureFormat_R32G32B32A32Float;
		}
		break;
	}
	default:
	{
		AssertMessage("Unsupported number of components encountered!");
		break;
	}
	}
	AssertMessage(TextureFormat_Invalid != format, "Unsupported texture format encountered!");
	return format;
}

END_UNNAMEDNAMESPACE()

GFXTextureHandle LoadTexture(GFXAPI &a_API, const std::string &a_Filename)
{
	unsigned char* loadedData = nullptr;
	int width = 0;
	int height = 0;
	int components = 4;
	loadedData = stbi_load(a_Filename.c_str(), &width, &height, &components, 4);
	AssertMessage(nullptr != loadedData, "Failed to load image data for texture!");

	GFXTextureDescriptor textureDescriptor = { 0 };
	textureDescriptor.m_Width = width;
	textureDescriptor.m_Height = height;
	textureDescriptor.m_Format = TextureFormat_R8G8B8A8Uint32Normalized;
	textureDescriptor.m_ShaderResourceViewFormat = textureDescriptor.m_Format;
	textureDescriptor.m_Data = loadedData;
	textureDescriptor.m_RowPitch = width * sizeof(*loadedData);

	GFXTextureHandle handle;
	GFXCreateTexture(a_API, &textureDescriptor, &handle);
	STBI_FREE(loadedData);
	return handle;
}

GFXShaderHandle LoadShader(GFXAPI &a_API, const std::string &a_VertexShaderFilename, std::vector<GFXVertexAttribute> a_Attributes, const std::string &a_FragmentShaderFilename)
{
	UNUSED(a_VertexShaderFilename);
	UNUSED(a_FragmentShaderFilename);
	const std::string vertexShaderSource; // (std::istreambuf_iterator<char>(std::ifstream(a_VertexShaderFilename)), (std::istreambuf_iterator<char>()));
	const std::string fragmentShaderSource; // (std::istreambuf_iterator<char>(std::ifstream(a_FragmentShaderFilename)), (std::istreambuf_iterator<char>()));

	GFXShaderDescriptor shaderDescriptor;
	shaderDescriptor.m_Type[0] = ShaderType_VertexShader;
	shaderDescriptor.m_Source[0] = vertexShaderSource.c_str();

	shaderDescriptor.m_Type[1] = ShaderType_FragmentShader;
	shaderDescriptor.m_Source[1] = fragmentShaderSource.c_str();
	shaderDescriptor.m_NumShaders = 2;

	shaderDescriptor.m_NumAttributes = static_cast<int>(a_Attributes.size());
	for (auto pos = a_Attributes.begin(); pos != a_Attributes.end(); ++pos)
	{
		shaderDescriptor.m_Attributes[pos - a_Attributes.begin()] = *pos;
	}

	GFXShaderHandle handle;
	GFXCreateShader(a_API, &shaderDescriptor, &handle);
	return handle;
}
