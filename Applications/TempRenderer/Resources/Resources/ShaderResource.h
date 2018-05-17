#pragma once

#include "..\Resource.h"
#include "Graphics\API\GFX.h"

BEGIN_NAMESPACE(Resources)

class ShaderResource : public Resource
{
public:
	ShaderResource()
		: Resource(EResourceType_Shader)
	{
	}

	GFXShaderHandle m_VertexShader;
	GFXShaderHandle m_PixelShader;
	GFXShaderHandle m_ComputeShader;
};

END_NAMESPACE(Resources)
