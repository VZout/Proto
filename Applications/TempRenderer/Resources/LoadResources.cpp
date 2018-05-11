#include "LoadResources.h"

#include "Platform/Debug/AssertMessage.h"

// #pragma warning(push)
// #pragma warning(disable: 4100)
// #pragma warning(disable: 4244)
// #pragma warning(disable: 4267)
// #pragma warning(disable: 4311)
// #pragma warning(disable: 4312)
// #pragma warning(disable: 4302)
// #pragma warning(disable: 4456)
// #pragma warning(disable: 4477)
// #pragma warning(disable: 4838)
// #pragma warning(disable: 4996)
// 
// #define STB_IMAGE_IMPLEMENTATION
// #include <stb_image.h>
// 
// #pragma warning(pop)

#include <fstream>

USING_NAMESPACE(Platform)

BEGIN_UNNAMEDNAMESPACE()

// GFXTextureFormat GetTextureFormatFromComponents(int a_DataSize, int a_NumComponents)
// {
// 	GFXTextureFormat format = TextureFormat_Invalid;
// 
// 	switch (a_NumComponents)
// 	{
// 	case 3:
// 	{
// 		if (sizeof(float) == a_DataSize)
// 		{
// 			format = TextureFormat_R32G32B32Float;
// 		}
// 		break;
// 	}
// 	case 4:
// 	{
// 		if (sizeof(uint32_t) == a_DataSize)
// 		{
// 			format = TextureFormat_R8G8B8A8Uint32Normalized;
// 		}
// 		else if (sizeof(float) == a_DataSize)
// 		{
// 			format = TextureFormat_R32G32B32A32Float;
// 		}
// 		break;
// 	}
// 	default:
// 	{
// 		AssertMessage("Unsupported number of components encountered!");
// 		break;
// 	}
// 	}
// 	AssertMessage(TextureFormat_Invalid != format, "Unsupported texture format encountered!");
// 	return format;
// }

END_UNNAMEDNAMESPACE()

// GFXTextureHandle LoadTexture(GFXAPI &a_API, const std::string &a_Filename)
// {
// 	unsigned char* loadedData = nullptr;
// 	int width = 0;
// 	int height = 0;
// 	int components = 4;
// 	loadedData = stbi_load(a_Filename.c_str(), &width, &height, &components, 4);
// 	AssertMessage(nullptr != loadedData, "Failed to load image data for texture!");
// 
// 	GFXTextureDescriptor textureDescriptor = { 0 };
// 	textureDescriptor.m_Width = width;
// 	textureDescriptor.m_Height = height;
// 	textureDescriptor.m_Format = TextureFormat_R8G8B8A8Uint32Normalized;
// 	textureDescriptor.m_ShaderResourceViewFormat = textureDescriptor.m_Format;
// 	textureDescriptor.m_Data = loadedData;
// 	textureDescriptor.m_RowPitch = width * sizeof(*loadedData);
// 
// 	GFXTextureHandle handle;
// 	GFXCreateTexture(a_API, &textureDescriptor, &handle);
// 	STBI_FREE(loadedData);
// 	return handle;
// }

GFXShaderHandle LoadShader(GFXAPI &a_API, const std::string &a_ShaderFilename, GFXShaderType a_Type, const std::string &a_EntryPoint)
{
	std::ifstream shaderFile(a_ShaderFilename);
	std::string shaderFileSource((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());

	GFXShaderDescriptor shaderDescriptor;
	shaderDescriptor.m_Type = a_Type;
	shaderDescriptor.m_Source = shaderFileSource.c_str();
	shaderDescriptor.m_EntryPoint = a_EntryPoint.c_str();
	GFXShaderHandle shader = { 0 };
	GFXCreateShader(a_API, &shaderDescriptor, &shader);

	return shader;
}
