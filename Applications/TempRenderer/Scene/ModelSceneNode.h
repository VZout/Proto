#pragma once

#include "Graphics/Light.h"
#include "SceneNode.h"

FORWARD_DECLARE(Graphics, class Model);

class ModelSceneNode : public SceneNode
{
public:
	ModelSceneNode(Graphics::Model &a_Model);
	~ModelSceneNode();

	Graphics::Model& GetModel();
	const Graphics::Model& GetModel() const;

private:
	Graphics::Model &m_Model;
};
