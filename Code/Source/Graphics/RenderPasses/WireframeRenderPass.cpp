#include "WireframeRenderPass.h"

USING_NAMESPACE(Resources)

BEGIN_NAMESPACE(Graphics)

WireframeRenderPass::WireframeRenderPass(GFXAPI a_API, GFXRenderTargetHandle a_RenderTarget)
	: RenderPass(a_API, a_RenderTarget)
{
}

WireframeRenderPass::~WireframeRenderPass()
{
}

void WireframeRenderPass::Initialize(ResourceManager &a_ResourceManager)
{
	UNUSED(a_ResourceManager);
}

void WireframeRenderPass::Prepare(const Camera &a_Camera, SceneGraph &a_SceneGraph)
{
	UNUSED(a_SceneGraph);
	UNUSED(a_Camera);
}

void WireframeRenderPass::Execute(GFXCommandQueueHandle a_CommandQueue)
{
	UNUSED(a_CommandQueue);
}

void WireframeRenderPass::Terminate()
{
}

END_NAMESPACE(Graphics)
