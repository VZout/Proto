#pragma once

#include "RenderPass.h"
#include "Graphics/API/GFX.h"

FORWARD_DECLARE(Platform, class Inspector)

BEGIN_NAMESPACE(Graphics)

class UIRenderPass : public RenderPass
{
public:
	UIRenderPass(GFXAPI a_API, GFXRenderTargetHandle a_RenderTarget);
	virtual ~UIRenderPass();

	void Initialize(Resources::ResourceManager &a_ResourceManager) OVERRIDE;
	void Prepare(const Camera &a_Camera, SceneGraph &a_SceneGraph) OVERRIDE;
	void Execute(GFXCommandQueueHandle a_CommandQueue) OVERRIDE;
	void Terminate() OVERRIDE;

	Platform::Inspector& GetInspector();

private:
	Platform::Inspector *m_Inspector;
};

END_NAMESPACE(Graphics)
