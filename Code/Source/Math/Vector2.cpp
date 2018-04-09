#include "Vector2.h"

#include "Platform/Debug/AssertMessage.h"

#include <math.h>

USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Math)

const Vector2 Vector2::ORIGIN(0.0f, 0.0f);
const Vector2 Vector2::X_AXIS(1.0f, 0.0f);
const Vector2 Vector2::Y_AXIS(0.0f, 1.0f);

Vector2::Vector2()
	: m_X(0.0f)
	, m_Y(0.0f)
{
}

Vector2::Vector2(float a_X, float a_Y)
	: m_X(a_X)
	, m_Y(a_Y)
{
}

Vector2::Vector2(const Vector2 &a_Rhs)
	: m_X(a_Rhs.m_X)
	, m_Y(a_Rhs.m_Y)
{
}

Vector2::~Vector2()
{
}

void Vector2::Clear()
{
	m_X = m_Y = 0.0f;
}

void Vector2::Normalize()
{
	const float length = Length(*this);
	if (0.0f != length)
	{
		*this *= (1.0f / length);
	}
}

Vector2& Vector2::operator=(Vector2 a_Rhs)
{
	swap(*this, a_Rhs);
	return *this;
}

Vector2& Vector2::operator+=(const Vector2 &a_Rhs)
{
	m_X += a_Rhs.m_X;
	m_Y += a_Rhs.m_Y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2 &a_Rhs)
{
	m_X -= a_Rhs.m_X;
	m_Y -= a_Rhs.m_Y;
	return *this;
}

Vector2& Vector2::operator*=(float a_Rhs)
{
	m_X *= a_Rhs;
	m_Y *= a_Rhs;
	return *this;
}

Vector2& Vector2::operator/=(float a_Rhs)
{
	m_X /= a_Rhs;
	m_Y /= a_Rhs;
	return *this;
}

Vector2 operator+(Vector2 a_Lhs, const Vector2 &a_Rhs)
{
	a_Lhs += a_Rhs;
	return a_Lhs;
}

Vector2 operator-(Vector2 a_Lhs, const Vector2 &a_Rhs)
{
	a_Lhs -= a_Rhs;
	return a_Lhs;
}

Vector2 operator*(Vector2 a_Lhs, float a_Rhs)
{
	a_Lhs *= a_Rhs;
	return a_Lhs;
}

Vector2 operator*(float a_Lhs, Vector2 a_Rhs)
{
	a_Rhs *= a_Lhs;
	return a_Rhs;
}

float operator*(const Vector2 &a_Lhs, const Vector2 &a_Rhs)
{
	return Dot(a_Lhs, a_Rhs);
}

Vector2 operator/(Vector2 a_Lhs, float a_Rhs)
{
	a_Lhs /= a_Rhs;
	return a_Lhs;
}

Vector2 operator-(Vector2 a_Lhs)
{
	a_Lhs *= -1;
	return a_Lhs;
}

bool operator==(const Vector2 &a_Lhs, const Vector2 &a_Rhs)
{
	return a_Lhs.m_X == a_Rhs.m_X && a_Lhs.m_Y == a_Rhs.m_Y;
}

bool operator!=(const Vector2 &a_Lhs, const Vector2 &a_Rhs)
{
	return !(a_Lhs == a_Rhs);
}

bool operator< (const Vector2 &a_Lhs, const Vector2 &a_Rhs)
{
	return a_Lhs.m_X < a_Rhs.m_X || a_Lhs.m_Y < a_Rhs.m_Y;
}

bool operator> (const Vector2 &a_Lhs, const Vector2 &a_Rhs)
{
	return (a_Rhs < a_Lhs);
}

bool operator<=(const Vector2 &a_Lhs, const Vector2 &a_Rhs)
{
	return !(a_Lhs > a_Rhs);
}

bool operator>=(const Vector2 &a_Lhs, const Vector2 &a_Rhs)
{
	return !(a_Lhs < a_Rhs);
}

float Dot(const Vector2 &a_Lhs, const Vector2 &a_Rhs)
{
	return a_Lhs.m_X * a_Rhs.m_X + a_Lhs.m_Y * a_Rhs.m_Y;
}

float Length(const Vector2 &a_Value)
{
	return static_cast<float>(sqrtf(LengthSquared(a_Value)));
}

float LengthSquared(const Vector2 &a_Value)
{
	return Dot(a_Value, a_Value);
}

Vector2 Normalize(const Vector2 &a_Value)
{
	const float length = Length(a_Value);
	if (0.0f != length)
	{
		return a_Value * 1.0f / length;
	}
	return a_Value;
}

END_NAMESPACE(Math)
