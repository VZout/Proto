#include "ShaderLoader.h"

#include "Graphics/API/GFXIncludes.h"
// #include "Graphics/EShaderType.h"
// #include "Resources/Data/ShaderData.h"
#include "Memory/Memory.h"
#include "Platform/Debug/AssertMessage.h"
// #include "Resources/Helpers/GenerateResourceID.h"
#include "../Helpers/LoadParameters.h"
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

std::string GetShaderProgramName(const rapidxml::xml_document<> &a_Doc)
{
	return std::string(a_Doc.first_node()->first_attribute()->value());
}

void GetShaderSourceData(const rapidxml::xml_node<> &a_ProgramNode, const std::string &a_Language/*, std::vector<ShaderSourceData*> &a_Shaders, std::string &a_Attributes/ *, Memory::MemoryPool &a_MemoryPool* /*/)
{
	//UNUSED(a_MemoryPool);

	for (uint32_t index = static_cast<uint32_t>(ShaderType_VertexShader); index < static_cast<uint32_t>(ShaderType_Invalid); ++index)
	{
		GFXShaderType currentShaderType = static_cast<GFXShaderType>(index);
		const std::string nodeName = Translate(currentShaderType);
		for (rapidxml::xml_node<> *node = a_ProgramNode.first_node(nodeName.c_str()); nullptr != node; node = node->next_sibling(nodeName.c_str()))
		{
			if (0 == strcmp(a_Language.c_str(), node->first_attribute("language")->value()))
			{
				const std::string apiCode = node->first_attribute("api")->value();
				if (0 == strcmp(GFXGetBaseAPICode(), apiCode.c_str()))
				{
					const std::string shaderSource = node->value();
					//ShaderSourceData *shaderSourceData = new ShaderSourceData(currentShaderType, apiCode, a_Language, shaderSource);
					//a_Shaders.push_back(shaderSourceData);

					if (ShaderType_VertexShader == currentShaderType)
					{
						if (node->first_attribute("attributes"))
						{
							//a_Attributes = node->first_attribute("attributes")->value();
						}
					}
				}
			}
		}
	}
}

END_UNNAMEDNAMESPACE()

ShaderLoader::ShaderLoader(const std::string &a_Extensions) //, Logger &a_Logger)
	: BaseLoader(a_Extensions)
{
	m_RegisteredLanguages.push_back("glsl");
	m_RegisteredLanguages.push_back("hlsl");
}

ShaderLoader::~ShaderLoader()
{
}

ResourceData* ShaderLoader::Load(const LoadParameters &a_Parameters/*, Memory::IMemoryPool &a_MemoryPool*/) const
{
	UNUSED(a_Parameters);

	rapidxml::file<char> xmlFile(a_Parameters.m_Filename.c_str());
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
// 
// 	ShaderData *shaderData = new ShaderData();// NEW(a_MemoryPool, ShaderData);
// 	shaderData->m_Filename = a_Parameters.m_Filename;
// 	shaderData->m_ProgramName = GetShaderProgramName(doc);
// 
	const rapidxml::xml_node<> &programNode = *doc.first_node("ShaderProgram");
	for (auto pos = m_RegisteredLanguages.begin(); pos != m_RegisteredLanguages.end(); ++pos)
	{
		const std::string &language = *pos;
		GetShaderSourceData(programNode, language/*, shaderData->m_ShaderSources, shaderData->m_Attributes, a_MemoryPool*/);
	}
// 	
// 	ResourceData *resourceData = new ResourceData(a_Parameters.m_ResourceID, EResourceType_Shader, a_Parameters.m_Filename, shaderData);
// 	AssertMessage(nullptr != resourceData, "Failed to read shader resource data!");
// 	return resourceData;
	return NULLPTR;
}

const std::string ShaderLoader::GetAssetDirectoryName() const
{
	return g_AssetDirectoryName;
}

END_NAMESPACE(Resources)
