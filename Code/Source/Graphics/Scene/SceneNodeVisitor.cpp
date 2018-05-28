#include "SceneNodeVisitor.h"

#include "Platform/Debug/AssertMessage.h"

USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Graphics)

SceneNodeVisitor::SceneNodeVisitor(SelectorFunctor a_Selector, SceneNodeVector &a_SceneNodes)
	: m_Selector(a_Selector)
	, m_SceneNodes(a_SceneNodes)
{
}

void SceneNodeVisitor::Visit(SceneNode& a_SceneNode)
{
	AssertMessage(m_Selector.IsBound(), "SceneNode selector function not bound!");
	if (m_Selector(a_SceneNode))
	{
		m_SceneNodes.push_back(&a_SceneNode);
	}
}

END_NAMESPACE(Graphics)
