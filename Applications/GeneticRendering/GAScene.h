#pragma once

#include "Graphics/API/GFX.h"
#include "Graphics/Scene/Scene.h"

class GAScene : public Graphics::Scene
{
public:
	GAScene(GFXAPI a_API);
	virtual ~GAScene();

	void Initialize(Resources::ResourceManager &a_ResourceManager) OVERRIDE;
	void Terminate() OVERRIDE;
};
