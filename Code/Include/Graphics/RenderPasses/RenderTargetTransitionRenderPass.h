#pragma once

#include "RenderPass.h"
#include "Graphics/API/GFX.h"

BEGIN_NAMESPACE(Graphics)

class RenderTargetTransitionRenderPass : public RenderPass
{
public:
	RenderTargetTransitionRenderPass(GFXAPI a_API, GFXResourceHandle a_Resource, GFXResourceTransitionState a_State);
	virtual ~RenderTargetTransitionRenderPass();

	void Initialize(Resources::ResourceManager &a_ResourceManager) OVERRIDE;
	void Prepare(const Camera &a_Camera, SceneGraph &a_SceneGraph) OVERRIDE;
	void Execute(GFXCommandQueueHandle a_CommandQueue) OVERRIDE;
	void Terminate() OVERRIDE;

private:
	GFXResourceTransitionState m_DestinationState;
};

END_NAMESPACE(Graphics)
