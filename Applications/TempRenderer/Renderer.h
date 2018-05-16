#pragma once

#include "Proto.h"
#include "Graphics/API/GFX.h"

FORWARD_DECLARE(Graphics, class Camera)
FORWARD_DECLARE(Platform, class Window)
FORWARD_DECLARE(Utility, struct UpdateEvent)

class RenderingTechnique;
class SceneGraph;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Initialize(Platform::Window &a_Window);
	void Update(const Utility::UpdateEvent &a_UpdateEvent);
	void BeginRender();
	void Render();
	void EndRender();
	void Terminate();

	GFXAPI m_API;
private:
	GFXCommandQueueHandle m_CommandQueue;
	GFXSwapChainHandle m_SwapChain;
	GFXRenderTargetHandle m_RenderTarget;

	Graphics::Camera *m_Camera;
	SceneGraph *m_SceneGraph;
	RenderingTechnique *m_CurrentTechnique;
};
