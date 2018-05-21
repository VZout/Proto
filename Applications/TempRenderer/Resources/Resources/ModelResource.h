#pragma once

#include "..\Resource.h"
#include "Graphics\API\GFX.h"

BEGIN_NAMESPACE(Resources)

struct MeshResource
{
	GFXVertexBufferHandle m_VertexBuffer;
	GFXIndexBufferHandle m_IndexBuffer;
};

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
