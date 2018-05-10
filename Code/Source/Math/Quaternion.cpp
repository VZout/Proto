#include "Quaternion.h"

#include "Helpers/GLMIncludes.h"
#include "Matrix4.h"
#include "Platform/Debug/AssertMessage.h"
#include "Trigonometry.h"

#include <math.h>

USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Math)

Quaternion::Quaternion()
	: m_X(0.0f)
	, m_Y(0.0f)
	, m_Z(0.0f)
	, m_W(1.0f)
{
}

Quaternion::Quaternion(float a_X, float a_Y, float a_Z, float a_W)
	: m_X(a_X)
	, m_Y(a_Y)
	, m_Z(a_Z)
	, m_W(a_W)
{
}

Quaternion::Quaternion(const Quaternion &a_Lhs)
	: m_X(a_Lhs.m_X)
	, m_Y(a_Lhs.m_Y)
	, m_Z(a_Lhs.m_Z)
	, m_W(a_Lhs.m_W)
{
}

Quaternion::Quaternion(const Math::Matrix4 &a_Matrix)
{
		float fourWSquaredMinus1 = a_Matrix.m[0][0] + a_Matrix.m[1][1] + a_Matrix.m[2][2];
		float fourXSquaredMinus1 = a_Matrix.m[0][0] - a_Matrix.m[1][1] - a_Matrix.m[2][2];
		float fourYSquaredMinus1 = a_Matrix.m[1][1] - a_Matrix.m[0][0] - a_Matrix.m[2][2];
		float fourZSquaredMinus1 = a_Matrix.m[2][2] - a_Matrix.m[0][0] - a_Matrix.m[1][1];

		int biggestIndex = 0;
		float fourBiggestSquaredMinus1 = fourWSquaredMinus1;
		if (fourXSquaredMinus1 > fourBiggestSquaredMinus1) 
		{
			fourBiggestSquaredMinus1 = fourXSquaredMinus1;
			biggestIndex = 1;
		}
		if (fourYSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourYSquaredMinus1;
			biggestIndex = 2;
		}
		if (fourZSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourZSquaredMinus1;
			biggestIndex = 3;
		}

		const float biggestVal = sqrtf(fourBiggestSquaredMinus1 + 1.0f) * 0.5f;
		const float mult = 0.25f / biggestVal;

		switch (biggestIndex)
		{
		case 0:
			{
				m_W = biggestVal;
				m_X = (a_Matrix.m[1][2] - a_Matrix.m[2][1]) * mult;
				m_Y = (a_Matrix.m[2][0] - a_Matrix.m[0][2]) * mult;
				m_Z = (a_Matrix.m[0][1] - a_Matrix.m[1][0]) * mult;
				break;
			}
		case 1:
			{
				m_X = biggestVal;
				m_W = (a_Matrix.m[1][2] - a_Matrix.m[2][1]) * mult;
				m_Y = (a_Matrix.m[0][1] + a_Matrix.m[1][0]) * mult;
				m_Z = (a_Matrix.m[2][0] + a_Matrix.m[0][2]) * mult;
				break;
			}
		case 2:
			{
				m_Y = biggestVal;
				m_W = (a_Matrix.m[2][0] - a_Matrix.m[0][2]) * mult;
				m_X = (a_Matrix.m[0][1] + a_Matrix.m[1][0]) * mult;
				m_Z = (a_Matrix.m[1][2] + a_Matrix.m[2][1]) * mult;
				break;
			}
		case 3:
			{
				m_Z = biggestVal;
				m_W = (a_Matrix.m[0][1] - a_Matrix.m[1][0]) * mult;
				m_X = (a_Matrix.m[2][0] + a_Matrix.m[0][2]) * mult;
				m_Y = (a_Matrix.m[1][2] + a_Matrix.m[2][1]) * mult;
				break;
			}
		}
}

Quaternion::~Quaternion()
{
}

Quaternion& Quaternion::operator*=(const Quaternion &a_Rhs)
{
	float x = m_X * a_Rhs.m_W + m_Y * a_Rhs.m_Z - m_Z * a_Rhs.m_Y + m_W * a_Rhs.m_X;
	float y = -m_X * a_Rhs.m_Z + m_Y * a_Rhs.m_W + m_Z * a_Rhs.m_X + m_W * a_Rhs.m_Y;
	float z = m_X * a_Rhs.m_Y - m_Y * a_Rhs.m_X + m_Z * a_Rhs.m_W + m_W * a_Rhs.m_Z;
	float w = -m_X * a_Rhs.m_X - m_Y * a_Rhs.m_Y - m_Z * a_Rhs.m_Z + m_W * a_Rhs.m_W;
	m_X = x;
	m_Y = y;
	m_Z = z;
	m_W = w;
	return *this;
}

