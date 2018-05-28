#pragma once

#include "Graphics/Light.h"
#include "SceneNode.h"

FORWARD_DECLARE(Graphics, class Model);

BEGIN_NAMESPACE(Graphics)

class ModelSceneNode : public SceneNode
{
public:
	ModelSceneNode(Model &a_Model);
	~ModelSceneNode();

	Model& GetModel();
	const Model& GetModel() const;

private:
	Model &m_Model;
};

END_NAMESPACE(Graphics)
