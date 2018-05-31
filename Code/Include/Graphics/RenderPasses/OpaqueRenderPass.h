#pragma once

#include "../RenderPass.h"
#include "Graphics/API/GFX.h"

FORWARD_DECLARE(Resources, class ResourceManager)

BEGIN_NAMESPACE(Graphics)

class SceneGraph;

struct SceneConstantBuffer
{
	float m_Offset[4];
};

class OpaqueRenderPass : public RenderPass
{
public:
	OpaqueRenderPass(GFXAPI a_API, GFXRenderTargetHandle a_RenderTarget);
	virtual ~OpaqueRenderPass();

	void Initialize(Resources::ResourceManager &a_ResourceManager) OVERRIDE;
	void Prepare(const Graphics::Camera &a_Camera, SceneGraph &a_SceneGraph) OVERRIDE;
	void Execute(GFXCommandQueueHandle a_CommandQueue) OVERRIDE;
	void Terminate() OVERRIDE;

private:
	SceneConstantBuffer m_BufferData;
};

END_NAMESPACE(Graphics)
