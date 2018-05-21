#include "ModelLoader.h"

#include "Graphics/API/GFXIncludes.h"
#include "../Helpers/LoadParameters.h"
#include "IO/File/GetExtensionFromFilename.h"
#include "Platform/Debug/AssertMessage.h"
#include "../Resources/ModelResource.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION

#pragma warning(push)
#pragma warning(disable: 4100)
#pragma warning(disable: 4996)
#include "tiny_gltf.h"
#pragma warning(pop)

#include <algorithm>
#include <cctype>
#include <sstream>

USING_NAMESPACE(IO)
USING_NAMESPACE(Platform)
USING_NAMESPACE(Utility)

BEGIN_NAMESPACE(Resources)

BEGIN_UNNAMEDNAMESPACE()

const std::string g_AssetDirectoryName = "Models";

END_UNNAMEDNAMESPACE()

ModelLoader::ModelLoader(const std::string &a_Extensions, GFXAPI a_API)
	: BaseLoader(a_Extensions, a_API)
{
}

ModelLoader::~ModelLoader()
{
}

Resource* ModelLoader::Load(const LoadParameters &a_Parameters) const
{
	ModelResource *resource = new ModelResource();

	tinygltf::Model model;
	tinygltf::TinyGLTF loader;

	bool result = false;
	const std::string extension = GetExtensionFromFilename(a_Parameters.m_Filename, true);
	std::string err;
	if (0 == strcmp("GLB", extension.c_str()))
	{
		result = loader.LoadBinaryFromFile(&model, &err, a_Parameters.m_Filename.c_str());
	}
	else
	{
		result = loader.LoadASCIIFromFile(&model, &err, a_Parameters.m_Filename.c_str());
	}
#if !defined(NDEBUG)
	if (!result)
	{
		std::stringstream ss;
		ss << "Error parsing gltf model [" << err << "]!";
		AssertMessage(ss.str().c_str());
	}
#endif

	const size_t numBufferViews = model.bufferViews.size();
	for (size_t currentBufferView = 0; currentBufferView < numBufferViews; ++currentBufferView)
	{
		const tinygltf::BufferView &bufferView = model.bufferViews[currentBufferView];
		AssertMessage(0 != bufferView.target, "Invalid bufferview target encountered in GLTF file!");

		tinygltf::Buffer &buffer = model.buffers[bufferView.buffer];
		switch (bufferView.target)
		{
		case TINYGLTF_TARGET_ARRAY_BUFFER:
			{
				GFXVertexBufferDescriptor vertexBufferDescriptor;
				vertexBufferDescriptor.m_Usage = Usage_Default;
				vertexBufferDescriptor.m_DataByteSize = static_cast<uint32_t>(bufferView.byteLength);
				vertexBufferDescriptor.m_Vertices = &buffer.data.at(0) + bufferView.byteOffset;
				vertexBufferDescriptor.m_ByteOffset = bufferView.byteOffset;
				vertexBufferDescriptor.m_Stride = static_cast<uint32_t>(bufferView.byteStride);
				GFXVertexBufferHandle vertexBuffer;
				GFXCreateVertexBuffer(m_API, &vertexBufferDescriptor, &vertexBuffer);
				break;
			}
		case TINYGLTF_TARGET_ELEMENT_ARRAY_BUFFER:
			{
				GFXIndexBufferDescriptor indexBufferDescriptor;
				indexBufferDescriptor.m_Usage = Usage_Default;
				indexBufferDescriptor.m_DataByteSize = bufferView.byteLength;
				indexBufferDescriptor.m_Indices = &buffer.data.at(0) + bufferView.byteOffset;
				GFXIndexBufferHandle indexBuffer;
				GFXCreateIndexBuffer(m_API, &indexBufferDescriptor, &indexBuffer);
				break;
			}
		default:
			{
				AssertMessage("Unexpected bufferview target encountered!");
				break;
			}
		}
	}
	const size_t numBuffers = model.buffers.size();
	const size_t numImages = model.images.size();
	UNUSED(numImages);
	UNUSED(numBuffers);
	return resource;
}

const std::string ModelLoader::GetAssetDirectoryName() const
{
	return g_AssetDirectoryName;
}

END_NAMESPACE(Resources)