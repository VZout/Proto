#include "OrthographicProjectionMatrix.h"

#include "EProjectionMatrix.h"
#include "Math/Matrix4.h"
#include "Platform/Debug/AssertMessage.h"

USING_NAMESPACE(Math)
USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Graphics)

OrthographicProjectionMatrix::OrthographicProjectionMatrix(Math::EHandedness a_Handedness /* = Math::EHandedness_Left */)
: ProjectionMatrix(EProjectionMatrix_Orthographic, a_Handedness)
{
}

OrthographicProjectionMatrix::~OrthographicProjectionMatrix()
{
}

void OrthographicProjectionMatrix::Initialize(uint32_t a_Left, uint32_t a_Right, uint32_t a_Bottom, uint32_t a_Top, float a_Near /* = -1.0f */, float a_Far /* = 1.0f */)
{
	m_Left = static_cast<float>(a_Left);
	m_Right = static_cast<float>(a_Right);
	m_Bottom = static_cast<float>(a_Bottom);
	m_Top = static_cast<float>(a_Top);
	m_Near = a_Near;
	m_Far = a_Far;
	m_MatrixDirty = true;
	m_InverseMatrixDirty = true;
}

void OrthographicProjectionMatrix::UpdateMatrix() const
{
	AssertMessage(m_Near < m_Far, ("Invalid near and far setting for orthographic projection matrix!"));
	switch (m_Handedness)
	{
		case Math::EHandedness_Left:
		{
			m_Matrix = CreateOrthoLH(m_Left, m_Right, m_Bottom, m_Top, m_Near, m_Far);
			break;
		}
		case Math::EHandedness_Right:
		{
			m_Matrix = CreateOrthoRH(m_Left, m_Right, m_Bottom, m_Top, m_Near, m_Far);
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

uint32_t OrthographicProjectionMatrix::GetLeft() const
{
	return static_cast<uint32_t>(m_Left);
}

uint32_t OrthographicProjectionMatrix::GetRight() const
{
	return static_cast<uint32_t>(m_Right);
}

uint32_t OrthographicProjectionMatrix::GetBottom() const
{
	return static_cast<uint32_t>(m_Bottom);
}

uint32_t OrthographicProjectionMatrix::GetTop() const
{
	return static_cast<uint32_t>(m_Top);
}

// void* OrthographicProjectionMatrix::operator new(size_t a_Size)
// {
// 	return _aligned_malloc(a_Size, 16);
// }

// void OrthographicProjectionMatrix::operator delete(void *a_Pointer)
// {
// 	OrthographicProjectionMatrix *projectionMatrix = reinterpret_cast<OrthographicProjectionMatrix*>(a_Pointer);
// 	projectionMatrix->~OrthographicProjectionMatrix();
// 	_aligned_free(projectionMatrix);
// }

END_NAMESPACE(Graphics)
