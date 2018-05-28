#pragma once

#include "Graphics/API/GFX.h"
#include "Graphics/Scene/Scene.h"

class SimpleScene : public Graphics::Scene
{
public:
	SimpleScene(GFXAPI a_API);
	virtual ~SimpleScene();

	void Initialize(Resources::ResourceManager &a_ResourceManager) OVERRIDE;
};
