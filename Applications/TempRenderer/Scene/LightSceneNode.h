#pragma once

//#include "Graphics/DebugRenderable.h"
#include "Graphics/Light.h"
#include "SceneNode.h"

FORWARD_DECLARE(Graphics, class Light)

class LightSceneNode : public SceneNode//, public Graphics::DebugRenderable
{
public:
	LightSceneNode(Graphics::Light &a_Light);
	~LightSceneNode();

	Graphics::Light& GetLight();
	const Graphics::Light& GetLight() const;

private:
	Graphics::Light &m_Light;
};
