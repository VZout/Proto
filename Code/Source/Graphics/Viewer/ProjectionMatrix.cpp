#include "ProjectionMatrix.h"

USING_NAMESPACE(Math)

BEGIN_NAMESPACE(Graphics)

ProjectionMatrix::ProjectionMatrix(EProjectionMatrix a_Type, Math::EHandedness a_Handedness)
: m_Type(a_Type)
, m_Handedness(a_Handedness)
, m_Near(0.01f)
, m_Far(1000.0f)
, m_MatrixDirty(true)
, m_InverseMatrixDirty(true)
{
}

ProjectionMatrix::~ProjectionMatrix()
{
}

Matrix4& ProjectionMatrix::GetMatrix()
{
	return const_cast<Matrix4&>(const_cast<const ProjectionMatrix*>(this)->GetMatrix());
}

const Matrix4& ProjectionMatrix::GetMatrix() const
{
	if (m_MatrixDirty)
	{
		UpdateMatrix();
	}
	return m_Matrix;
}

Math::Matrix4& ProjectionMatrix::GetInverseMatrix()
{
	return const_cast<Matrix4&>(const_cast<const ProjectionMatrix*>(this)->GetInverseMatrix());
}

const Math::Matrix4& ProjectionMatrix::GetInverseMatrix() const
{
	if (m_InverseMatrixDirty)
	{
		UpdateInverseMatrix();
	}
	return m_Inverse;
}

float ProjectionMatrix::GetNear() const
{
	return m_Near;
}

float ProjectionMatrix::GetFar() const
{
	return m_Far;
}

EProjectionMatrix ProjectionMatrix::GetType() const
{
	return m_Type;
}

void ProjectionMatrix::SetHandedness(EHandedness a_Handedness)
{
	if (m_Handedness != a_Handedness)
	{
		m_MatrixDirty = true;
		m_InverseMatrixDirty = true;
		m_Handedness = a_Handedness;
	}
}

EHandedness ProjectionMatrix::GetHandedness() const
{
	return m_Handedness;
}

void ProjectionMatrix::UpdateInverseMatrix() const
{
	m_Inverse = Inverse(m_Matrix);
	m_InverseMatrixDirty = false;
}

END_NAMESPACE(Graphics)
