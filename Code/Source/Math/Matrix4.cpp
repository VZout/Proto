#include "Matrix4.h"

#include "Helpers/GLMIncludes.h"

#include "Constants.h"
#include "DegToRad.h"
#include "RadToDeg.h"
#include "Platform/Debug/AssertMessage.h"
#include "Quaternion.h"
#include "Trigonometry.h"
#include "Vector4.h"

#include <math.h>
#include <utility>

USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Math)

Matrix4::Matrix4()
{
	::memset(static_cast<void*>(m), 0x0, 4 * 4 * sizeof(float));

	m[0][0] = 1.0f;
	m[1][1] = 1.0f;
	m[2][2] = 1.0f;
	m[3][3] = 1.0f;
}

Matrix4::Matrix4(float a_00, float a_01, float a_02, float a_03,
	float a_10, float a_11, float a_12, float a_13,
	float a_20, float a_21, float a_22, float a_23,
	float a_30, float a_31, float a_32, float a_33)
{
	m[0][0] = a_00; m[0][1] = a_01; m[0][2] = a_02; m[0][3] = a_03;
	m[1][0] = a_10; m[1][1] = a_11; m[1][2] = a_12; m[1][3] = a_13;
	m[2][0] = a_20; m[2][1] = a_21; m[2][2] = a_22; m[2][3] = a_23;
	m[3][0] = a_30; m[3][1] = a_31; m[3][2] = a_32; m[3][3] = a_33;
}

Matrix4::Matrix4(const Vector4 &a_XAxis, const Vector4 &a_YAxis, const Vector4 &a_ZAxis, const Vector4 &a_Translation)
{
	f[0] = a_XAxis.m_X;
	f[1] = a_XAxis.m_Y;
	f[2] = a_XAxis.m_Z;
	f[3] = a_XAxis.m_W;

	f[4] = a_YAxis.m_X;
	f[5] = a_YAxis.m_Y;
	f[6] = a_YAxis.m_Z;
	f[7] = a_YAxis.m_W;
	
	f[8] = a_ZAxis.m_X;
	f[9] = a_ZAxis.m_Y;
	f[10] = a_ZAxis.m_Z;
	f[11] = a_ZAxis.m_W;

	f[12] = a_Translation.m_X;
	f[13] = a_Translation.m_Y;
	f[14] = a_Translation.m_Z;
	f[15] = 1.0f;
}

Matrix4::Matrix4(const Matrix4 &a_Rhs)
{
	memcpy(f, a_Rhs.f, 16 * sizeof(float));
// 	for (uint32_t index = 0; index < 16; ++index)
// 	{
// 		f[index] = a_Rhs.f[index];
// 	}
}

Matrix4::Matrix4(const Quaternion &a_Quat)
{
	memset(f, 0, 16 * sizeof(float));
	const float qxx = a_Quat.m_X * a_Quat.m_X;
	const float qyy = a_Quat.m_Y * a_Quat.m_Y;
	const float qzz = a_Quat.m_Z * a_Quat.m_Z;
	const float qxz = a_Quat.m_X * a_Quat.m_Z;
	const float qxy = a_Quat.m_X * a_Quat.m_Y;
	const float qyz = a_Quat.m_Y * a_Quat.m_Z;
	const float qwx = a_Quat.m_W * a_Quat.m_X;
	const float qwy = a_Quat.m_W * a_Quat.m_Y;
	const float qwz = a_Quat.m_W * a_Quat.m_Z;

	m[0][0] = 1 - 2 * (qyy + qzz);
	m[0][1] = 2 * (qxy + qwz);
	m[0][2] = 2 * (qxz - qwy);

	m[1][0] = 2 * (qxy - qwz);
	m[1][1] = 1 - 2 * (qxx + qzz);
	m[1][2] = 2 * (qyz + qwx);

	m[2][0] = 2 * (qxz + qwy);
	m[2][1] = 2 * (qyz - qwx);
	m[2][2] = 1 - 2 * (qxx + qyy);
}

Matrix4::~Matrix4()
{
}

Matrix4& Matrix4::operator=(Matrix4 a_Rhs)
{
	swap(*this, a_Rhs);
	return *this;
}

Matrix4& Matrix4::operator+=(const Matrix4 &a_Rhs)
{
	for (uint32_t index = 0; index < 16; ++index)
	{
		f[index] += a_Rhs.f[index];
	}
	return *this;
}

Matrix4& Matrix4::operator-=(const Matrix4 &a_Rhs)
{
	for (uint32_t index = 0; index < 16; ++index)
	{
		f[index] -= a_Rhs.f[index];
	}
	return *this;
}

