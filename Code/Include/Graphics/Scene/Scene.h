#pragma once

#include "Graphics/API/GFX.h"
#include "Utility/NoCopy.h"

FORWARD_DECLARE(Resources, class ResourceManager)
FORWARD_DECLARE(Utility, struct UpdateEvent)
FORWARD_DECLARE(Utility, class HashedString)

BEGIN_NAMESPACE(Graphics)

class SceneGraph;

class Scene : public Utility::NoCopy
{
public:
	Scene(GFXAPI a_API, const Utility::HashedString &a_Name);
	virtual ~Scene();

	virtual void Initialize(Resources::ResourceManager &a_ResourceManager) = 0;
	void Update(const Utility::UpdateEvent &a_UpdateEvent);
	SceneGraph& GetSceneGraph();
	const SceneGraph& GetSceneGraph() const;

protected:
	GFXAPI m_API;
	SceneGraph *m_SceneGraph;
};

END_NAMESPACE(Graphics)
