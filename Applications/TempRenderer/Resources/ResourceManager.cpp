#include "ResourceManager.h"

#include "ILoader.h"
#include "Helpers/GenerateResourceID.h"
#include "Helpers/LoadParameters.h"
#include "IO/File/GetExtensionFromFilename.h"
#include "IO/File/GetPathSeparator.h"
#include "Loaders/ShaderLoader.h"
#include "Platform/Debug/AssertMessage.h"
#include "Utility/ClearContainerContents.h"

#include <algorithm>
#include <cctype>

USING_NAMESPACE(IO)
USING_NAMESPACE(Platform)
USING_NAMESPACE(Resources)
USING_NAMESPACE(Utility)

BEGIN_NAMESPACE(Resources)

BEGIN_UNNAMEDNAMESPACE()

struct LoaderComparator
{
	explicit LoaderComparator(const std::string &a_Extension)
		: m_Extension(a_Extension)
	{
	}

	inline bool operator()(const std::pair<const EResourceType, ILoader*> &a_Rhs) const
	{
		ILoader *loader = a_Rhs.second;
		AssertMessage(NULLPTR != loader, "Invalid loader found!");
		return loader->Handles(m_Extension);
	}

private:
	const std::string m_Extension;
};

END_UNNAMEDNAMESPACE()

ResourceManager::ResourceManager(GFXAPI a_API)
	: m_API(a_API)
{
}

ResourceManager::~ResourceManager()
{
	ClearContainerContents(m_Resources);
	ClearContainerContents(m_Loaders);
}

void ResourceManager::Initialize()
{
	m_ResourceDir = "";

	// 
// 	RegisterLoader(EResourceType_DataBlob, new JsonLoader("bson;json", m_Logger));
// 	RegisterLoader(EResourceType_Model, new ModelLoader("obj;fbx;dae", *this, m_Logger));
// 	RegisterLoader(EResourceType_Model, new MD2ModelLoader("md2", *this, m_Logger));
// 	RegisterLoader(EResourceType_Model, new MD3ModelLoader("md3", *this, m_Logger));
// 	RegisterLoader(EResourceType_Model, new MD5ModelLoader("md5anim;md5mesh", *this, m_Logger));
// 	RegisterLoader(EResourceType_Package, new PackageLoader("pak;pk3;pk4", *this, m_Logger));
// 	RegisterLoader(EResourceType_Texture, new TextureLoader("png;bmp;jpg;tga", m_Logger));
// 	RegisterLoader(EResourceType_Tilemap, new TilemapLoader("tmx", *this, m_Logger));
// 	RegisterLoader(EResourceType_Script, new ScriptLoader("lua", m_Logger));
	RegisterLoader(EResourceType_Shader, new ShaderLoader("shader", m_API));
// 	RegisterLoader(EResourceType_Sound, new WavLoader("wav", m_Logger));
// 
// 	m_LoadingThread = std::thread(&ResourceManager::ASyncLoad, this);
}

ResourceID ResourceManager::AddResource(const std::string &a_Filename, const std::string &a_ResourceName)
{
	const std::string extension = GetExtensionFromFilename(a_Filename);
	ILoader &loader = GetLoader(extension);
	const std::string fullFilename = /*m_ResourceDir + GetPathSeparator() +*/ loader.GetAssetDirectoryName() + GetPathSeparator() + a_Filename;

	LoadParameters parameters;
	parameters.m_Filename = fullFilename;
	parameters.m_ResourceID = GenerateResourceID(a_ResourceName);
	//parameters.m_Loader = &loader;

	Resource *resource = loader.Load(parameters);

	auto entry = std::make_pair(parameters.m_ResourceID, resource);
	std::pair<ResourceMapIt, bool> result = m_Resources.insert(ResourceMapPair(parameters.m_ResourceID, resource));
	AssertMessage(result.second, "Failed to store resource data!");
	
	// 	std::lock_guard<std::mutex> lock(m_LoadMutex);
// 	m_LoadQueue.Push(parameters);
// 	m_LoadQueueConditionVariable.notify_one();

	return parameters.m_ResourceID;
}

// ResourceID ResourceManager::AddResource(const std::string &a_Filename, const std::string &a_ResourceName, LoadFinishedCallback a_Callback)
// {
// 	const std::string extension = GetExtensionFromFilename(a_Filename);
// 	ILoader &loader = GetLoader(extension);
// 	const std::string fullFilename = m_ResourceDir + g_PathSeparator + loader.GetAssetDirectoryName() + g_PathSeparator + a_Filename;
// 
// 	LoadParameters parameters;
// 	parameters.m_Filename = fullFilename;
// 	parameters.m_ResourceID = GenerateResourceID(a_ResourceName);
// 	parameters.m_Loader = &loader;
// 	parameters.m_Callback = a_Callback;
// 
// 	std::lock_guard<std::mutex> lock(m_LoadMutex);
// 	m_LoadQueue.Push(parameters);
// 	m_LoadQueueConditionVariable.notify_one();
// 
// 	return parameters.m_ResourceID;
// }

