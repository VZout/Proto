#include "ForwardRendering.h"

#include "RenderPasses/OpaqueRenderPass.h"
#include "Utility/ClearContainerContents.h"

USING_NAMESPACE(Resources)
USING_NAMESPACE(Utility)

BEGIN_NAMESPACE(Graphics)

ForwardRenderingTechnique::ForwardRenderingTechnique(GFXAPI a_API, GFXRenderTargetHandle a_RenderTarget)
{
	m_RenderPasses.push_back(new OpaqueRenderPass(a_API, a_RenderTarget));
}

ForwardRenderingTechnique::~ForwardRenderingTechnique()
{
	ClearContainerContents(m_RenderPasses);
}

void ForwardRenderingTechnique::Initialize(ResourceManager &a_ResourceManager)
{
	m_RenderPasses[0]->Initialize(a_ResourceManager);
}

END_NAMESPACE(Graphics)
