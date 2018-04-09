#pragma once

#include "Proto.h"

#include <utility>

BEGIN_NAMESPACE(Math)

class Vector2
{
public:
	static const Vector2 ORIGIN;
	static const Vector2 X_AXIS;
	static const Vector2 Y_AXIS;

public:
	Vector2();
	Vector2(float a_X, float a_Y);
	Vector2(const Vector2 &a_Rhs);
	~Vector2();

	void Clear();
	void Normalize();

	Vector2& operator=(Vector2 a_Rhs);
	Vector2& operator+=(const Vector2 &a_Rhs);
	Vector2& operator-=(const Vector2 &a_Rhs);
	Vector2& operator*=(float a_Rhs);
	Vector2& operator/=(float a_Rhs);

#pragma warning( push )
#pragma warning( disable : 4201 )
	union
	{
		float m_F[2];
		struct
		{
			float m_X;
			float m_Y;
		};
	};
#pragma warning(pop)

	friend void swap(Vector2 &a_Lhs, Vector2 &a_Rhs)
	{
		using std::swap;
		swap(a_Lhs.m_X, a_Rhs.m_X);
		swap(a_Lhs.m_Y, a_Rhs.m_Y);
	}
};

Vector2 operator+(Vector2 a_Lhs, const Vector2 &a_Rhs);
Vector2 operator-(Vector2 a_Lhs, const Vector2 &a_Rhs);
Vector2 operator*(Vector2 a_Lhs, float a_Rhs);
Vector2 operator*(float a_Lhs, Vector2 a_Rhs);
float operator*(const Vector2 &a_Lhs, const Vector2 &a_Rhs);
Vector2 operator/(Vector2 a_Lhs, float a_Rhs);
Vector2 operator-(Vector2 a_Lhs);

bool operator==(const Vector2 &a_Lhs, const Vector2 &a_Rhs);
bool operator!=(const Vector2 &a_Lhs, const Vector2 &a_Rhs);
bool operator< (const Vector2 &a_Lhs, const Vector2 &a_Rhs);
bool operator> (const Vector2 &a_Lhs, const Vector2 &a_Rhs);
bool operator<=(const Vector2 &a_Lhs, const Vector2 &a_Rhs);
bool operator>=(const Vector2 &a_Lhs, const Vector2 &a_Rhs);

float Dot(const Vector2 &a_Lhs, const Vector2 &a_Rhs);
float Length(const Vector2 &a_Value);
float LengthSquared(const Vector2 &a_Value);
Vector2 Normalize(const Vector2 &a_Value);

END_NAMESPACE(Math)
