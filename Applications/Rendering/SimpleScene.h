#pragma once

#include "Graphics/Scene/Scene.h"

struct SceneConstantBuffer
{
	float m_Offset[4];
};

class SimpleScene : public Graphics::Scene
{
public:
	SimpleScene(GFXAPI a_API);
	virtual ~SimpleScene();

	void Initialize(Resources::ResourceManager &a_ResourceManager) OVERRIDE;
	void Update(const Utility::UpdateEvent &a_UpdateEvent) OVERRIDE;
	void Terminate() OVERRIDE;

private:
	GFXConstantBufferHandle m_ConstantBuffer;
	SceneConstantBuffer m_BufferData;
};
