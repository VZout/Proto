#include "ForwardRendering.h"

#include "RenderPasses/RenderPasses.h"
#include "Utility/ClearContainerContents.h"

USING_NAMESPACE(Resources)
USING_NAMESPACE(Utility)

BEGIN_NAMESPACE(Graphics)

ForwardRenderingTechnique::ForwardRenderingTechnique(GFXAPI a_API, GFXRenderTargetHandle a_RenderTarget)
{
	m_RenderPasses.push_back(new RenderTargetTransitionRenderPass(a_API, a_RenderTarget, ResourceState_RenderTarget));
	//m_RenderPasses.push_back(new OpaqueRenderPass(a_API, a_RenderTarget));
	//m_RenderPasses.push_back(new UIRenderPass(a_API, a_RenderTarget));
	m_RenderPasses.push_back(new RenderTargetTransitionRenderPass(a_API, a_RenderTarget, ResourceState_Present));
}

ForwardRenderingTechnique::~ForwardRenderingTechnique()
{
	for (RenderPassList::iterator pos = m_RenderPasses.begin(); pos != m_RenderPasses.end(); ++pos)
	{
		RenderPass *renderPass = *pos;
		renderPass->Terminate();
	}
	ClearContainerContents(m_RenderPasses);
}

void ForwardRenderingTechnique::Initialize(ResourceManager &a_ResourceManager)
{
	for (RenderPassList::iterator pos = m_RenderPasses.begin(); pos != m_RenderPasses.end(); ++pos)
	{
		RenderPass &renderPass = **pos;
		renderPass.Initialize(a_ResourceManager);
	}
}

END_NAMESPACE(Graphics)
