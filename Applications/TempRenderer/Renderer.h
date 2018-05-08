#pragma once

#include "Proto.h"

FORWARD_DECLARE(Graphics, class Camera)
FORWARD_DECLARE(Platform, class Window)

class RenderTechnique;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Initialize(Platform::Window &a_Window);
	void Update();
	void Render();
	void Terminate();

private:
	Graphics::Camera *m_Camera = nullptr;
	RenderTechnique *m_CurrentTechnique = nullptr;
};
