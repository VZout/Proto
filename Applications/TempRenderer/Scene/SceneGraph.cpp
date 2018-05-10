#include "SceneGraph.h"

#include "Platform/Debug/AssertMessage.h"
#include "SceneGraphVisitor.h"
#include "SceneNode.h"
#include "Utility/ClearContainerContents.h"

USING_NAMESPACE(Memory)
USING_NAMESPACE(Platform)
USING_NAMESPACE(Utility)

SceneGraph::SceneGraph(const Utility::HashedString &a_ID)
	: m_ID(a_ID)
{
}

SceneGraph::~SceneGraph()
{
	ClearContainerContents(m_Nodes);
}

void SceneGraph::Initialize(IMemoryPool &a_ResourcePool)
{
	UNUSED(a_ResourcePool);
}

void SceneGraph::Update(const UpdateEvent &a_UpdateEvent)
{
	for (auto node : m_Nodes)
	{
		node->Update(a_UpdateEvent);
	}
	UNUSED(a_UpdateEvent);
}

void SceneGraph::Terminate()
{
}

void SceneGraph::AddNode(SceneNode &a_Node)
{
	AssertMessage(m_Nodes.end() == std::find(m_Nodes.begin(), m_Nodes.end(), &a_Node), "Node is already part of the scene!");
	m_Nodes.push_back(&a_Node);
}

void SceneGraph::Accept(SceneGraphVisitor &a_Visitor)
{
	a_Visitor.Visit(*this);
}
