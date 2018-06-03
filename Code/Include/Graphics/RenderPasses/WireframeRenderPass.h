#pragma once

#include "../RenderPass.h"
#include "Graphics/API/GFX.h"

BEGIN_NAMESPACE(Graphics)

class WireframeRenderPass : public RenderPass
{
public:
	WireframeRenderPass(GFXAPI a_API, GFXRenderTargetHandle a_RenderTarget);
	virtual ~WireframeRenderPass();

	void Initialize(Resources::ResourceManager &a_ResourceManager) OVERRIDE;
	void Prepare(const Camera &a_Camera, SceneGraph &a_SceneGraph) OVERRIDE;
	void Execute(GFXCommandQueueHandle a_CommandQueue) OVERRIDE;
	void Terminate() OVERRIDE;
};

END_NAMESPACE(Graphics)
