#include "Vector3.h"

#include "Math/Helpers/GLMIncludes.h"
#include "Platform/Debug/AssertMessage.h"
#include "Quaternion.h"

#include <math.h>

USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Math)

const Vector3 Vector3::ORIGIN(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::X_AXIS(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::NEG_X_AXIS(-1.0f, 0.0f, 0.0f);
const Vector3 Vector3::Y_AXIS(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::NEG_Y_AXIS(0.0f, -1.0f, 0.0f);
const Vector3 Vector3::Z_AXIS(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::NEG_Z_AXIS(0.0f, 0.0f, -1.0f);

Vector3::Vector3()
	: m_X(0.0f)
	, m_Y(0.0f)
	, m_Z(0.0f)
{
}

Vector3::Vector3(float a_X, float a_Y, float a_Z)
	: m_X(a_X)
	, m_Y(a_Y)
	, m_Z(a_Z)
{
}

Vector3::Vector3(const Vector3 &a_Rhs)
	: m_X(a_Rhs.m_X)
	, m_Y(a_Rhs.m_Y)
	, m_Z(a_Rhs.m_Z)
{
}

Vector3::~Vector3()
{
}

void Vector3::Clear()
{
	m_X = m_Y = m_Z = 0.0f;
}

void Vector3::Normalize()
{
	const float length = Length(*this);
	if (0.0f != length)
	{
		*this *= (1.0f / length);
	}
}

Vector3& Vector3::operator=(Vector3 a_Rhs)
{
	swap(*this, a_Rhs);
	return *this;
}

Vector3& Vector3::operator+=(const Vector3 &a_Rhs)
{
	m_X += a_Rhs.m_X;
	m_Y += a_Rhs.m_Y;
	m_Z += a_Rhs.m_Z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3 &a_Rhs)
{
	m_X -= a_Rhs.m_X;
	m_Y -= a_Rhs.m_Y;
	m_Z -= a_Rhs.m_Z;
	return *this;
}

Vector3& Vector3::operator*=(float a_Rhs)
{
	m_X *= a_Rhs;
	m_Y *= a_Rhs;
	m_Z *= a_Rhs;
	return *this;
}

Vector3& Vector3::operator/=(float a_Rhs)
{
	m_X /= a_Rhs;
	m_Y /= a_Rhs;
	m_Z /= a_Rhs;
	return *this;
}

Vector3 operator+(Vector3 a_Lhs, const Vector3 &a_Rhs)
{
	a_Lhs += a_Rhs;
	return a_Lhs;
}

Vector3 operator-(Vector3 a_Lhs, const Vector3 &a_Rhs)
{
	a_Lhs -= a_Rhs;
	return a_Lhs;
}

Vector3 operator*(Vector3 a_Lhs, float a_Rhs)
{
	a_Lhs *= a_Rhs;
	return a_Lhs;
}

Vector3 operator*(float a_Lhs, Vector3 a_Rhs)
{
	a_Rhs *= a_Lhs;
	return a_Rhs;
}

float operator*(const Vector3 &a_Lhs, const Vector3 &a_Rhs)
{
	return Dot(a_Lhs, a_Rhs);
}

Vector3 operator/(Vector3 a_Lhs, float a_Rhs)
{
	a_Lhs /= a_Rhs;
	return a_Lhs;
}

Vector3 operator-(Vector3 a_Lhs)
{
	a_Lhs *= -1;
	return a_Lhs;
}

bool operator==(const Vector3 &a_Lhs, const Vector3 &a_Rhs)
{
	return a_Lhs.m_X == a_Rhs.m_X && a_Lhs.m_Y == a_Rhs.m_Y && a_Lhs.m_Z == a_Rhs.m_Z;
}

bool operator!=(const Vector3 &a_Lhs, const Vector3 &a_Rhs)
{
	return !(a_Lhs == a_Rhs);
}

bool operator< (const Vector3 &a_Lhs, const Vector3 &a_Rhs)
{
	return a_Lhs.m_X < a_Rhs.m_X || a_Lhs.m_Y < a_Rhs.m_Y || a_Lhs.m_Z < a_Rhs.m_Z;
}

bool operator> (const Vector3 &a_Lhs, const Vector3 &a_Rhs)
{
	return (a_Rhs < a_Lhs);
}

bool operator<=(const Vector3 &a_Lhs, const Vector3 &a_Rhs)
{
	return !(a_Lhs > a_Rhs);
}

bool operator>=(const Vector3 &a_Lhs, const Vector3 &a_Rhs)
{
	return !(a_Lhs < a_Rhs);
}

float Dot(const Vector3 &a_Lhs, const Vector3 &a_Rhs)
{
	return a_Lhs.m_X * a_Rhs.m_X + a_Lhs.m_Y * a_Rhs.m_Y + a_Lhs.m_Z * a_Rhs.m_Z;
}

Vector3 Cross(const Vector3 &a_Lhs, const Vector3 &a_Rhs)
{
	return Vector3(a_Lhs.m_Y * a_Rhs.m_Z - a_Lhs.m_Z * a_Rhs.m_Y,
		a_Lhs.m_Z * a_Rhs.m_X - a_Lhs.m_X * a_Rhs.m_Z,
		a_Lhs.m_X * a_Rhs.m_Y - a_Lhs.m_Y * a_Rhs.m_X);
}

float Length(const Vector3 &a_Value)
{
	return sqrtf(LengthSquared(a_Value));
}

float LengthSquared(const Vector3 &a_Value)
{
	return Dot(a_Value, a_Value);
}

Vector3 Negate(const Vector3 &a_Vector)
{
	return Vector3(-1.0f * a_Vector);
}

Vector3 Normalize(const Vector3 &a_Value)
{
	const float length = Length(a_Value);
	if (0.0f != length)
	{
		return a_Value * 1.0f / length;
	}
	return a_Value;
}

Vector3 Rotate(const Vector3 &a_Vector, const Quaternion &a_Rotation)
{
#if defined(PROTO_GLM_ENABLED)
	glm::quat rotation(a_Rotation.m_W, a_Rotation.m_X, a_Rotation.m_Y, a_Rotation.m_Z);
	glm::vec3 vector(a_Vector.m_X, a_Vector.m_Y, a_Vector.m_Z);
	glm::vec3 rotated = glm::rotate(rotation, vector);
	return Vector3(rotated.x, rotated.y, rotated.z);
#else
	UNUSED(a_Rotation);
	UNUSED(a_Vector);
	AssertMessage("Not implemented!");
	return Vector3();
#endif
}

Vector3 Slerp(float a_Factor, const Vector3 &a_From, const Vector3 &a_To)
{
	float cosAlpha = Dot(a_From, a_To);
	float alpha = acosf(cosAlpha);
	float sinAlpha = sinf(alpha);

	Vector3 result;
	if (sinAlpha == 0)
	{
		result = a_From + (a_To - a_From) * a_Factor;
	}
	else
	{
		const float t1 = sinf((1.0f - a_Factor) * alpha) / sinAlpha;
		const float t2 = sinf(a_Factor * alpha) / sinAlpha;
		result = a_From * t1 + a_To * t2;
	}

	return result;
}

bool AnyNonZero(const Vector3 &a_Vector)
{
	return a_Vector.m_X != 0.0f ||
		a_Vector.m_Y != 0.0f ||
		a_Vector.m_Z != 0.0f;
}

END_NAMESPACE(Math)
