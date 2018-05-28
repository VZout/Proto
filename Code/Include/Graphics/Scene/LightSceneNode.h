#pragma once

//#include "Graphics/DebugRenderable.h"
#include "Graphics/Light.h"
#include "SceneNode.h"

BEGIN_NAMESPACE(Graphics)

class Light;

class LightSceneNode : public SceneNode//, public DebugRenderable
{
public:
	LightSceneNode(Graphics::Light &a_Light);
	~LightSceneNode();

	Light& GetLight();
	const Light& GetLight() const;

private:
	Light &m_Light;
};

END_NAMESPACE(Graphics)
