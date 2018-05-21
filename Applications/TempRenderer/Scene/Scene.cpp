#include "Scene.h"

#include "Platform/Debug/AssertMessage.h"
#include "SceneGraph.h"

USING_NAMESPACE(Platform)
USING_NAMESPACE(Utility)

Scene::Scene(GFXAPI a_API, const HashedString &a_Name)
	: m_API(a_API)
	, m_SceneGraph(new SceneGraph(a_Name))
{
}

Scene::~Scene()
{
}

void Scene::Update(const Utility::UpdateEvent &a_UpdateEvent)
{
	AssertMessage(NULLPTR != m_SceneGraph, "Attempt to update an invalid scene graph!");
	m_SceneGraph->Update(a_UpdateEvent);
}

SceneGraph& Scene::GetSceneGraph()
{
	return const_cast<SceneGraph&>(const_cast<const Scene*>(this)->GetSceneGraph());
}

const SceneGraph& Scene::GetSceneGraph() const
{
	AssertMessage(NULLPTR != m_SceneGraph, "Attempt to retrieve an invalid scene graph!");
	return *m_SceneGraph;
}