Matrix4& Matrix4::operator*=(const Matrix4 &a_Rhs)
{
	Matrix4 result;
	for (int i = 0; i < 4; i++)
	{
		result.m[i][0] = a_Rhs.m[i][0] * m[0][0] +
			a_Rhs.m[i][1] * m[1][0] +
			a_Rhs.m[i][2] * m[2][0] +
			a_Rhs.m[i][3] * m[3][0];

		result.m[i][1] = a_Rhs.m[i][0] * m[0][1] +
			a_Rhs.m[i][1] * m[1][1] +
			a_Rhs.m[i][2] * m[2][1] +
			a_Rhs.m[i][3] * m[3][1];

		result.m[i][2] = a_Rhs.m[i][0] * m[0][2] +
			a_Rhs.m[i][1] * m[1][2] +
			a_Rhs.m[i][2] * m[2][2] +
			a_Rhs.m[i][3] * m[3][2];

		result.m[i][3] = a_Rhs.m[i][0] * m[0][3] +
			a_Rhs.m[i][1] * m[1][3] +
			a_Rhs.m[i][2] * m[2][3] +
			a_Rhs.m[i][3] * m[3][3];
	}
	*this = result;
	return *this;
}

void Matrix4::SetTranslation(float a_X, float a_Y, float a_Z)
{
	m[3][0] = a_X;
	m[3][1] = a_Y;
	m[3][2] = a_Z;
}

void Matrix4::SetTranslation(const Vector3 &a_Translation)
{
	m[3][0] = a_Translation.m_X;
	m[3][1] = a_Translation.m_Y;
	m[3][2] = a_Translation.m_Z;
}

Vector3 Matrix4::GetTranslation() const
{
	return Vector3(m[3][0], m[3][1], m[3][2]);
}

Vector3 Matrix4::GetXAxis() const
{
	return Vector3(m[0][0], m[0][1], m[0][2]);
}

Vector3 Matrix4::GetYAxis() const
{
	return Vector3(m[1][0], m[1][1], m[1][2]);
}

Vector3 Matrix4::GetZAxis() const
{
	return Vector3(m[2][0], m[2][1], m[2][2]);
}

void Matrix4::SetOrientation(const Vector3 &a_XAxis, const Vector3 &a_YAxis, const Vector3 &a_ZAxis)
{
	// TODO: Check orthogonality with an assert
	m[0][0] = a_XAxis.m_X; m[0][1] = a_XAxis.m_Y; m[0][2] = a_XAxis.m_Z;
	m[1][0] = a_YAxis.m_X; m[1][1] = a_YAxis.m_Y; m[1][2] = a_YAxis.m_Z;
	m[2][0] = a_ZAxis.m_X; m[2][1] = a_ZAxis.m_Y; m[2][2] = a_ZAxis.m_Z;
}

void Matrix4::SetEulerAxis(float a_Yaw, float a_Pitch, float a_Roll)
{
	//AssertMessage("Broken!");

	const float phi = a_Pitch;
	const float psi = a_Yaw;
	const float theta = a_Roll;

	Matrix4 newMatrix;

	newMatrix.m[0][0] = cosf(psi) * cosf(phi) - cosf(theta) * sinf(phi) * sinf(psi);
	newMatrix.m[0][1] = cosf(psi) * sinf(phi) + cosf(theta) * cosf(phi) * sinf(psi);
	newMatrix.m[0][2] = sinf(psi) * sinf(theta);

	newMatrix.m[1][0] = -sinf(psi) * cosf(phi) - cosf(theta) * sinf(phi) * cosf(psi);
	newMatrix.m[1][1] = -sinf(psi) * sinf(phi) + cosf(theta) * cosf(phi) * cosf(psi);
	newMatrix.m[1][2] = cosf(psi) * sinf(theta);

	newMatrix.m[2][0] = sinf(theta) * sinf(phi);
	newMatrix.m[2][1] = -sinf(theta) * cosf(phi);
	newMatrix.m[2][2] = cosf(theta);

	*this *= Transpose(newMatrix);
}

Matrix4 operator+(Matrix4 a_Lhs, const Matrix4 &a_Rhs)
{
	a_Lhs += a_Rhs;
	return a_Lhs;
}

Matrix4 operator-(Matrix4 a_Lhs, const Matrix4 &a_Rhs)
{
	a_Lhs -= a_Rhs;
	return a_Lhs;
}

Matrix4 operator*(Matrix4 a_Lhs, const Matrix4 &a_Rhs)
{
	a_Lhs *= a_Rhs;
	return a_Lhs;
}

