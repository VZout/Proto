#pragma once

#include "Platform/Debug/AssertMessage.h"
#include "RenderPasses/RenderPasses.h"

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

	template<typename T>
	RenderPass* FindPass()
	{
		RenderPass *renderPass = NULLPTR;
		for (RenderPassListIt pos = m_RenderPasses.begin(); pos != m_RenderPasses.end() && NULLPTR == renderPass; ++pos)
		{
			RenderPass *pass = dynamic_cast<T*>(*pos);
			if (NULLPTR != pass)
			{
				renderPass = pass;
				break;
			}
		}
		return renderPass;
	}

	template<typename T>
	RenderPass& GetPass()
	{
		RenderPass *renderPass = FindPass<T>();
		Platform::AssertMessage(NULLPTR != renderPass, "Failed to find requested renderpass!");
		return *renderPass;
	}

	void AddPass(RenderPass &a_RenderPass);

protected:
	RenderPassList m_RenderPasses;
};

END_NAMESPACE(Graphics)
