#include "RenderPass.h"

BEGIN_NAMESPACE(Graphics)

RenderPass::RenderPass(GFXAPI a_API, GFXRenderTargetHandle a_RenderTarget)
	: m_API(a_API)
	, m_RenderTarget(a_RenderTarget)
	, m_CommandList(NULLPTR)
	, m_PipelineStateObject(NULLPTR)
	, m_Viewport(NULLPTR)
	, m_ScissorRect(NULLPTR)
	, m_ConstantBuffer(NULLPTR)
{
}

RenderPass::~RenderPass()
{
	GFXDestroyConstantBuffer(m_API, m_ConstantBuffer);
	GFXDestroyScissorRect(m_API, m_ScissorRect);
	GFXDestroyViewport(m_API, m_Viewport);
	GFXDestroyPipelineStateObject(m_API, m_PipelineStateObject);
	GFXDestroyCommandList(m_API, m_CommandList);
}

END_NAMESPACE(Graphics)
