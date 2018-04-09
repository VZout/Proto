#pragma once

#include "Proto.h"
#include "Math/EHandedness.h"
#include "Math/Matrix4.h"
#include "Utility/NoCopy.h"
#include "EProjectionMatrix.h"

BEGIN_NAMESPACE(Graphics)

class ProjectionMatrix :public Utility::NoCopy
{
protected:
	ProjectionMatrix(EProjectionMatrix a_Type, Math::EHandedness a_Handedness);

public:
	~ProjectionMatrix();

	Math::Matrix4& GetMatrix();
	const Math::Matrix4& GetMatrix() const;
	Math::Matrix4& GetInverseMatrix();
	const Math::Matrix4& GetInverseMatrix() const;

	float GetNear() const;
	float GetFar() const;
	EProjectionMatrix GetType() const;

	void SetHandedness(Math::EHandedness a_Handedness);
	Math::EHandedness GetHandedness() const;

protected:
	float m_Near;
	float m_Far;
	mutable bool m_MatrixDirty;
	mutable bool m_InverseMatrixDirty;
	Math::EHandedness m_Handedness;
	mutable Math::Matrix4 m_Matrix;

private:
	virtual void UpdateMatrix() const = 0;
	void UpdateInverseMatrix() const;

	EProjectionMatrix m_Type;
	mutable Math::Matrix4 m_Inverse;
};

END_NAMESPACE(Graphics)
