#include "RenderTechnique.h"

RenderTechnique::RenderPassListIt RenderTechnique::GetPassListBegin()
{
	return m_RenderPasses.begin();
}

RenderTechnique::RenderPassListConstIt RenderTechnique::GetPassListBegin() const
{
	return m_RenderPasses.begin();
}

RenderTechnique::RenderPassListIt RenderTechnique::GetPassListEnd()
{
	return m_RenderPasses.end();
}

RenderTechnique::RenderPassListConstIt RenderTechnique::GetPassListEnd() const
{
	return m_RenderPasses.end();
}

const RenderTechnique::RenderPassList& RenderTechnique::GetPasses() const
{
	return m_RenderPasses;
}


