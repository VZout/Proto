#include "SceneNode.h"

#include "SceneNodeVisitor.h"

BEGIN_NAMESPACE(Graphics)

TransformNode& SceneNode::GetTransformNode()
{
	return const_cast<TransformNode&>(const_cast<const SceneNode*>(this)->GetTransformNode());
}

const TransformNode& SceneNode::GetTransformNode() const
{
	return m_TransformNode;
}

void SceneNode::Update(const Utility::UpdateEvent &a_UpdateEvent)
{
	UNUSED(a_UpdateEvent);
}

void SceneNode::Accept(SceneNodeVisitor &a_Visitor)
{
	a_Visitor.Visit(*this);
}

END_NAMESPACE(Graphics)
