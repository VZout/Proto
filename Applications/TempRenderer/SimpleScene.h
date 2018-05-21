#pragma once

#include "Scene/Scene.h"

class SimpleScene : public Scene
{
public:
	SimpleScene(GFXAPI a_API);
	virtual ~SimpleScene();

	void Initialize(Resources::ResourceManager &a_ResourceManager) OVERRIDE;
};
