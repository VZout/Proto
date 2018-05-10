#pragma once

#include "Proto.h"

#include "Matrix4.h"

BEGIN_NAMESPACE(Math)

class Matrix;

class Quaternion
{
public:
	Quaternion();
	Quaternion(float a_X, float a_Y, float a_Z, float a_W);
	Quaternion(const Quaternion &a_Lhs);
	Quaternion(const Matrix4 &a_Matrix);
	~Quaternion();

	Quaternion& operator*=(const Quaternion &a_Rhs);
	Quaternion& operator*=(float a_Rhs);

	void Normalize();

#if !defined(PROTO_PLATFORM_ORBIS)
#pragma warning(push)
#pragma warning(disable : 4201)
#endif
	union
	{
		float m[4];
		struct
		{
			float m_X;
			float m_Y;
			float m_Z;
			float m_W;
		};
	};
#if !defined(PROTO_PLATFORM_ORBIS)
#pragma warning(pop) 
#endif
};

Quaternion operator*(Quaternion a_Lhs, const Quaternion &a_Rhs);
Quaternion operator*(Quaternion a_Lhs, float a_Rhs);
Vector3 operator*(Quaternion a_Lhs, const Vector3 &a_Rhs);

Quaternion Concatenate(const Quaternion &a_Rhs, const Quaternion &a_Lhs);

Quaternion Normalize(const Quaternion &a_Value);
float Length(const Quaternion &a_Value);
Matrix4 ToMatrix(const Quaternion &a_Quaternion);
Quaternion ToQuaternion(const Matrix4 &a_Matrix);
Quaternion FromAngleAxis(float a_Radians, const Vector3 &a_Axis);

END_NAMESPACE(Math)
