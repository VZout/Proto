#pragma once

#include "SceneNode.h"
#include "Utility/Functors.h"
#include "Utility/Patterns/IVisitor.h"

#include <vector>

BEGIN_NAMESPACE(Graphics)

typedef Utility::Functor<bool(const SceneNode&)> SelectorFunctor;

class SceneNodeVisitor : public Utility::IVisitor<SceneNode>
{
public:
	SceneNodeVisitor(SelectorFunctor a_Selector, SceneNodeVector &a_SceneNodes);
	void Visit(SceneNode& a_SceneNode) OVERRIDE;

private:
	SelectorFunctor m_Selector;
	SceneNodeVector &m_SceneNodes;
};

END_NAMESPACE(Graphics)
