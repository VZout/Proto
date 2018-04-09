#include "PerspectiveProjectionMatrix.h"

#include "Math/Matrix4.h"
#include "Math/DegToRad.h"
#include "Platform/Debug/AssertMessage.h"
#include "EProjectionMatrix.h"

USING_NAMESPACE(Math)
USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Graphics)

PerspectiveProjectionMatrix::PerspectiveProjectionMatrix(Math::EHandedness a_Handedness /* = Math::EHandedness_Left */)
: ProjectionMatrix(EProjectionMatrix_Perspective, a_Handedness)
, m_FOVDegrees(60.0f)
, m_FOVRadians(DegToRad(m_FOVDegrees))
, m_AspectRatio(1.0f)
{
}

PerspectiveProjectionMatrix::~PerspectiveProjectionMatrix()
{
}

void PerspectiveProjectionMatrix::Initialize(float a_FOVDegrees, float a_AspectRatio, float a_Near, float a_Far)
{
	m_FOVDegrees = a_FOVDegrees;
	m_FOVRadians = DegToRad(m_FOVDegrees);
	m_AspectRatio = a_AspectRatio;
	m_Near = a_Near;
	m_Far = a_Far;
	m_MatrixDirty = true;
	m_InverseMatrixDirty = true;
}

float PerspectiveProjectionMatrix::GetFOV(EUnit a_Unit) const
{
	float fov = 0.0f;
	switch (a_Unit)
	{
		case EUnit_Degrees:
		{
			fov = m_FOVDegrees;
			break;
		}
		case EUnit_Radians:
		{
			fov = m_FOVRadians;
			break;
		}
	}
	return fov;
}

float PerspectiveProjectionMatrix::GetAspectRatio() const
{
	return m_AspectRatio;
}

void PerspectiveProjectionMatrix::UpdateMatrix() const
{
	AssertMessage(m_Near < m_Far, ("Invalid near and far setting for perspective projection matrix!"));
	switch (m_Handedness)
	{
		case Math::EHandedness_Left:
		{
			m_Matrix = CreatePerspectiveLH(m_FOVRadians, m_AspectRatio, m_Near, m_Far);
			break;
		}
		case Math::EHandedness_Right:
		{
			m_Matrix = CreatePerspectiveRH(m_FOVRadians, m_AspectRatio, m_Near, m_Far);
			break;
		}
		default:
		{
			AssertMessage("Invalid handedness set for camera!");
			break;
		}
	}
	m_InverseMatrixDirty = true;
	m_MatrixDirty = false;
}

// void* PerspectiveProjectionMatrix::operator new(size_t a_Size)
// {
// 	return _aligned_malloc(a_Size, 16);
// }

// void PerspectiveProjectionMatrix::operator delete(void *a_Pointer)
// {
// 	PerspectiveProjectionMatrix *projectionMatrix = reinterpret_cast<PerspectiveProjectionMatrix*>(a_Pointer);
// 	projectionMatrix->~PerspectiveProjectionMatrix();
// 	_aligned_free(projectionMatrix);
// }

END_NAMESPACE(Graphics)
