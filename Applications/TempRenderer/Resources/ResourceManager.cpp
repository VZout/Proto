#include "ResourceManager.h"

#include "Platform/Debug/AssertMessage.h"

USING_NAMESPACE(Platform)
USING_NAMESPACE(Utility)

BEGIN_UNNAMEDNAMESPACE()

ResourceManager *g_ResourceManager = NULLPTR;

END_UNNAMEDNAMESPACE()

ResourceManager::~ResourceManager()
{
}

void ResourceManager::Add(void *a_Resource, const HashedString &a_ID)
{
	std::pair<std::map<HashedString, void*>::iterator, bool> ret;
	ret = m_Resources.insert(std::pair<HashedString, void*>(a_ID, a_Resource));
	AssertMessage(ret.second, "Error while adding resource!");
}

void* ResourceManager::Get(const Utility::HashedString &a_ID)
{
	void *resource = NULLPTR;
	std::map<Utility::HashedString, void*>::iterator pos = m_Resources.find(a_ID);
	if (m_Resources.end() != pos)
	{
		resource = pos->second;
	}
	return resource;
}

ResourceManager::ResourceManager()
{
}

bool HasResourceManager()
{
	return NULLPTR != g_ResourceManager;
}

void CreateResourceManager()
{
	AssertMessage(NULLPTR == g_ResourceManager, "Attempt to recreate resource manager!");
	g_ResourceManager = new ResourceManager();
}

ResourceManager& GetResourceManager()
{
	AssertMessage(NULLPTR != g_ResourceManager, "Attempt to retrieve an invalid resource manager!");
	return *g_ResourceManager;
}

void DestoryResourceManager()
{
	AssertMessage(NULLPTR != g_ResourceManager, "No valid resource manager available!");
	delete g_ResourceManager;
}
