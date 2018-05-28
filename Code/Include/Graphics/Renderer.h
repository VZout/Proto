#pragma once

#include "Proto.h"
#include "Graphics/API/GFX.h"

FORWARD_DECLARE(Platform, class Window)
FORWARD_DECLARE(Resources, class ResourceManager)
FORWARD_DECLARE(Utility, struct UpdateEvent)

BEGIN_NAMESPACE(Graphics)

class Camera;
class RenderingTechnique;
class Scene;

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

	GFXAPI GetAPI() const;
	void SetScene(Scene &a_Scene);
	Resources::ResourceManager& Renderer::GetResourceManager() const;

private:
	GFXAPI m_API;
	GFXCommandQueueHandle m_CommandQueue;
	GFXSwapChainHandle m_SwapChain;
	GFXRenderTargetHandle m_RenderTarget;

	Resources::ResourceManager *m_ResourceManager;

	Camera *m_Camera;
	Scene *m_Scene;
	RenderingTechnique *m_CurrentTechnique;
};

END_NAMESPACE(Graphics)
