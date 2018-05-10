#pragma once

#include "Proto.h"

#include "Math/Matrix4.h"
#include "Utility/IUpdatable.h"

FORWARD_DECLARE(Math, class Vector3)
FORWARD_DECLARE(Utility, struct UpdateEvent)

class TransformNode : public Utility::IUpdatable
{
public:
	TransformNode();
	virtual ~TransformNode();

	void Update(const Utility::UpdateEvent &a_UpdateEvent) override;

	void SetPosition(float a_X, float a_Y, float a_Z);
	void SetPosition(Math::Vector3 &a_Position);
	void SetRotation(float a_X, float a_Y, float a_Z);
	void SetScale(float a_Scale);
	void SetScale(Math::Vector3 &a_Scale);

	Math::Matrix4& GetTransform();
	const Math::Matrix4& GetTransform() const;

private:
	mutable bool m_TransformDirty;
	Math::Vector3 m_Position;
	Math::Vector3 m_Rotation;
	Math::Vector3 m_Scale;
	mutable Math::Matrix4 m_Transform;
};
