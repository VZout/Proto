#include "CreateViewMatrix.h"

// TODO: Move to Math library

#include "Math/Helpers/GLMIncludes.h"
#include "Math/Quaternion.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Platform/Debug/AssertMessage.h"

USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Math)

BEGIN_UNNAMEDNAMESPACE()

Matrix4 LookAtMatrixLH(const Vector3 &a_EyePosition, const Vector3 &a_Direction, const Vector3 &a_Up)
{
	const Vector3 R2 = Normalize(a_Direction);
	Vector3 R0 = Normalize(Cross(a_Up, R2));

	const Vector3 R1 = Cross(R2, R0);
	const Vector3 negatedEyePosition = Negate(a_EyePosition);

	const float D0 = Dot(R0, negatedEyePosition);
	const float D1 = Dot(R1, negatedEyePosition);
	const float D2 = Dot(R2, negatedEyePosition);

	return Transpose(Matrix4(Vector4(R0, D0), Vector4(R1, D1), Vector4(R2, D2), Vector4(0.0f, 0.0f, 0.0f, 1.0f)));
}

END_UNNAMEDNAMESPACE()

Matrix4 CreateViewMatrixLH(const Vector3 &a_EyePosition, const Vector3 &a_TargetPosition, const Vector3 &a_Up)
{
	const Vector3 eyeDirection = a_TargetPosition - a_EyePosition;
	return LookAtMatrixLH(a_EyePosition, eyeDirection, a_Up);
}

Matrix4 CreateViewMatrixLH(const Quaternion &a_Orientation, const Vector3 &a_Position)
{
	Matrix4 rotationMatrix(a_Orientation);
	Matrix4 translationMatrix = CreateTranslation(a_Position);
	return rotationMatrix * Inverse(translationMatrix);
}

Matrix4 CreateViewMatrixRH(const Vector3 &a_EyePosition, const Vector3 &a_TargetPosition, const Vector3 &a_Up)
{
	const Vector3 negativeEyeDirection = a_EyePosition - a_TargetPosition;
	return LookAtMatrixLH(a_EyePosition, negativeEyeDirection, a_Up);
}

Matrix4 CreateViewMatrixRH(const Quaternion &a_Orientation, const Vector3 &a_Position)
{
	Vector3 targetPosition = a_Position + Rotate(Vector3::NEG_Z_AXIS, a_Orientation);
	return CreateViewMatrixRH(a_Position, targetPosition, Vector3::Y_AXIS);
}

END_NAMESPACE(Math)
