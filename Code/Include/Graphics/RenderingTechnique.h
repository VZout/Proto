#pragma once

#include "Proto.h"

#include <vector>

FORWARD_DECLARE(Resources, class ResourceManager)

BEGIN_NAMESPACE(Graphics)

class RenderPass;

class RenderingTechnique
{
public:
	typedef std::vector<RenderPass*> RenderPassList;
	typedef RenderPassList::iterator RenderPassListIt;
	typedef RenderPassList::const_iterator RenderPassListConstIt;

public:
	virtual ~RenderingTechnique();

	virtual void Initialize(Resources::ResourceManager &a_ResourceManager) = 0;

	RenderPassListIt GetPassListBegin();
	RenderPassListIt GetPassListEnd();
	RenderPassListConstIt GetPassListBegin() const;
	RenderPassListConstIt GetPassListEnd() const;
	const RenderPassList& GetPasses() const;

	void AddPass(RenderPass &a_RenderPass);

protected:
	RenderPassList m_RenderPasses;
};

END_NAMESPACE(Graphics)
