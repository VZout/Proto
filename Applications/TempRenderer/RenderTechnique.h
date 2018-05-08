#pragma once

#include <vector>

class RenderPass;

class RenderTechnique
{
public:
	typedef std::vector<RenderPass*> RenderPassList;
	typedef RenderPassList::iterator RenderPassListIt;
	typedef RenderPassList::const_iterator RenderPassListConstIt;

public:
	RenderPassListIt GetPassListBegin();
	RenderPassListIt GetPassListEnd();
	RenderPassListConstIt GetPassListBegin() const;
	RenderPassListConstIt GetPassListEnd() const;
	const RenderPassList& GetPasses() const;

private:
	RenderPassList m_RenderPasses;
};