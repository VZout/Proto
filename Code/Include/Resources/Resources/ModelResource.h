#pragma once

#include "..\Resource.h"

#include <vector>

BEGIN_NAMESPACE(Resources)

class MeshResource;

class ModelResource : public Resource
{
public:
	ModelResource()
		: Resource(EResourceType_Model)
	{
	}

	std::vector<MeshResource*> m_Meshes;
};

END_NAMESPACE(Resources)
