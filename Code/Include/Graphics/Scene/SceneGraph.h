#pragma once

#include "SceneNode.h"
#include "Utility/HashedString.h"
#include "Utility/IUpdatable.h"
#include "Utility/NoCopy.h"

FORWARD_DECLARE(Memory, class IMemoryPool)

BEGIN_NAMESPACE(Graphics)

class SceneNode;
class SceneGraphVisitor;

class SceneGraph : public Utility::IUpdatable, public Utility::NoCopy
{
public:
	explicit SceneGraph(const Utility::HashedString &a_ID);
	~SceneGraph();

	void Initialize(Memory::IMemoryPool &a_ResourcePool);
	void Update(const Utility::UpdateEvent &a_UpdateEvent) override;
	void Terminate();

	void AddNode(SceneNode &a_Node);

	void Accept(SceneGraphVisitor &a_Visitor);

private:
	const Utility::HashedString m_ID;
	SceneNodeVector m_Nodes;

	friend class SceneGraphVisitor;
};

END_NAMESPACE(Graphics)
