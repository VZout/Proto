#include "Vector4.h"

#include "Platform/Debug/AssertMessage.h"
#include "Vector3.h"

#include <math.h>

USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Math)

const Vector4 Vector4::ORIGIN(0.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::X_AXIS(1.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::NEG_X_AXIS(-1.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::Y_AXIS(0.0f, 1.0f, 0.0f, 0.0f);
const Vector4 Vector4::NEG_Y_AXIS(0.0f, -1.0f, 0.0f, 0.0f);
const Vector4 Vector4::Z_AXIS(0.0f, 0.0f, 1.0f, 0.0f);
const Vector4 Vector4::NEG_Z_AXIS(0.0f, 0.0f, -1.0f, 0.0f);

Vector4::Vector4()
	: m_X(0.0f)
	, m_Y(0.0f)
	, m_Z(0.0f)
	, m_W(0.0f)
{
}

Vector4::Vector4(float a_X, float a_Y, float a_Z, float a_W)
	: m_X(a_X)
	, m_Y(a_Y)
	, m_Z(a_Z)
	, m_W(a_W)
{
}

Vector4::Vector4(const Vector4 &a_Rhs)
	: m_X(a_Rhs.m_X)
	, m_Y(a_Rhs.m_Y)
	, m_Z(a_Rhs.m_Z)
	, m_W(a_Rhs.m_W)
{
}

Vector4::Vector4(const Vector3 &a_Rhs, float a_W)
	: m_X(a_Rhs.m_X)
	, m_Y(a_Rhs.m_Y)
	, m_Z(a_Rhs.m_Z)
	, m_W(a_W)
{
}

Vector4::~Vector4()
{
}

void Vector4::Clear()
{
	m_X = m_Y = m_Z = 0.0f;
}

void Vector4::Normalize()
{
	const float length = Length(*this);
	if (0.0f != length)
	{
		*this *= (1.0f / length);
	}
}

Vector4& Vector4::operator=(Vector4 a_Rhs)
{
	swap(*this, a_Rhs);
	return *this;
}

Vector4& Vector4::operator+=(const Vector4 &a_Rhs)
{
	m_X += a_Rhs.m_X;
	m_Y += a_Rhs.m_Y;
	m_Z += a_Rhs.m_Z;
	return *this;
}

Vector4& Vector4::operator-=(const Vector4 &a_Rhs)
{
	m_X -= a_Rhs.m_X;
	m_Y -= a_Rhs.m_Y;
	m_Z -= a_Rhs.m_Z;
	return *this;
}

Vector4& Vector4::operator*=(float a_Rhs)
{
	m_X *= a_Rhs;
	m_Y *= a_Rhs;
	m_Z *= a_Rhs;
	return *this;
}

Vector4& Vector4::operator/=(float a_Rhs)
{
	m_X /= a_Rhs;
	m_Y /= a_Rhs;
	m_Z /= a_Rhs;
	return *this;
}

Vector4 operator+(Vector4 a_Lhs, const Vector4 &a_Rhs)
{
	a_Lhs += a_Rhs;
	return a_Lhs;
}

Vector4 operator-(Vector4 a_Lhs, const Vector4 &a_Rhs)
{
	a_Lhs -= a_Rhs;
	return a_Lhs;
}

Vector4 operator*(Vector4 a_Lhs, float a_Rhs)
{
	a_Lhs *= a_Rhs;
	return a_Lhs;
}

Vector4 operator*(float a_Lhs, Vector4 a_Rhs)
{
	a_Rhs *= a_Lhs;
	return a_Rhs;
}

float operator*(const Vector4 &a_Lhs, const Vector4 &a_Rhs)
{
	return Dot(a_Lhs, a_Rhs);
}

Vector4 operator/(Vector4 a_Lhs, float a_Rhs)
{
	a_Lhs /= a_Rhs;
	return a_Lhs;
}

Vector4 operator-(Vector4 a_Lhs)
{
	a_Lhs *= -1;
	return a_Lhs;
}

bool operator==(const Vector4 &a_Lhs, const Vector4 &a_Rhs)
{
	return a_Lhs.m_X == a_Rhs.m_X && a_Lhs.m_Y == a_Rhs.m_Y && a_Lhs.m_Z == a_Rhs.m_Z;
}

bool operator!=(const Vector4 &a_Lhs, const Vector4 &a_Rhs)
{
	return !(a_Lhs == a_Rhs);
}

bool operator< (const Vector4 &a_Lhs, const Vector4 &a_Rhs)
{
	return a_Lhs.m_X < a_Rhs.m_X || a_Lhs.m_Y < a_Rhs.m_Y || a_Lhs.m_Z < a_Rhs.m_Z;
}

bool operator> (const Vector4 &a_Lhs, const Vector4 &a_Rhs)
{
	return (a_Rhs < a_Lhs);
}

bool operator<=(const Vector4 &a_Lhs, const Vector4 &a_Rhs)
{
	return !(a_Lhs > a_Rhs);
}

bool operator>=(const Vector4 &a_Lhs, const Vector4 &a_Rhs)
{
	return !(a_Lhs < a_Rhs);
}

float Dot(const Vector4 &a_Lhs, const Vector4 &a_Rhs)
{
	return a_Lhs.m_X * a_Rhs.m_X + a_Lhs.m_Y * a_Rhs.m_Y + a_Lhs.m_Z * a_Rhs.m_Z;
}

// Vector4 Cross(const Vector4 &a_Lhs, const Vector4 &a_Rhs)
// {
// 	return Vector4(a_Lhs.m_Y * a_Rhs.m_Z - a_Lhs.m_Z * a_Rhs.m_Y,
// 		a_Lhs.m_Z * a_Rhs.m_X - a_Lhs.m_X * a_Rhs.m_Z,
// 		a_Lhs.m_X * a_Rhs.m_Y - a_Lhs.m_Y * a_Rhs.m_X);
// }

float Length(const Vector4 &a_Value)
{
	return sqrtf(LengthSquared(a_Value));
}

float LengthSquared(const Vector4 &a_Value)
{
	return Dot(a_Value, a_Value);
}

Vector4 Normalize(const Vector4 &a_Value)
{
	const float length = Length(a_Value);
	if (0.0f != length)
	{
		return a_Value * 1.0f / length;
	}
	return a_Value;
}

Vector4 Slerp(float a_Factor, const Vector4 &a_From, const Vector4 &a_To)
{
	float cosAlpha = Dot(a_From, a_To);
	float alpha = acosf(cosAlpha);
	float sinAlpha = sinf(alpha);

	Vector4 result;
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

END_NAMESPACE(Math)
