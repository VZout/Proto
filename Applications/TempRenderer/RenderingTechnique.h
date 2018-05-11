#pragma once

#include <vector>

class RenderPass;

class RenderingTechnique
{
public:
	typedef std::vector<RenderPass*> RenderPassList;
	typedef RenderPassList::iterator RenderPassListIt;
	typedef RenderPassList::const_iterator RenderPassListConstIt;

public:
	virtual ~RenderingTechnique();

	virtual void Initialize() = 0;

	RenderPassListIt GetPassListBegin();
	RenderPassListIt GetPassListEnd();
	RenderPassListConstIt GetPassListBegin() const;
	RenderPassListConstIt GetPassListEnd() const;
	const RenderPassList& GetPasses() const;

protected:
	RenderPassList m_RenderPasses;
};