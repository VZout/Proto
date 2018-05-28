#pragma once

#include "TransformNode.h"
#include "Utility/Functors.h"
#include "Utility/IUpdatable.h"

#include <vector>

BEGIN_NAMESPACE(Graphics)

class SceneNodeVisitor;

class SceneNode : public Utility::IUpdatable
{
public:
	TransformNode& GetTransformNode();
	const TransformNode& GetTransformNode() const;

	void Update(const Utility::UpdateEvent &a_UpdateEvent) override;

	void Accept(SceneNodeVisitor &a_Visitor);

private:
	TransformNode m_TransformNode;
};

typedef std::vector<SceneNode*> SceneNodeVector;

END_NAMESPACE(Graphics)
