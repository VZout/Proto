#include "RenderingTechnique.h"

BEGIN_NAMESPACE(Graphics)

RenderingTechnique::~RenderingTechnique()
{
}

RenderingTechnique::RenderPassListIt RenderingTechnique::GetPassListBegin()
{
	return m_RenderPasses.begin();
}

RenderingTechnique::RenderPassListConstIt RenderingTechnique::GetPassListBegin() const
{
	return m_RenderPasses.begin();
}

RenderingTechnique::RenderPassListIt RenderingTechnique::GetPassListEnd()
{
	return m_RenderPasses.end();
}

RenderingTechnique::RenderPassListConstIt RenderingTechnique::GetPassListEnd() const
{
	return m_RenderPasses.end();
}

const RenderingTechnique::RenderPassList& RenderingTechnique::GetPasses() const
{
	return m_RenderPasses;
}

void RenderingTechnique::AddPass(RenderPass &a_RenderPass)
{
	// TODO: find if pass already is contained in technique
	m_RenderPasses.push_back(&a_RenderPass);
}

END_NAMESPACE(Graphics)

