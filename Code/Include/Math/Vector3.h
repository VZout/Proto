#pragma once

#include "Proto.h"

#include <utility>

BEGIN_NAMESPACE(Math)

class Quaternion;

class Vector3
{
public:
	static const Vector3 ORIGIN;
	static const Vector3 X_AXIS;
	static const Vector3 NEG_X_AXIS;
	static const Vector3 Y_AXIS;
	static const Vector3 NEG_Y_AXIS;
	static const Vector3 Z_AXIS;
	static const Vector3 NEG_Z_AXIS;

public:
	Vector3();
	Vector3(float a_X, float a_Y, float a_Z);
	Vector3(const Vector3 &a_Rhs);
	~Vector3();

	void Clear();
	void Normalize();

	Vector3& operator=(Vector3 a_Rhs);
	Vector3& operator+=(const Vector3 &a_Rhs);
	Vector3& operator-=(const Vector3 &a_Rhs);
	Vector3& operator*=(float a_Rhs);
	Vector3& operator/=(float a_Rhs);

#if !defined(PROTO_PLATFORM_ORBIS)
#pragma warning( push )
#pragma warning( disable : 4201 )
#endif
	union
	{
		float m_F[3];
		struct
		{
			float m_X;
			float m_Y;
			float m_Z;
		};
	};
#if !defined(PROTO_PLATFORM_ORBIS)
#pragma warning(pop)
#endif

	friend void swap(Vector3 &a_Lhs, Vector3 &a_Rhs)
	{
		using std::swap;
		swap(a_Lhs.m_X, a_Rhs.m_X);
		swap(a_Lhs.m_Y, a_Rhs.m_Y);
		swap(a_Lhs.m_Z, a_Rhs.m_Z);
	}
};

Vector3 operator+(Vector3 a_Lhs, const Vector3 &a_Rhs);
Vector3 operator-(Vector3 a_Lhs, const Vector3 &a_Rhs);
Vector3 operator*(Vector3 a_Lhs, float a_Rhs);
Vector3 operator*(float a_Lhs, Vector3 a_Rhs);
float operator*(const Vector3 &a_Lhs, const Vector3 &a_Rhs);
Vector3 operator/(Vector3 a_Lhs, float a_Rhs);
Vector3 operator-(Vector3 a_Lhs);

bool operator==(const Vector3 &a_Lhs, const Vector3 &a_Rhs);
bool operator!=(const Vector3 &a_Lhs, const Vector3 &a_Rhs);
bool operator< (const Vector3 &a_Lhs, const Vector3 &a_Rhs);
bool operator> (const Vector3 &a_Lhs, const Vector3 &a_Rhs);
bool operator<=(const Vector3 &a_Lhs, const Vector3 &a_Rhs);
bool operator>=(const Vector3 &a_Lhs, const Vector3 &a_Rhs);

float Dot(const Vector3 &a_Lhs, const Vector3 &a_Rhs);
Vector3 Cross(const Vector3 &a_Lhs, const Vector3 &a_Rhs);
float Length(const Vector3 &a_Value);
float LengthSquared(const Vector3 &a_Value);
Vector3 Negate(const Vector3 &a_Vector);
Vector3 Normalize(const Vector3 &a_Value);
Vector3 Rotate(const Vector3 &a_Vector, const Quaternion &a_Rotation);
Vector3 Slerp(float a_Factor, const Vector3 &a_From, const Vector3 &a_To);
bool AnyNonZero(const Vector3 &a_Vector);

END_NAMESPACE(Math)
