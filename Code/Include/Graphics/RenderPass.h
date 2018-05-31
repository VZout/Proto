#pragma once

#include "Graphics/API/GFX.h"
#include "Scene/SceneNode.h"
#include "Scene/SceneNodeVisitor.h"

FORWARD_DECLARE(Resources, class ResourceManager)

BEGIN_NAMESPACE(Graphics)

class Camera;
class SceneGraph;

class RenderPass
{
public:
	RenderPass(GFXAPI a_API, GFXRenderTargetHandle a_RenderTarget);
	virtual ~RenderPass();

	virtual void Initialize(Resources::ResourceManager &a_ResourceManager) = 0;
	virtual void Prepare(const Graphics::Camera &a_Camera, SceneGraph &a_SceneGraph) = 0;
	virtual void Execute(GFXCommandQueueHandle a_CommandQueue) = 0;
	virtual void Terminate() = 0;

protected:
	SceneNodeVector m_SceneNodes;
	SelectorFunctor m_Selector;
	GFXAPI m_API;
	GFXRenderTargetHandle m_RenderTarget;
	GFXCommandListHandle m_CommandList;
	GFXPipelineStateObjectHandle m_PipelineStateObject;
	GFXViewportHandle m_Viewport;
	GFXScissorRectHandle m_ScissorRect;
	GFXConstantBufferHandle m_ConstantBuffer;
};

END_NAMESPACE(Graphics)
