#pragma once

#include "Proto.h"
#include "ERotationMultiplicationOrder.h"

#include "Vector3.h"

#include <stdint.h>

BEGIN_NAMESPACE(Math)

class Vector4;
class Quaternion;

class Matrix4
{
public:
	Matrix4();
	Matrix4(float a_00, float a_01, float a_02, float a_03,
		float a_10, float a_11, float a_12, float a_13,
		float a_20, float a_21, float a_22, float a_23,
		float a_30, float a_31, float a_32, float a_33);
	Matrix4(const Vector4 &a_XAxis, const Vector4 &a_YAxis, const Vector4 &a_ZAxis, const Vector4 &a_Translation);
	Matrix4(const Matrix4 &a_Rhs);
	Matrix4(const Quaternion &a_Quat);
	~Matrix4();

	Matrix4& operator=(Matrix4 a_Rhs);
	Matrix4& operator+=(const Matrix4 &a_Rhs);
	Matrix4& operator-=(const Matrix4 &a_Rhs);
	Matrix4& operator*=(const Matrix4 &a_Rhs);

	void SetTranslation(float a_X, float a_Y, float a_Z);
	void SetTranslation(const Vector3 &a_Translation);
	Vector3 GetTranslation() const;
	Vector3 GetXAxis() const;
	Vector3 GetYAxis() const;
	Vector3 GetZAxis() const;

	void SetOrientation(const Vector3 &a_XAxis, const Vector3 &a_YAxis, const Vector3 &a_ZAxis);
	void SetEulerAxis(float a_Yaw, float a_Pitch, float a_Roll);

#pragma warning( push )
#pragma warning( disable : 4201 )
	union
	{
		float m[4][4];
		float f[16];
	};
#pragma warning( pop ) 

	friend void swap(Matrix4 &a_Lhs, Matrix4 &a_Rhs)
	{
		using std::swap;
		for (uint32_t index = 0; index < 16; ++index)
		{
			swap(a_Lhs.f[index], a_Rhs.f[index]);
		}
	}
};

Matrix4 operator+(Matrix4 a_Lhs, const Matrix4 &a_Rhs);
Matrix4 operator-(Matrix4 a_Lhs, const Matrix4 &a_Rhs);
Matrix4 operator*(Matrix4 a_Lhs, const Matrix4 &a_Rhs);
Vector3 operator*(const Matrix4 &a_Rhs, const Vector3& a_Vector);

bool operator==(const Matrix4 &a_Lhs, const Matrix4 &a_Rhs);
bool operator!=(const Matrix4 &a_Lhs, const Matrix4 &a_Rhs);
bool operator< (const Matrix4 &a_Lhs, const Matrix4 &a_Rhs);
bool operator> (const Matrix4 &a_Lhs, const Matrix4 &a_Rhs);
bool operator<=(const Matrix4 &a_Lhs, const Matrix4 &a_Rhs);
bool operator>=(const Matrix4 &a_Lhs, const Matrix4 &a_Rhs);

float Determinant(const Matrix4 &a_Matrix);
Matrix4 Inverse(const Matrix4 &a_Matrix);
Matrix4 Transpose(const Matrix4 &a_Matrix);
Matrix4 CreateIdentity();
Matrix4 CreateTranslation(const Vector3 &a_Translation);
Matrix4 CreateTranslation(float a_X, float a_Y, float a_Z);
Matrix4 CreateScale(float a_Scale);
Matrix4 CreateScale(const Vector3 &a_Scale);
Matrix4 CreateRotate(float a_Radians, const Vector3 &a_Axis);
Matrix4 CreateRotate(float a_Roll, float a_Pitch, float a_Yaw, ERotationMultiplicationOrder a_Order = ERotationMultiplicationOrder_XYZ);
Matrix4 CreateRotateX(float a_Radians);
Matrix4 CreateRotateY(float a_Radians);
Matrix4 CreateRotateZ(float a_Radians);
Matrix4 FromEulerAngles(const Vector3 &a_Angles, ERotationMultiplicationOrder a_Order = ERotationMultiplicationOrder_XYZ);
Matrix4 FromEulerAnglesYX(float a_AngleY, float a_AngleX);
Matrix4 CreateOrthoLH(float a_Left, float a_Right, float a_Bottom, float a_Top, float a_NearZ, float a_FarZ);
Matrix4 CreateOrthoRH(float a_Left, float a_Right, float a_Bottom, float a_Top, float a_NearZ, float a_FarZ);
Matrix4 CreateFrustum(float a_Left, float a_Right, float a_Bottom, float a_Top, float a_NearZ, float a_FarZ);
Matrix4 CreatePerspectiveLH(float a_FOVy, float a_Aspect, float a_NearZ, float a_FarZ);
Matrix4 CreatePerspectiveRH(float a_FOVy, float a_Aspect, float a_NearZ, float a_FarZ);
Matrix4 CreateLookAtLH(const Vector3 &a_Eye, const Vector3 &a_Center, const Vector3 &a_Up);
Matrix4 CreateLookAtRH(const Vector3 &a_Eye, const Vector3 &a_Center, const Vector3 &a_Up);
Vector3 Transform(const Matrix4 &a_Transform, const Vector3 &a_Direction);
void ExtractYawPitchRoll(const Matrix4 &a_Matrix, float &a_Yaw, float &a_Pitch, float &a_Roll);
void ExtractYawPitchRollDegrees(const Matrix4 &a_Matrix, float &a_Yaw, float &a_Pitch, float &a_Roll);
void ExtractEulerAngles(const Matrix4 &a_Matrix, float &a_X, float &a_Y, float &a_Z);
void ExtractEulerAnglesDegrees(const Matrix4 &a_Matrix, float &a_X, float &a_Y, float &a_Z);

END_NAMESPACE(Math)

