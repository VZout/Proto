#pragma once

#include "Proto.h"
#include "EResourceType.h"
#include "Graphics/API/GFX.h"
#include "Platform/Debug/AssertMessage.h"
#include "ResourceID.h"
#include "Utility/HashedString.h"

#include <map>
#include <string.h>

FORWARD_DECLARE(Utility, class Logger);

BEGIN_NAMESPACE(Resources)

class ILoader;
class Resource;

class ResourceManager
{
public:
	ResourceManager(GFXAPI a_API);
	~ResourceManager();

	void Initialize();

	ResourceID AddResource(const std::string &a_Filename);
	ResourceID AddResource(const std::string &a_Filename, const std::string &a_ResourceName);
	ResourceID AddResource(Resource *a_Resource, const std::string &a_ResourceName);

	template<typename TYPE>
	TYPE& GetResource(const ResourceID &a_ResourceID)
	{
		auto pos = m_Resources.find(a_ResourceID);
		Platform::AssertMessage(m_Resources.end() != pos, "Unable to retrieve specified resource!");
		Resource *resource = pos->second;
		Platform::AssertMessage(NULLPTR != resource, "Invalid (NULL) resource found!");
		return *reinterpret_cast<TYPE*>(resource);
	}

private:
	void RegisterLoader(EResourceType a_ResourceType, ILoader *a_Loader /* = nullptr */);
	ILoader* FindLoader(const std::string &a_FileExtension);
	const ILoader* FindLoader(const std::string &a_FileExtension) const;
	ILoader& GetLoader(const std::string &a_FileExtension);
	const ILoader& GetLoader(const std::string &a_FileExtension) const;

	std::multimap<EResourceType, ILoader*> m_Loaders;

	typedef std::map<ResourceID, Resource*> ResourceMap;
	typedef ResourceMap::iterator ResourceMapIt;
	typedef ResourceMap::const_iterator ResourceMapConstIt;
	typedef std::pair<ResourceID, Resource*> ResourceMapPair;
	ResourceMap m_Resources;

	std::string m_ResourceDir;

	GFXAPI m_API;
};

END_NAMESPACE(Resources)
