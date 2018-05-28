#pragma once

#include "SceneNode.h"
#include "SceneNodeVisitor.h"
#include "Utility/Patterns/IVisitor.h"

BEGIN_NAMESPACE(Graphics)

class SceneGraph;

class SceneGraphVisitor : public Utility::IVisitor<SceneGraph>
{
public:
	SceneGraphVisitor(SceneNodeVector &a_SceneNodes, SelectorFunctor a_Functor);
	void Visit(SceneGraph &a_SceneGraph) override;

private:
	SceneNodeVisitor m_SceneNodeVisitor;
	const SceneNodeVector &m_SceneNodes;
};

END_NAMESPACE(Graphics)