Quaternion& Quaternion::operator*=(float a_Rhs)
{
	m_X *= a_Rhs;
	m_Y *= a_Rhs;
	m_Z *= a_Rhs;
	m_W *= a_Rhs;
	return *this;
}

Quaternion Concatenate(const Quaternion &a_Rhs, const Quaternion &a_Lhs)
{
	return Quaternion(a_Rhs * a_Lhs);
}

void Quaternion::Normalize()
{
	const float length = Length(*this);
	if (0.0f != length)
	{
		*this *= (1.0f / length);
	}
}

Quaternion operator*(Quaternion a_Lhs, const Quaternion &a_Rhs)
{
	a_Lhs *= a_Rhs;
	return a_Lhs;
}

Quaternion operator*(Quaternion a_Lhs, float a_Rhs)
{
	a_Lhs *= a_Rhs;
	return a_Lhs;
}

Vector3 operator*(Quaternion a_Lhs, const Vector3 &a_Rhs)
{
	const Vector3 u(a_Lhs.m_X, a_Lhs.m_Y, a_Lhs.m_Z);
	const float s = a_Lhs.m_W;

	return 2.0f * Dot(u, a_Rhs) * u
		+ (s * s - Dot(u, u)) * a_Rhs
		+ 2.0f * s * Cross(u, a_Rhs);
}

Quaternion Normalize(const Quaternion &a_Value)
{
	const float length = Length(a_Value);
	if (0.0f != length)
	{
		return a_Value * (1.0f / length);
	}
	return a_Value;
}

float Length(const Quaternion &a_Value)
{
	const float length = sqrtf(a_Value.m_X * a_Value.m_X + a_Value.m_Y * a_Value.m_Y + a_Value.m_Z * a_Value.m_Z + a_Value.m_W * a_Value.m_W);
	return length;
}

Matrix4 ToMatrix(const Quaternion &a_Quaternion)
{
	Quaternion n = Normalize(a_Quaternion);

	Matrix4 result;
	const float qxx(a_Quaternion.m_X * a_Quaternion.m_X);
	const float qyy(a_Quaternion.m_Y * a_Quaternion.m_Y);
	const float qzz(a_Quaternion.m_Z * a_Quaternion.m_Z);
	const float qxz(a_Quaternion.m_X * a_Quaternion.m_Z);
	const float qxy(a_Quaternion.m_X * a_Quaternion.m_Y);
	const float qyz(a_Quaternion.m_Y * a_Quaternion.m_Z);
	const float qwx(a_Quaternion.m_W * a_Quaternion.m_X);
	const float qwy(a_Quaternion.m_W * a_Quaternion.m_Y);
	const float qwz(a_Quaternion.m_W * a_Quaternion.m_Z);

	result.m[0][0] = 1 - 2 * (qyy + qzz);
	result.m[0][1] = 2 * (qxy + qwz);
	result.m[0][2] = 2 * (qxz - qwy);

	result.m[1][0] = 2 * (qxy - qwz);
	result.m[1][1] = 1 - 2 * (qxx + qzz);
	result.m[1][2] = 2 * (qyz + qwx);
	
	result.m[2][0] = 2 * (qxz + qwy);
	result.m[2][1] = 2 * (qyz - qwx);
	result.m[2][2] = 1 - 2 * (qxx + qyy);

	return result;
}

Quaternion ToQuaternion(const Matrix4 &a_Matrix)
{
#if defined(PROTO_GLM_ENABLED)
	glm::mat4 mat;
	mat[0][0] = a_Matrix.f[0];
	mat[0][1] = a_Matrix.f[1];
	mat[0][2] = a_Matrix.f[2];
	mat[0][3] = a_Matrix.f[3];

	mat[1][0] = a_Matrix.f[4];
	mat[1][1] = a_Matrix.f[5];
	mat[1][2] = a_Matrix.f[6];
	mat[1][3] = a_Matrix.f[7];

	mat[2][0] = a_Matrix.f[8];
	mat[2][1] = a_Matrix.f[9];
	mat[2][2] = a_Matrix.f[10];
	mat[2][3] = a_Matrix.f[11];

	mat[3][0] = a_Matrix.f[12];
	mat[3][1] = a_Matrix.f[13];
	mat[3][2] = a_Matrix.f[14];
	mat[3][3] = a_Matrix.f[15];

	glm::quat rotation = glm::quat_cast(mat);
	return Quaternion(rotation.x, rotation.y, rotation.z, rotation.x);
#else
	UNUSED(a_Matrix);
	AssertMessage("Not implemented!");
	return Quaternion();
#endif
}

Quaternion FromAngleAxis(float a_Radians, const Vector3 &a_Axis)
{
	const float s = Sin(a_Radians / 2.0f);
	return Quaternion(a_Axis.m_X * s, a_Axis.m_Y * s, a_Axis.m_Z * s, Cos(a_Radians / 2.0f));
}

END_NAMESPACE(Math)
