#pragma once

#include "..\Resource.h"
#include "Graphics\API\GFX.h"

BEGIN_NAMESPACE(Resources)

class MeshResource
{
public:
	GFXVertexBufferHandle m_VertexBuffer;
	GFXIndexBufferHandle m_IndexBuffer;
};

END_NAMESPACE(Resources)
