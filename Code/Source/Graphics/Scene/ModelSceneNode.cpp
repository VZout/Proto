#include "ModelSceneNode.h"

BEGIN_NAMESPACE(Graphics)

ModelSceneNode::ModelSceneNode(Model &a_Model)
	: m_Model(a_Model)
{
}

ModelSceneNode::~ModelSceneNode()
{
}

Model& ModelSceneNode::GetModel()
{
	return const_cast<Model&>(const_cast<const ModelSceneNode*>(this)->GetModel());
}

const Model& ModelSceneNode::GetModel() const
{
	return m_Model;
}

END_NAMESPACE(Graphics)
