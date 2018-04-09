#pragma once

#include "Proto.h"

#include <utility>

BEGIN_NAMESPACE(Math)

class Vector3;

class Vector4
{
public:
	static const Vector4 ORIGIN;
	static const Vector4 X_AXIS;
	static const Vector4 NEG_X_AXIS;
	static const Vector4 Y_AXIS;
	static const Vector4 NEG_Y_AXIS;
	static const Vector4 Z_AXIS;
	static const Vector4 NEG_Z_AXIS;

public:
	Vector4();
	Vector4(float a_X, float a_Y, float a_Z, float a_W);
	Vector4(const Vector4 &a_Rhs);
	Vector4(const Vector3 &a_Rhs, float a_W);
	~Vector4();

	void Clear();
	void Normalize();

	Vector4& operator=(Vector4 a_Rhs);
	Vector4& operator+=(const Vector4 &a_Rhs);
	Vector4& operator-=(const Vector4 &a_Rhs);
	Vector4& operator*=(float a_Rhs);
	Vector4& operator/=(float a_Rhs);

#pragma warning( push )
#pragma warning( disable : 4201 )
	union
	{
		float m_F[4];
		struct
		{
			float m_X;
			float m_Y;
			float m_Z;
			float m_W;
		};
	};
#pragma warning(pop)

	friend void swap(Vector4 &a_Lhs, Vector4 &a_Rhs)
	{
		using std::swap;
		swap(a_Lhs.m_X, a_Rhs.m_X);
		swap(a_Lhs.m_Y, a_Rhs.m_Y);
		swap(a_Lhs.m_Z, a_Rhs.m_Z);
		swap(a_Lhs.m_W, a_Rhs.m_W);
	}
};

Vector4 operator+(Vector4 a_Lhs, const Vector4 &a_Rhs);
Vector4 operator-(Vector4 a_Lhs, const Vector4 &a_Rhs);
Vector4 operator*(Vector4 a_Lhs, float a_Rhs);
Vector4 operator*(float a_Lhs, Vector4 a_Rhs);
float operator*(const Vector4 &a_Lhs, const Vector4 &a_Rhs);
Vector4 operator/(Vector4 a_Lhs, float a_Rhs);
Vector4 operator-(Vector4 a_Lhs);

bool operator==(const Vector4 &a_Lhs, const Vector4 &a_Rhs);
bool operator!=(const Vector4 &a_Lhs, const Vector4 &a_Rhs);
bool operator< (const Vector4 &a_Lhs, const Vector4 &a_Rhs);
bool operator> (const Vector4 &a_Lhs, const Vector4 &a_Rhs);
bool operator<=(const Vector4 &a_Lhs, const Vector4 &a_Rhs);
bool operator>=(const Vector4 &a_Lhs, const Vector4 &a_Rhs);

float Dot(const Vector4 &a_Lhs, const Vector4 &a_Rhs);
// Vector4 Cross(const Vector4 &a_Lhs, const Vector4 &a_Rhs);
float Length(const Vector4 &a_Value);
float LengthSquared(const Vector4 &a_Value);
Vector4 Normalize(const Vector4 &a_Value);
Vector4 Slerp(float a_Factor, const Vector4 &a_From, const Vector4 &a_To);

END_NAMESPACE(Math)
