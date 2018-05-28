#include "TransformNode.h"

#include "Utility/UpdateEvent.h"

USING_NAMESPACE(Math)
USING_NAMESPACE(Utility)

BEGIN_NAMESPACE(Graphics)

TransformNode::TransformNode()
	: m_TransformDirty(false)
	, m_Scale(1.0f, 1.0f, 1.0f)
{
}

TransformNode::~TransformNode()
{
}

void TransformNode::Update(const UpdateEvent &a_UpdateEvent)
{
	UNUSED(a_UpdateEvent);
	// do nothing
}

void TransformNode::SetPosition(float a_X, float a_Y, float a_Z)
{
	m_Position.m_X = a_X;
	m_Position.m_Y = a_Y;
	m_Position.m_Z = a_Z;
	m_TransformDirty = true;
}

void TransformNode::SetPosition(Math::Vector3& a_Position)
{
	m_Position.m_X = a_Position.m_X;
	m_Position.m_Y = a_Position.m_Y;
	m_Position.m_Z = a_Position.m_Z;
	m_TransformDirty = true;
}

void TransformNode::SetRotation(float a_X, float a_Y, float a_Z)
{
	m_Rotation.m_X = a_X;
	m_Rotation.m_Y = a_Y;
	m_Rotation.m_Z = a_Z;
	m_TransformDirty = true;
}

void TransformNode::SetScale(float a_Scale)
{
	m_Scale.m_X = a_Scale;
	m_Scale.m_Y = a_Scale;
	m_Scale.m_Z = a_Scale;
	m_TransformDirty = true;
}

void TransformNode::SetScale(Math::Vector3 &a_Scale)
{
	m_Scale = a_Scale;
	m_TransformDirty = true;
}

Matrix4& TransformNode::GetTransform()
{
	return const_cast<Matrix4&>(const_cast<const TransformNode*>(this)->GetTransform());
}

const Matrix4& TransformNode::GetTransform() const
{
	if (m_TransformDirty)
	{
		m_Transform = CreateRotateX(m_Rotation.m_X) * CreateRotateY(m_Rotation.m_Y) * CreateRotateZ(m_Rotation.m_Z);
		m_Transform.SetTranslation(m_Position);
		m_Transform *= CreateScale(m_Scale);
		m_TransformDirty = false;
	}
	return m_Transform;
}

END_NAMESPACE(Graphics)