ResourceID ResourceManager::AddResource(const std::string &a_Filename)
{
	const std::string extension = GetExtensionFromFilename(a_Filename);
	ILoader &loader = GetLoader(extension);
	const std::string fullFilename = /*m_ResourceDir + GetPathSeparator() +*/ loader.GetAssetDirectoryName() + GetPathSeparator() + a_Filename;

	LoadParameters parameters;
	parameters.m_Filename = fullFilename;
	parameters.m_ResourceID = GenerateResourceID(fullFilename);
	//parameters.m_Loader = &loader;

	Resource *resource = loader.Load(parameters);
	
	auto entry = std::make_pair(parameters.m_ResourceID, resource);
	std::pair<ResourceMapIt, bool> result = m_Resources.insert(ResourceMapPair(parameters.m_ResourceID, resource));
	AssertMessage(result.second, "Failed to store resource data!");

	return parameters.m_ResourceID;
}

// ResourceID ResourceManager::AddResource(const std::string &a_Filename, LoadFinishedCallback a_Callback)
// {
// 	const std::string extension = GetExtensionFromFilename(a_Filename);
// 	ILoader &loader = GetLoader(extension);
// 	const std::string fullFilename = m_ResourceDir + g_PathSeparator + loader.GetAssetDirectoryName() + g_PathSeparator + a_Filename;
// 
// 	LoadParameters parameters;
// 	parameters.m_Filename = fullFilename;
// 	parameters.m_ResourceID = GenerateResourceID(fullFilename);
// 	parameters.m_Loader = &loader;
// 	parameters.m_Callback = a_Callback;
// 
// 	std::lock_guard<std::mutex> lock(m_LoadMutex);
// 	m_LoadQueue.Push(parameters);
// 	m_LoadQueueConditionVariable.notify_one();
// 
// 	return parameters.m_ResourceID;
// }

// ResourceID ResourceManager::AddResource(const std::string &a_Filename, const std::string &a_ResourceName, MemoryBuffer &a_Buffer)
// {
// 	AssertMessage(a_Buffer.IsValid(), "Empty data buffer encountered!");
// 	const std::string extension = GetExtensionFromFilename(a_Filename);
// 	ILoader &loader = GetLoader(extension);
// 
// 	LoadParameters parameters;
// 	parameters.m_Filename = a_Filename;
// 	parameters.m_ResourceID = GenerateResourceID(a_ResourceName);
// 	parameters.m_Loader = &loader;
// 	parameters.m_Buffer = a_Buffer;
// 
// 	std::lock_guard<std::mutex> lock(m_LoadMutex);
// 	m_LoadQueue.Push(parameters);
// 	m_LoadQueueConditionVariable.notify_one();
// 
// 	return parameters.m_ResourceID;
// }

void ResourceManager::RegisterLoader(EResourceType a_ResourceType, ILoader *a_Loader /* = nullptr */)
{
	AssertMessage(nullptr != a_Loader, "Attempt to register an invalid loader!");
#if defined(_DEBUG)
	const std::vector<std::string>& tokens = a_Loader->Handles();
	for (auto pos = tokens.begin(); pos != tokens.end(); ++pos)
	{
		AssertMessage(nullptr == FindLoader(*pos), "Duplicate loader found for extension!");
	}
#endif
	m_Loaders.insert(std::make_pair(a_ResourceType, a_Loader));
}

ILoader* ResourceManager::FindLoader(const std::string &a_FileExtension)
{
	return const_cast<ILoader*>(const_cast<const ResourceManager*>(this)->FindLoader(a_FileExtension));
}

const ILoader* ResourceManager::FindLoader(const std::string &a_FileExtension) const
{
	std::string fileExtension;
	std::transform(a_FileExtension.begin(), a_FileExtension.end(), std::back_inserter(fileExtension),
		[](unsigned char a_Char) -> unsigned char { return static_cast<unsigned char>(std::toupper(a_Char)); });

	ILoader *loader = nullptr;
	auto pos = std::find_if(m_Loaders.begin(), m_Loaders.end(), LoaderComparator(fileExtension));
	if (m_Loaders.end() != pos)
	{
		loader = (*pos).second;
	}
	return loader;
}

ILoader& ResourceManager::GetLoader(const std::string &a_FileExtension)
{
	return const_cast<ILoader&>(const_cast<const ResourceManager*>(this)->GetLoader(a_FileExtension));
}

const ILoader& ResourceManager::GetLoader(const std::string &a_FileExtension) const
{
	const ILoader *loader = FindLoader(a_FileExtension);
	AssertMessage(nullptr != loader, "Unable to find a loader for the given file extension!");
	return *loader;
}

END_NAMESPACE(Resources)