Vector3 operator*(const Matrix4 &a_Rhs, const Vector3& a_Vector)
{
	return Transform(a_Rhs, a_Vector);
}

bool operator==(const Matrix4 &a_Lhs, const Matrix4 &a_Rhs)
{
	for (uint32_t index = 0; index < 16; ++index)
	{
		if (a_Lhs.f[index] != a_Rhs.f[index])
		{
			return false;
		}
	}
	return true;
}

bool operator!=(const Matrix4 &a_Lhs, const Matrix4 &a_Rhs)
{
	return !(a_Lhs == a_Rhs);
}

bool operator< (const Matrix4 &a_Lhs, const Matrix4 &a_Rhs)
{
	for (uint32_t index = 0; index < 16; ++index)
	{
		if (a_Lhs.f[index] < a_Rhs.f[index])
		{
			return true;
		}
	}
	return false;
}

bool operator> (const Matrix4 &a_Lhs, const Matrix4 &a_Rhs)
{
	return (a_Rhs < a_Lhs);
}

bool operator<=(const Matrix4 &a_Lhs, const Matrix4 &a_Rhs)
{
	return !(a_Lhs > a_Rhs);
}

bool operator>=(const Matrix4 &a_Lhs, const Matrix4 &a_Rhs)
{
	return !(a_Lhs < a_Rhs);
}

float Determinant(const Matrix4 &a_Value)
{
	return a_Value.f[2] * a_Value.f[5] * a_Value.f[8] +
		a_Value.f[1] * a_Value.f[6] * a_Value.f[8] +
		a_Value.f[2] * a_Value.f[4] * a_Value.f[9] -
		a_Value.f[0] * a_Value.f[6] * a_Value.f[9] -
		a_Value.f[1] * a_Value.f[4] * a_Value.f[10] +
		a_Value.f[0] * a_Value.f[5] * a_Value.f[10];
}

