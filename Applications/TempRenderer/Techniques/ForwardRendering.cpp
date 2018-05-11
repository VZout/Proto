#include "ForwardRendering.h"

#include "../RenderPasses/OpaqueRenderPass.h"
#include "Utility/ClearContainerContents.h"

USING_NAMESPACE(Utility)

ForwardRenderingTechnique::ForwardRenderingTechnique(GFXAPI a_API, GFXRenderTargetHandle a_RenderTarget)
{
	m_RenderPasses.push_back(new OpaqueRenderPass(a_API, a_RenderTarget));
}

ForwardRenderingTechnique::~ForwardRenderingTechnique()
{
	ClearContainerContents(m_RenderPasses);
}

void ForwardRenderingTechnique::Initialize()
{
	m_RenderPasses[0]->Initialize();
}