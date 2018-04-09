#pragma once

#include "Proto.h"

#include "Graphics/API/GFX.h"

BEGIN_NAMESPACE(Graphics)

struct Mesh
{
	GFXVertexBufferHandle m_VertexBuffer;
	GFXIndexBufferHandle m_IndexBuffer;
	uint32_t m_NumIndices;
};

END_NAMESPACE(Graphics)