Matrix4 Inverse(const Matrix4 &a_Matrix)
{
	Matrix4 inverse;

	inverse.f[0] = a_Matrix.f[5] * a_Matrix.f[10] * a_Matrix.f[15] -
		a_Matrix.f[5] * a_Matrix.f[11] * a_Matrix.f[14] -
		a_Matrix.f[9] * a_Matrix.f[6] * a_Matrix.f[15] +
		a_Matrix.f[9] * a_Matrix.f[7] * a_Matrix.f[14] +
		a_Matrix.f[13] * a_Matrix.f[6] * a_Matrix.f[11] -
		a_Matrix.f[13] * a_Matrix.f[7] * a_Matrix.f[10];

	inverse.f[4] = -a_Matrix.f[4] * a_Matrix.f[10] * a_Matrix.f[15] +
		a_Matrix.f[4] * a_Matrix.f[11] * a_Matrix.f[14] +
		a_Matrix.f[8] * a_Matrix.f[6] * a_Matrix.f[15] -
		a_Matrix.f[8] * a_Matrix.f[7] * a_Matrix.f[14] -
		a_Matrix.f[12] * a_Matrix.f[6] * a_Matrix.f[11] +
		a_Matrix.f[12] * a_Matrix.f[7] * a_Matrix.f[10];

	inverse.f[8] = a_Matrix.f[4] * a_Matrix.f[9] * a_Matrix.f[15] -
		a_Matrix.f[4] * a_Matrix.f[11] * a_Matrix.f[13] -
		a_Matrix.f[8] * a_Matrix.f[5] * a_Matrix.f[15] +
		a_Matrix.f[8] * a_Matrix.f[7] * a_Matrix.f[13] +
		a_Matrix.f[12] * a_Matrix.f[5] * a_Matrix.f[11] -
		a_Matrix.f[12] * a_Matrix.f[7] * a_Matrix.f[9];

	inverse.f[12] = -a_Matrix.f[4] * a_Matrix.f[9] * a_Matrix.f[14] +
		a_Matrix.f[4] * a_Matrix.f[10] * a_Matrix.f[13] +
		a_Matrix.f[8] * a_Matrix.f[5] * a_Matrix.f[14] -
		a_Matrix.f[8] * a_Matrix.f[6] * a_Matrix.f[13] -
		a_Matrix.f[12] * a_Matrix.f[5] * a_Matrix.f[10] +
		a_Matrix.f[12] * a_Matrix.f[6] * a_Matrix.f[9];

	inverse.f[1] = -a_Matrix.f[1] * a_Matrix.f[10] * a_Matrix.f[15] +
		a_Matrix.f[1] * a_Matrix.f[11] * a_Matrix.f[14] +
		a_Matrix.f[9] * a_Matrix.f[2] * a_Matrix.f[15] -
		a_Matrix.f[9] * a_Matrix.f[3] * a_Matrix.f[14] -
		a_Matrix.f[13] * a_Matrix.f[2] * a_Matrix.f[11] +
		a_Matrix.f[13] * a_Matrix.f[3] * a_Matrix.f[10];

	inverse.f[5] = a_Matrix.f[0] * a_Matrix.f[10] * a_Matrix.f[15] -
		a_Matrix.f[0] * a_Matrix.f[11] * a_Matrix.f[14] -
		a_Matrix.f[8] * a_Matrix.f[2] * a_Matrix.f[15] +
		a_Matrix.f[8] * a_Matrix.f[3] * a_Matrix.f[14] +
		a_Matrix.f[12] * a_Matrix.f[2] * a_Matrix.f[11] -
		a_Matrix.f[12] * a_Matrix.f[3] * a_Matrix.f[10];

	inverse.f[9] = -a_Matrix.f[0] * a_Matrix.f[9] * a_Matrix.f[15] +
		a_Matrix.f[0] * a_Matrix.f[11] * a_Matrix.f[13] +
		a_Matrix.f[8] * a_Matrix.f[1] * a_Matrix.f[15] -
		a_Matrix.f[8] * a_Matrix.f[3] * a_Matrix.f[13] -
		a_Matrix.f[12] * a_Matrix.f[1] * a_Matrix.f[11] +
		a_Matrix.f[12] * a_Matrix.f[3] * a_Matrix.f[9];

	inverse.f[13] = a_Matrix.f[0] * a_Matrix.f[9] * a_Matrix.f[14] -
		a_Matrix.f[0] * a_Matrix.f[10] * a_Matrix.f[13] -
		a_Matrix.f[8] * a_Matrix.f[1] * a_Matrix.f[14] +
		a_Matrix.f[8] * a_Matrix.f[2] * a_Matrix.f[13] +
		a_Matrix.f[12] * a_Matrix.f[1] * a_Matrix.f[10] -
		a_Matrix.f[12] * a_Matrix.f[2] * a_Matrix.f[9];

	inverse.f[2] = a_Matrix.f[1] * a_Matrix.f[6] * a_Matrix.f[15] -
		a_Matrix.f[1] * a_Matrix.f[7] * a_Matrix.f[14] -
		a_Matrix.f[5] * a_Matrix.f[2] * a_Matrix.f[15] +
		a_Matrix.f[5] * a_Matrix.f[3] * a_Matrix.f[14] +
		a_Matrix.f[13] * a_Matrix.f[2] * a_Matrix.f[7] -
		a_Matrix.f[13] * a_Matrix.f[3] * a_Matrix.f[6];

	inverse.f[6] = -a_Matrix.f[0] * a_Matrix.f[6] * a_Matrix.f[15] +
		a_Matrix.f[0] * a_Matrix.f[7] * a_Matrix.f[14] +
		a_Matrix.f[4] * a_Matrix.f[2] * a_Matrix.f[15] -
		a_Matrix.f[4] * a_Matrix.f[3] * a_Matrix.f[14] -
		a_Matrix.f[12] * a_Matrix.f[2] * a_Matrix.f[7] +
		a_Matrix.f[12] * a_Matrix.f[3] * a_Matrix.f[6];

	inverse.f[10] = a_Matrix.f[0] * a_Matrix.f[5] * a_Matrix.f[15] -
		a_Matrix.f[0] * a_Matrix.f[7] * a_Matrix.f[13] -
		a_Matrix.f[4] * a_Matrix.f[1] * a_Matrix.f[15] +
		a_Matrix.f[4] * a_Matrix.f[3] * a_Matrix.f[13] +
		a_Matrix.f[12] * a_Matrix.f[1] * a_Matrix.f[7] -
		a_Matrix.f[12] * a_Matrix.f[3] * a_Matrix.f[5];

	inverse.f[14] = -a_Matrix.f[0] * a_Matrix.f[5] * a_Matrix.f[14] +
		a_Matrix.f[0] * a_Matrix.f[6] * a_Matrix.f[13] +
		a_Matrix.f[4] * a_Matrix.f[1] * a_Matrix.f[14] -
		a_Matrix.f[4] * a_Matrix.f[2] * a_Matrix.f[13] -
		a_Matrix.f[12] * a_Matrix.f[1] * a_Matrix.f[6] +
		a_Matrix.f[12] * a_Matrix.f[2] * a_Matrix.f[5];

	inverse.f[3] = -a_Matrix.f[1] * a_Matrix.f[6] * a_Matrix.f[11] +
		a_Matrix.f[1] * a_Matrix.f[7] * a_Matrix.f[10] +
		a_Matrix.f[5] * a_Matrix.f[2] * a_Matrix.f[11] -
		a_Matrix.f[5] * a_Matrix.f[3] * a_Matrix.f[10] -
		a_Matrix.f[9] * a_Matrix.f[2] * a_Matrix.f[7] +
		a_Matrix.f[9] * a_Matrix.f[3] * a_Matrix.f[6];

	inverse.f[7] = a_Matrix.f[0] * a_Matrix.f[6] * a_Matrix.f[11] -
		a_Matrix.f[0] * a_Matrix.f[7] * a_Matrix.f[10] -
		a_Matrix.f[4] * a_Matrix.f[2] * a_Matrix.f[11] +
		a_Matrix.f[4] * a_Matrix.f[3] * a_Matrix.f[10] +
		a_Matrix.f[8] * a_Matrix.f[2] * a_Matrix.f[7] -
		a_Matrix.f[8] * a_Matrix.f[3] * a_Matrix.f[6];

	inverse.f[11] = -a_Matrix.f[0] * a_Matrix.f[5] * a_Matrix.f[11] +
		a_Matrix.f[0] * a_Matrix.f[7] * a_Matrix.f[9] +
		a_Matrix.f[4] * a_Matrix.f[1] * a_Matrix.f[11] -
		a_Matrix.f[4] * a_Matrix.f[3] * a_Matrix.f[9] -
		a_Matrix.f[8] * a_Matrix.f[1] * a_Matrix.f[7] +
		a_Matrix.f[8] * a_Matrix.f[3] * a_Matrix.f[5];

	inverse.f[15] = a_Matrix.f[0] * a_Matrix.f[5] * a_Matrix.f[10] -
		a_Matrix.f[0] * a_Matrix.f[6] * a_Matrix.f[9] -
		a_Matrix.f[4] * a_Matrix.f[1] * a_Matrix.f[10] +
		a_Matrix.f[4] * a_Matrix.f[2] * a_Matrix.f[9] +
		a_Matrix.f[8] * a_Matrix.f[1] * a_Matrix.f[6] -
		a_Matrix.f[8] * a_Matrix.f[2] * a_Matrix.f[5];

	float det = a_Matrix.f[0] * inverse.f[0] + a_Matrix.f[1] * inverse.f[4] + a_Matrix.f[2] * inverse.f[8] + a_Matrix.f[3] * inverse.f[12];
	AssertMessage(0 != det, "Unable to calculate inverse of singular matrix!");
	det = 1.0f / det;

	for (int i = 0; i < 16; i++)
	{
		inverse.f[i] *= det;
	}
	return inverse;
}

