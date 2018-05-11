#pragma once

#include "Proto.h"
#include "Graphics/API/GFX.h"

#include <vector>

BEGIN_NAMESPACE(Graphics)

class Mesh
{
public:
	Mesh();
	~Mesh();

	GFXVertexBufferHandle m_VertexBuffer;
	GFXIndexBufferHandle m_IndexBuffer;
	uint32_t m_NumIndices;
};

typedef std::vector<Mesh*> MeshVector;

END_NAMESPACE(Graphics)
