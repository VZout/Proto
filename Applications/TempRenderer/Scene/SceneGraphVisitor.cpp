#include "SceneGraphVisitor.h"

#include "SceneGraph.h"

SceneGraphVisitor::SceneGraphVisitor(SceneNodeVector &a_SceneNodes, SelectorFunctor a_Functor)
	: m_SceneNodes(a_SceneNodes)
	, m_SceneNodeVisitor(a_Functor, a_SceneNodes)
{
}

void SceneGraphVisitor::Visit(SceneGraph &a_SceneGraph)
{
	for (auto sceneNode : a_SceneGraph.m_Nodes)
	{
		sceneNode->Accept(m_SceneNodeVisitor);
	}
}
