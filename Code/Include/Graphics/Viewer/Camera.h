#pragma once

#include "Proto.h"

#include "Math/EHandedness.h"
#include "Math/ERotationMultiplicationOrder.h"
#include "Math/ESpace.h"
#include "Math/Matrix4.h"
#include "Math/Quaternion.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Platform/KeyEvent.h"
#include "Utility/NoCopy.h"

BEGIN_NAMESPACE(Graphics)

class Frustum;
class OrthographicProjectionMatrix;
class PerspectiveProjectionMatrix;
class ProjectionMatrix;

class Camera : public Utility::NoCopy
{
public:
	enum ELens
	{
		ELens_Perspective,
		ELens_Orthographic
	};

public:
	Camera(Math::EHandedness a_Handedness = Math::EHandedness_Left);
	virtual ~Camera();

	void SetLookAt(const Math::Vector3 &a_EyePosition, const Math::Vector3 &a_TargetPosition, const Math::Vector3 &a_Up = Math::Vector3::Y_AXIS);
	const Math::Matrix4& GetViewMatrix() const;
	const Math::Matrix4& GetInverseViewMatrix() const;

	void CreatePerspectiveLens(float a_FOVDegrees, float a_AspectRatio, float a_Near, float a_Far);
	void CreateOrthographicLens(uint32_t a_Left, uint32_t a_Right, uint32_t a_Bottom, uint32_t a_Top, float a_Near = -1.0f, float a_Far = 1.0f);

	void SetLens(ELens a_Lens);
	const ProjectionMatrix& GetProjectionMatrix() const;

	void SetPosition(const Math::Vector3 &a_Position);
	Math::Vector3 GetPosition() const;

	void SetTarget(const Math::Vector3 &a_Target);
	Math::Vector3 GetTarget() const;

	void Translate(const Math::Vector3 &a_Translation, Math::ESpace a_Space = Math::ESpace_Local);
	void Rotate(float a_Pitch, float a_Yaw, float a_Roll, Math::ERotationMultiplicationOrder a_Order = Math::ERotationMultiplicationOrder_XYZ);

	Math::EHandedness GetHandedness() const;

	const Frustum& GetFrustum() const;
	Math::Vector3 GetRight() const;
	Math::Vector3 GetUp() const;
	Math::Vector3 GetLookAt() const;

private:
	void UpdateViewMatrix() const;

	mutable Math::Matrix4 m_ViewMatrix;
	mutable OrthographicProjectionMatrix *m_OrthographicProjectionMatrix;
	mutable PerspectiveProjectionMatrix *m_PerspectiveProjectionMatrix;
	mutable ProjectionMatrix *m_ProjectionMatrix;
	mutable Frustum *m_Frustum;

	Math::Vector3 m_Target;
	Math::EHandedness m_Handedness;
	mutable bool m_FrustumDirty;

	Math::Vector3 m_Translation;
	mutable Math::Matrix4 m_Transform;
	mutable bool m_ViewMatrixDirty;
};

END_NAMESPACE(Graphics)
