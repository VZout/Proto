#include "Camera.h"

#include "CreateViewMatrix.h"
#include "Frustum2D.h"
#include "Frustum3D.h"
#include "Math/Clamp.h"
#include "Math/Cos.h"
#include "Math/DegToRad.h"
#include "Math/Sin.h"
#include "Math/Vector3.h"
#include "Platform/Debug/AssertMessage.h"
#include "CreateFrustum.h"
#include "ProjectionMatrix.h"
#include "OrthographicProjectionMatrix.h"
#include "PerspectiveProjectionMatrix.h"

USING_NAMESPACE(Math)
USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Graphics)

Camera::Camera(EHandedness a_Handedness /* = EHandedness_Left */)
	: m_Handedness(a_Handedness)
	, m_FrustumDirty(true)
{
}

Camera::~Camera()
{
	delete m_Frustum;
	delete m_OrthographicProjectionMatrix;
	delete m_PerspectiveProjectionMatrix;
}

// TO TEST: Camera::SetLookAt
void Camera::SetLookAt(const Vector3 &a_EyePosition, const Vector3 &a_TargetPosition, const Vector3 &a_Up /* = Vector3::Y_AXIS */)
{
	switch (m_Handedness)
	{
	case EHandedness_Left:
		{
			m_ViewMatrix = CreateViewMatrixLH(a_EyePosition, a_TargetPosition, a_Up);
			break;
		}
	case EHandedness_Right:
		{
			m_ViewMatrix = CreateViewMatrixRH(a_EyePosition, a_TargetPosition, a_Up);
			break;
		}
	default:
		{
			AssertMessage("Invalid handedness set for camera!");
			break;
		}
	}

	m_Transform = Inverse(m_ViewMatrix);
	m_Target = a_TargetPosition;
}

const Matrix4& Camera::GetViewMatrix() const
{
	if (m_ViewMatrixDirty)
	{
		UpdateViewMatrix();
	}
	return m_ViewMatrix;
}

const Matrix4& Camera::GetInverseViewMatrix() const
{
	return m_Transform;
}

void Camera::CreatePerspectiveLens(float a_FOVDegrees, float a_AspectRatio, float a_Near, float a_Far)
{
	if (nullptr == m_PerspectiveProjectionMatrix)
	{
		m_PerspectiveProjectionMatrix = new PerspectiveProjectionMatrix(m_Handedness);
		AssertMessage(nullptr != m_PerspectiveProjectionMatrix, ("Failed to create perspective projection matrix!"));
		m_PerspectiveProjectionMatrix->Initialize(a_FOVDegrees, a_AspectRatio, a_Near, a_Far);

		m_Frustum = new Frustum3D();
		m_FrustumDirty = true;
	}
	m_ProjectionMatrix = m_PerspectiveProjectionMatrix;
}

void Camera::CreateOrthographicLens(uint32_t a_Left, uint32_t a_Right, uint32_t a_Bottom, uint32_t a_Top, float a_Near /* = -1.0f */, float a_Far /* = 1.0f */)
{
	if (nullptr == m_OrthographicProjectionMatrix)
	{
		m_OrthographicProjectionMatrix = new OrthographicProjectionMatrix(m_Handedness);
		AssertMessage(nullptr != m_OrthographicProjectionMatrix, ("Failed to create orthographic projection matrix!"));
		m_OrthographicProjectionMatrix->Initialize(a_Left, a_Right, a_Bottom, a_Top, a_Near, a_Far);
		m_Frustum = new Frustum2D();
		m_FrustumDirty = true;
	}
	m_ProjectionMatrix = m_OrthographicProjectionMatrix;
}

void Camera::SetLens(ELens a_Lens)
{
	switch (a_Lens)
	{
	case Graphics::Camera::ELens_Perspective:
		{
			AssertMessage(nullptr != m_PerspectiveProjectionMatrix, "No perspective lens available!");
			m_ProjectionMatrix = m_PerspectiveProjectionMatrix;
			break;
		}
	case Graphics::Camera::ELens_Orthographic:
		{
			AssertMessage(nullptr != m_OrthographicProjectionMatrix, "No orthographic lens available!");
			m_ProjectionMatrix = m_OrthographicProjectionMatrix;
			break;
		}
	default:
		{
			AssertMessage("Invalid lens requested!");
			break;
		}
	}
}

