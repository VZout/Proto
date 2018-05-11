#pragma once

#include "../RenderPass.h"
#include "Graphics/API/GFX.h"

class OpaqueRenderPass : public RenderPass
{
public:
	OpaqueRenderPass(GFXAPI a_API, GFXRenderTargetHandle a_RenderTarget);
	virtual ~OpaqueRenderPass();

	void Initialize() OVERRIDE;
	//void Initialize(GFXShaderHandle a_VertexShader, GFXShaderHandle a_PixelShader);
	void Prepare() OVERRIDE;
	void Execute(GFXCommandQueueHandle a_CommandQueue) OVERRIDE;
};

