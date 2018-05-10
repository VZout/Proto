#pragma once

#include "Proto.h"
#include "Scene/SceneNodeVisitor.h"

FORWARD_DECLARE(Graphics, class Camera)
FORWARD_DECLARE(Platform, class Window)
FORWARD_DECLARE(Utility, struct UpdateEvent)

class RenderTechnique;
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

private:
	Graphics::Camera *m_Camera;
	SceneGraph *m_SceneGraph;
	SceneNodeVector m_SceneNodes;
	SelectorFunctor m_Selector;
	RenderTechnique *m_CurrentTechnique;
};