const ProjectionMatrix& Camera::GetProjectionMatrix() const
{
	AssertMessage(nullptr != m_ProjectionMatrix, "Attempt to access an invalid projection matrix!");
	return *m_ProjectionMatrix;
}

void Camera::SetPosition(const Vector3 &a_Position)
{
	m_Transform.m[3][0] = a_Position.m_X; 
	m_Transform.m[3][1] = a_Position.m_Y; 
	m_Transform.m[3][2] = a_Position.m_Z; 
	m_Transform.m[3][3] = 1.0f;
	m_ViewMatrixDirty = true;
}

Vector3 Camera::GetPosition() const
{
	return Vector3(m_Transform.m[3][0], m_Transform.m[3][1], m_Transform.m[3][2]);
}

void Camera::SetTarget(const Vector3 &a_Target)
{
	const Vector3 position = m_Transform.GetTranslation();
	SetLookAt(a_Target, position);
}

Vector3 Camera::GetTarget() const
{
	AssertMessage("Not implemented!");
	return m_Target;
}

void Camera::Translate(const Vector3 &a_Translation, ESpace a_Space /* = ESpace_Local */)
{
	switch (a_Space)
	{
	case ESpace_Local:
		{
			if (LengthSquared(a_Translation) > 0.0f)
			{
				const Vector3 forward = m_Transform.GetZAxis();
				const Vector3 right = m_Transform.GetXAxis();
				const Vector3 up = Normalize(Cross(forward, right));
				m_Translation = (forward * a_Translation.m_Z) + (right * a_Translation.m_X) + (up * a_Translation.m_Y);

				m_Transform.m[3][0] += m_Translation.m_X;
				m_Transform.m[3][1] += m_Translation.m_Y;
				m_Transform.m[3][2] += m_Translation.m_Z;
				m_Target += a_Translation;
				m_ViewMatrixDirty = true;
			}
			else
			{
				m_Translation = Vector3(0.0f, 0.0f, 0.0f);
			}
			break;
		}
	case ESpace_World:
		{
			if (LengthSquared(a_Translation) > 0.0f)
			{
				AssertMessage("Not implemented!");
			}
			break;
		}
	default:
		{
			AssertMessage("Invalid space encountered");
			break;
		}
	}
}

void Camera::Rotate(float a_Pitch, float a_Yaw, float a_Roll, ERotationMultiplicationOrder a_Order /* = Math::ERotationMultiplicationOrder_XYZ */)
{
	UNUSED(a_Order);
	if (AnyNonZero(Vector3(a_Pitch, a_Yaw, a_Roll)))
	{
		const Matrix4 rotation = CreateRotate(a_Pitch, a_Yaw, a_Roll);
		const Matrix4 translation = CreateTranslation(m_Translation);
		m_Transform = m_Transform * (rotation * translation);

		m_ViewMatrixDirty = true;
	}
}

EHandedness Camera::GetHandedness() const
{
	return m_Handedness;
}

const Frustum& Camera::GetFrustum() const
{
	if (m_FrustumDirty)
	{
		EProjectionMatrix type = m_ProjectionMatrix->GetType();
		switch (type)
		{
		case EProjectionMatrix_Perspective:
			{
				Frustum3D *frustum = static_cast<Frustum3D*>(m_Frustum);
				CreateFrustum(*frustum, *this);
				break;
			}
		case EProjectionMatrix_Orthographic:
			{
				Frustum2D *frustum = static_cast<Frustum2D*>(m_Frustum);
				CreateFrustum(*frustum, *this);
				break;
			}
		default:
			{
				AssertMessage(("Invalid projection matrix type encountered!"));
				break;
			}
		}
		m_FrustumDirty = false;
	}
	return *m_Frustum;
}



Vector3 Camera::GetRight() const
{
	if (m_ViewMatrixDirty)
	{
		UpdateViewMatrix();
	}
	return m_ViewMatrix.GetXAxis();
}

Vector3 Camera::GetUp() const
{
	if (m_ViewMatrixDirty)
	{
		UpdateViewMatrix();
	}
	return m_ViewMatrix.GetYAxis();
}

Vector3 Camera::GetLookAt() const
{
	if (m_ViewMatrixDirty)
	{
		UpdateViewMatrix();
	}
	return m_ViewMatrix.GetZAxis();
}

void Camera::UpdateViewMatrix() const
{
	m_ViewMatrix = Inverse(m_Transform);
	m_ViewMatrixDirty = false;
}

END_NAMESPACE(Graphics)
