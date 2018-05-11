#include "RenderingTechnique.h"

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