Matrix4 Transpose(const Matrix4 &a_Matrix)
{
	Matrix4 result;
	for (uint32_t i = 0; i < 4; i++)
	{
		result.f[i + 0] = a_Matrix.m[i][0];
		result.f[i + 4] = a_Matrix.m[i][1];
		result.f[i + 8] = a_Matrix.m[i][2];
		result.f[i + 12] = a_Matrix.m[i][3];
	}
	return result;
}

Matrix4 CreateIdentity()
{
	return Matrix4();
}

Matrix4 CreateTranslation(const Vector3 &a_Translation)
{
	Matrix4 result;
	result.m[3][0] = a_Translation.m_X;
	result.m[3][1] = a_Translation.m_Y;
	result.m[3][2] = a_Translation.m_Z;
	return result;
}

Matrix4 CreateTranslation(float a_X, float a_Y, float a_Z)
{
	Matrix4 result;
	result.m[3][0] = a_X;
	result.m[3][1] = a_Y;
	result.m[3][2] = a_Z;
	return result;
}

Matrix4 CreateScale(float a_Scale)
{
	Matrix4 res;
	res.m[0][0] = a_Scale;
	res.m[1][1] = a_Scale;
	res.m[2][2] = a_Scale;
	res.m[3][3] = 1.0f;
	return res;
}

Matrix4 CreateScale(const Vector3 &a_Scale)
{
	Matrix4 res;
	res.m[0][0] = a_Scale.m_X;
	res.m[1][1] = a_Scale.m_Y;
	res.m[2][2] = a_Scale.m_Z;
	res.m[3][3] = 1.0f;
	return res;
}

