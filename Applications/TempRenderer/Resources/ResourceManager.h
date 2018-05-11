#pragma once

#include "Proto.h"
#include "Utility/HashedString.h"

#include <map>

class ResourceManager
{
public:
	~ResourceManager();

	void Add(void *a_Resource, const Utility::HashedString &a_ID);
	void* Get(const Utility::HashedString &a_ID);

private:
	ResourceManager();

	std::map<Utility::HashedString, void*> m_Resources;

	friend void CreateResourceManager();
};

bool HasResourceManager();
void CreateResourceManager();
ResourceManager& GetResourceManager();
void DestoryResourceManager();
