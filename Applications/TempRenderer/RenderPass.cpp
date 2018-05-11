#include "RenderPass.h"

RenderPass::RenderPass(GFXAPI a_API, GFXRenderTargetHandle a_RenderTarget)
	: m_API(a_API)
	, m_RenderTarget(a_RenderTarget)
	, m_CommandList(NULLPTR)
	, m_PipelineStateObject(NULLPTR)
{
}

RenderPass::~RenderPass()
{
	GFXDestroyPipelineStateObject(m_API, m_PipelineStateObject);
}
