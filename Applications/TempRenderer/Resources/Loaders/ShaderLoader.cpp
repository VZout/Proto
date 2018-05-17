#include "ShaderLoader.h"

#include "Graphics/API/GFXIncludes.h"
// #include "Graphics/EShaderType.h"
// #include "Resources/Data/ShaderData.h"
#include "Memory/Memory.h"
#include "Platform/Debug/AssertMessage.h"
// #include "Resources/Helpers/GenerateResourceID.h"
#include "../Helpers/LoadParameters.h"
#include "../Resources/ShaderResource.h"
// #include "Resources/Helpers/ResourceData.h"

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

USING_NAMESPACE(Platform)
USING_NAMESPACE(Utility)

BEGIN_NAMESPACE(Resources)

BEGIN_UNNAMEDNAMESPACE()

const std::string g_AssetDirectoryName = "Shaders";

std::string Translate(GFXShaderType a_ShaderType)
{
	std::string translation;

	switch (a_ShaderType)
	{
	case ShaderType_VertexShader:
		{
			translation = "VertexShader";
			break;
		}
	case ShaderType_FragmentShader:
		{
			translation = "PixelShader";
			break;
		}
	case ShaderType_ComputeShader:
		{
			translation = "ComputeShader";
			break;
		}
	case ShaderType_Geometry:
		{
			translation = "GeomteryShader";
			break;
		}
	case ShaderType_Tesselation:
		{
			translation = "TesselationShader";
			break;
		}
	case ShaderType_Invalid:
	default:
		{
			AssertMessage("Invalid shader type encountered!");
			break;
		}
	}
	return translation;
}

struct ShaderData
{
	std::string m_ShaderSource;
	std::string m_EntryPoint;
};

ShaderData GetShaderSource(const rapidxml::xml_node<> &a_ProgramNode, const char *a_APICode, GFXShaderType a_ShaderType)
{
	ShaderData shaderData;
	shaderData.m_EntryPoint = "main";

	const std::string nodeName = Translate(a_ShaderType);
	for (rapidxml::xml_node<> *node = a_ProgramNode.first_node(nodeName.c_str()); nullptr != node; node = node->next_sibling(nodeName.c_str()))
	{
		rapidxml::xml_attribute<> *entryPointAttribute = node->first_attribute("entrypoint");
		if (NULLPTR != entryPointAttribute)
		{
			const char *entryPoint = entryPointAttribute->value();
			shaderData.m_EntryPoint = (NULLPTR == entryPoint) ? "main" : std::string(entryPoint);
		}
		const std::string apiCode = node->first_attribute("api")->value();
		if (0 == strcmp(a_APICode, apiCode.c_str()))
		{
			shaderData.m_ShaderSource = node->value();
			break;
		}
	}

	return shaderData;
}

END_UNNAMEDNAMESPACE()

ShaderLoader::ShaderLoader(const std::string &a_Extensions, GFXAPI a_API) //, Logger &a_Logger)
	: BaseLoader(a_Extensions, a_API)
{
	m_RegisteredLanguages.push_back("glsl");
	m_RegisteredLanguages.push_back("hlsl");
}

ShaderLoader::~ShaderLoader()
{
}

Resource* ShaderLoader::Load(const LoadParameters &a_Parameters) const
{
	rapidxml::file<char> xmlFile(a_Parameters.m_Filename.c_str());
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	const rapidxml::xml_node<> &programNode = *doc.first_node("ShaderProgram");
	const char *apiCode = GFXGetBaseAPICode();

	ShaderResource *resource = new ShaderResource();

	for (uint32_t index = static_cast<uint32_t>(ShaderType_VertexShader); index < static_cast<uint32_t>(ShaderType_Invalid); ++index)
	{
		GFXShaderType shaderType = static_cast<GFXShaderType>(index);
		const ShaderData shaderData = GetShaderSource(programNode, apiCode, shaderType);
		if (!shaderData.m_ShaderSource.empty())
		{
			GFXShaderDescriptor shaderDescriptor;
			shaderDescriptor.m_Type = shaderType;
			shaderDescriptor.m_Source = shaderData.m_ShaderSource.c_str();
			shaderDescriptor.m_EntryPoint = shaderData.m_EntryPoint.c_str();
			switch (shaderType)
			{
			case ShaderType_VertexShader:
				{
					GFXCreateShader(m_API, &shaderDescriptor, &resource->m_VertexShader);
					break;
				}
			case ShaderType_FragmentShader:
				{
					GFXCreateShader(m_API, &shaderDescriptor, &resource->m_PixelShader);
					break;
				}
			case ShaderType_ComputeShader:
				{
					GFXCreateShader(m_API, &shaderDescriptor, &resource->m_ComputeShader);
					break;
				}
			case ShaderType_Geometry:
			case ShaderType_Tesselation:
			default:
				{
					AssertMessage("Unexpected shader type encountered!");
					break;
				}
			}
		}
	}

	return resource;
}

const std::string ShaderLoader::GetAssetDirectoryName() const
{
	return g_AssetDirectoryName;
}

END_NAMESPACE(Resources)
