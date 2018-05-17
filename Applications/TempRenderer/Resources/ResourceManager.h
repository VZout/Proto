#pragma once

#include "Proto.h"
#include "EResourceType.h"
#include "ResourceID.h"
#include "Utility/HashedString.h"

#include <map>
#include <string.h>

FORWARD_DECLARE(Utility, class Logger);

BEGIN_NAMESPACE(Resources)

class ILoader;

class ResourceManager
{
public:
	~ResourceManager();

	void Initialize();

	ResourceID AddResource(const std::string &a_Filename);
	//ResourceID AddResource(const std::string &a_Filename, Resources::LoadFinishedCallback a_Callback);
	ResourceID AddResource(const std::string &a_Filename, const std::string &a_ResourceName);
	//ResourceID AddResource(const std::string &a_Filename, const std::string &a_ResourceName, Resources::LoadFinishedCallback a_Callback);
	//ResourceID AddResource(const std::string &a_Filename, const std::string &a_ResourceName, Memory::MemoryBuffer &a_Buffer);

	void* Get(const Utility::HashedString &a_ID);

private:
	ResourceManager();

	void RegisterLoader(EResourceType a_ResourceType, ILoader *a_Loader /* = nullptr */);
	ILoader* FindLoader(const std::string &a_FileExtension);
	const ILoader* FindLoader(const std::string &a_FileExtension) const;
	ILoader& GetLoader(const std::string &a_FileExtension);
	const ILoader& GetLoader(const std::string &a_FileExtension) const;

	std::multimap<EResourceType, ILoader*> m_Loaders;
	std::map<Utility::HashedString, void*> m_Resources;

	std::string m_ResourceDir;

	//Utility::Logger &m_Logger;

	friend void CreateResourceManager();
};

bool HasResourceManager();
void CreateResourceManager();
ResourceManager& GetResourceManager();
void DestoryResourceManager();

END_NAMESPACE(Resources)
