#pragma once

#include "Graphics/API/GFX.h"
#include "Scene/SceneNode.h"
#include "Scene/SceneNodeVisitor.h"

class SceneGraph;

class RenderPass
{
public:
	RenderPass(GFXAPI a_API, GFXRenderTargetHandle a_RenderTarget);
	~RenderPass();

	virtual void Initialize() = 0;
	virtual void Prepare(SceneGraph &a_SceneGraph) = 0;
	virtual void Execute(GFXCommandQueueHandle a_CommandQueue) = 0;

protected:
	SceneNodeVector m_SceneNodes;
	SelectorFunctor m_Selector;
	GFXAPI m_API;
	GFXRenderTargetHandle m_RenderTarget;
	GFXCommandListHandle m_CommandList;
	GFXPipelineStateObjectHandle m_PipelineStateObject;
	GFXViewportHandle m_Viewport;
	GFXScissorRectHandle m_ScissorRect;
};