Matrix4 CreateRotate(float a_Radians, const Vector3 &a_Axis)
{
	const float c = static_cast<float>(cos(a_Radians));
	const float cp = 1.0f - c;
	const float s = static_cast<float>(sin(a_Radians));

	return Matrix4(c + cp * a_Axis.m_F[0] * a_Axis.m_F[0], cp * a_Axis.m_F[0] * a_Axis.m_F[1] + a_Axis.m_F[2] * s, cp * a_Axis.m_F[0] * a_Axis.m_F[2] - a_Axis.m_F[1] * s, 0.0f,
		cp * a_Axis.m_F[0] * a_Axis.m_F[1] - a_Axis.m_F[2] * s, c + cp * a_Axis.m_F[1] * a_Axis.m_F[1], cp * a_Axis.m_F[1] * a_Axis.m_F[2] + a_Axis.m_F[0] * s, 0.0f,
		cp * a_Axis.m_F[0] * a_Axis.m_F[2] + a_Axis.m_F[1] * s, cp * a_Axis.m_F[1] * a_Axis.m_F[2] - a_Axis.m_F[0] * s, c + cp * a_Axis.m_F[2] * a_Axis.m_F[2], 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 CreateRotate(float a_Roll, float a_Pitch, float a_Yaw, Math::ERotationMultiplicationOrder a_Order /* = Math::ERotationMultiplicationOrder_XYZ */)
{
	const Matrix4 rotateX = CreateRotate(DegToRad(a_Roll), Vector3::X_AXIS);
	const Matrix4 rotateY = CreateRotate(DegToRad(a_Pitch), Vector3::Y_AXIS);
	const Matrix4 rotateZ = CreateRotate(DegToRad(a_Yaw), Vector3::Z_AXIS);

	Matrix4 rotation;
	switch (a_Order)
	{
	case ERotationMultiplicationOrder_ZXZ:
		{
			rotation = rotateZ * rotateX * rotateZ;
			break;
		}
	case ERotationMultiplicationOrder_XYX:
		{
			rotation = rotateX * rotateY * rotateX;
			break;
		}
	case ERotationMultiplicationOrder_YZY:
		{
			rotation = rotateY * rotateZ * rotateY;
			break;
		}
	case ERotationMultiplicationOrder_ZYZ:
		{
			rotation = rotateZ * rotateY * rotateZ;
			break;
		}
	case ERotationMultiplicationOrder_XZX:
		{
			rotation = rotateX * rotateZ * rotateX;
			break;
		}
	case ERotationMultiplicationOrder_YXY:
		{
			rotation = rotateY * rotateX * rotateY;
			break;
		}
	case ERotationMultiplicationOrder_XYZ:
		{
			rotation = rotateX * rotateY * rotateZ;
			break;
		}
	case ERotationMultiplicationOrder_YZX:
		{
			rotation = rotateY * rotateZ * rotateX;
			break;
		}
	case ERotationMultiplicationOrder_ZXY:
		{
			rotation = rotateZ * rotateX * rotateY;
			break;
		}
	case ERotationMultiplicationOrder_XZY:
		{
			rotation = rotateX * rotateZ * rotateY;
			break;
		}
	case ERotationMultiplicationOrder_ZYX:
		{
			rotation = rotateZ * rotateY * rotateX;
			break;
		}
	case ERotationMultiplicationOrder_YXZ:
		{
			rotation = rotateY * rotateX * rotateZ;
			break;
		}
	case ERotationMultiplicationOrder_Invalid:
	default:
		{
			AssertMessage("Invalid rotation order encountered");
			break;
		}
	}
	return rotation;
}

Matrix4 CreateRotateX(float a_Radians)
{
	const float c = static_cast<float>(cos(a_Radians));
	const float s = static_cast<float>(sin(a_Radians));
	return Matrix4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, c, s, 0.0f,
		0.0f, -s, c, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 CreateRotateY(float a_Radians)
{
	const float c = static_cast<float>(cos(a_Radians));
	const float s = static_cast<float>(sin(a_Radians));
	return Matrix4(c, 0.0f, -s, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		s, 0.0f, c, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 CreateRotateZ(float a_Radians)
{
	const float c = static_cast<float>(cos(a_Radians));
	const float s = static_cast<float>(sin(a_Radians));
	return Matrix4(c, s, 0.0f, 0.0f, -s, c, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 FromEulerAngles(const Vector3 &a_Angles, ERotationMultiplicationOrder a_Order /* = ERotationMultiplicationOrder_XYZ */)
{
	Matrix4 matrix = CreateRotate(a_Angles.m_X, a_Angles.m_Y, a_Angles.m_Z, a_Order);
	return matrix;
}

Matrix4 FromEulerAnglesYX(float a_AngleY, float a_AngleX)
{
	const float cosX = static_cast<float>(cos(a_AngleX));
	const float sinX = static_cast<float>(sin(a_AngleX));
	const float cosY = static_cast<float>(cos(a_AngleY));
	const float sinY = static_cast<float>(sin(a_AngleY));

	return Matrix4(cosY, 0.0f, -sinY, 0.0f,
		sinY * sinX, cosX, cosY * sinX, 0.0f,
		sinY * cosX, -sinX, cosY * cosX, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4 CreateOrthoLH(float a_Left, float a_Right, float a_Bottom, float a_Top, float a_NearZ, float a_FarZ)
{
	const float deltaX = a_Right - a_Left;
	const float deltaY = a_Top - a_Bottom;
	const float deltaZ = a_FarZ - a_NearZ;
	AssertMessage(0.0f != deltaX && 0.0f != deltaY && 0.0f != deltaZ, "Invalid parameters encountered!");

	Matrix4 ortho;
	ortho.m[0][0] = 2.0f / deltaX;
	ortho.m[3][0] = -(a_Right + a_Left) / deltaX;
	ortho.m[1][1] = 2.0f / deltaY;
	ortho.m[3][1] = -(a_Top + a_Bottom) / deltaY;
	ortho.m[2][2] = -2.0f / deltaZ;
	ortho.m[3][2] = -(a_NearZ + a_FarZ) / deltaZ;
	return ortho;
}

Matrix4 CreateOrthoRH(float a_Left, float a_Right, float a_Bottom, float a_Top, float a_NearZ, float a_FarZ)
{
	const float deltaX = a_Right - a_Left;
	const float deltaY = a_Top - a_Bottom;
	const float deltaZ = a_FarZ - a_NearZ;
	AssertMessage(0.0f != deltaX && 0.0f != deltaY && 0.0f != deltaZ, "Invalid parameters encountered!");

	Matrix4 ortho;
	ortho.m[0][0] = 2.0f / deltaX;
	ortho.m[3][0] = -(a_Right + a_Left) / deltaX;
	ortho.m[1][1] = 2.0f / deltaY;
	ortho.m[3][1] = -(a_Top + a_Bottom) / deltaY;
	ortho.m[2][2] = -2.0f / deltaZ;
	ortho.m[3][2] = -(a_NearZ + a_FarZ) / deltaZ;
	return ortho;
}

Matrix4 CreateFrustum(float a_Left, float a_Right, float a_Bottom, float a_Top, float a_NearZ, float a_FarZ)
{
	const float deltaX = a_Right - a_Left;
	const float deltaY = a_Top - a_Bottom;
	const float deltaZ = a_FarZ - a_NearZ;
	AssertMessage(0.0f != deltaX && 0.0f != deltaY && 0.0f != deltaZ, "Invalid parameters encountered!");

	Matrix4 frustum;
	frustum.m[0][0] = 2.0f * a_NearZ / deltaX;
	frustum.m[0][1] = frustum.m[0][2] = frustum.m[0][3] = 0.0f;

	frustum.m[1][1] = 2.0f * a_NearZ / deltaY;
	frustum.m[1][0] = frustum.m[1][2] = frustum.m[1][3] = 0.0f;

	frustum.m[2][0] = (a_Right + a_Left) / deltaX;
	frustum.m[2][1] = (a_Top + a_Bottom) / deltaY;
	frustum.m[2][2] = -(a_NearZ + a_FarZ) / deltaZ;
	frustum.m[2][3] = -1.0f;

	frustum.m[3][2] = -2.0f * a_NearZ * a_FarZ/ deltaZ;
	frustum.m[3][0] = frustum.m[3][1] = frustum.m[3][3] = 0.0f;

	return frustum;
}

Matrix4 CreatePerspectiveLH(float a_FOVy, float a_Aspect, float a_NearZ, float a_FarZ)
{
	const float cotan = 1.0f / tanf(a_FOVy / 2.0f);
	return Matrix4(cotan / a_Aspect, 0.0f, 0.0f, 0.0f,
		0.0f, cotan, 0.0f, 0.0f,
		0.0f, 0.0f, -(a_FarZ + a_NearZ) / (a_NearZ - a_FarZ), 1.0f,
		0.0f, 0.0f, (2.0f * a_FarZ * a_NearZ) / (a_NearZ - a_FarZ), 0.0f);
}

Matrix4 CreatePerspectiveRH(float a_FOVy, float a_Aspect, float a_NearZ, float a_FarZ)
{
	const float cotan = 1.0f / tanf(a_FOVy / 2.0f);
	return Matrix4(cotan / a_Aspect, 0.0f, 0.0f, 0.0f,
		0.0f, cotan, 0.0f, 0.0f,
		0.0f, 0.0f, (a_FarZ + a_NearZ) / (a_NearZ - a_FarZ), -1.0f,
		0.0f, 0.0f, (2.0f * a_FarZ * a_NearZ) / (a_NearZ - a_FarZ), 0.0f);
}

Matrix4 CreateLookAtLH(const Vector3 &a_Eye, const Vector3 &a_Center, const Vector3 &a_Up)
{
	Vector3 n = a_Center - a_Eye;
	n.Normalize();
	Vector3 u = Cross(a_Up, n);
	u.Normalize();
	Vector3 v = Cross(n, u);
	v.Normalize();

	return Matrix4(u.m_F[0], v.m_F[0], n.m_F[0], 0.0f,
		u.m_F[1], v.m_F[1], n.m_F[1], 0.0f,
		u.m_F[2], v.m_F[2], n.m_F[2], 0.0f,
		Dot((u * -1), a_Eye),
		Dot((v * -1), a_Eye),
		Dot((n * -1), a_Eye),
		1.0f);
}

Matrix4 CreateLookAtRH(const Vector3 &a_Eye, const Vector3 &a_Center, const Vector3 &a_Up)
{
	Vector3 n = a_Eye - a_Center;
	n.Normalize();
	Vector3 u = Cross(a_Up, n);
	u.Normalize();
	Vector3 v = Cross(n, u);

	return Matrix4(u.m_F[0], v.m_F[0], n.m_F[0], 0.0f,
		u.m_F[1], v.m_F[1], n.m_F[1], 0.0f,
		u.m_F[2], v.m_F[2], n.m_F[2], 0.0f,
		Dot((u * -1), a_Eye),
		Dot((v * -1), a_Eye),
		Dot((n * -1), a_Eye),
		1.0f);
}

Vector3 Transform(const Matrix4 &a_Transform, const Vector3 &a_Direction)
{
	return Vector3(a_Direction.m_X * a_Transform.m[0][0] +
		a_Direction.m_Y * a_Transform.m[1][0] +
		a_Direction.m_Z * a_Transform.m[2][0],

		a_Direction.m_X * a_Transform.m[0][1] +
		a_Direction.m_Y * a_Transform.m[1][1] +
		a_Direction.m_Z * a_Transform.m[2][1],

		a_Direction.m_X * a_Transform.m[0][2] +
		a_Direction.m_Y * a_Transform.m[1][2] +
		a_Direction.m_Z * a_Transform.m[2][2]);
}

void ExtractYawPitchRollDegrees(const Matrix4 &a_Matrix, float &a_Yaw, float &a_Pitch, float &a_Roll)
{
	ExtractYawPitchRoll(a_Matrix, a_Yaw, a_Pitch, a_Roll);
	a_Yaw = RadToDeg(a_Yaw);
	a_Pitch = RadToDeg(a_Pitch);
	a_Roll = RadToDeg(a_Roll);
}

void ExtractYawPitchRoll(const Matrix4 &a_Matrix, float &a_Yaw, float &a_Pitch, float &a_Roll)
{
#if defined(PROTO_GLM_ENABLED)
	a_Roll = std::atan2(a_Matrix.m[1][2], a_Matrix.m[2][2]);

	const float cosYangle = glm::sqrt(glm::pow(a_Matrix.m[0][0], 2) + glm::pow(a_Matrix.m[0][1], 2));
	a_Yaw = std::atan2(-a_Matrix.m[0][2], cosYangle);

	const float sinXangle = glm::sin(a_Roll);
	const float cosXangle = glm::cos(a_Roll);
	a_Pitch = std::atan2(sinXangle * a_Matrix.m[2][0] - cosXangle * a_Matrix.m[1][0],
		cosXangle * a_Matrix.m[1][1] - sinXangle * a_Matrix.m[2][1]);
#else
	UNUSED(a_Roll);
	UNUSED(a_Pitch);
	UNUSED(a_Yaw);
	UNUSED(a_Matrix);

	AssertMessage("Not implemented!");
#endif
}

void ExtractEulerAngles(const Matrix4 &a_Matrix, float &a_X, float &a_Y, float &a_Z)
{
	ExtractYawPitchRoll(a_Matrix, a_Z, a_Y, a_X);
}

void ExtractEulerAnglesDegrees(const Matrix4 &a_Matrix, float &a_X, float &a_Y, float &a_Z)
{
	ExtractYawPitchRollDegrees(a_Matrix, a_Z, a_Y, a_X);
}

END_NAMESPACE(Math)
