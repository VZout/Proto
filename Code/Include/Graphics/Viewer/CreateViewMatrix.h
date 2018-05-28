#pragma once

// TODO: Move to Math library

#include "Proto.h"
#include "Math/Matrix4.h"

BEGIN_NAMESPACE(Math)

class Quaternion;
class Vector3;

Matrix4 CreateViewMatrixLH(const Vector3 &a_EyePosition, const Vector3 &a_TargetPosition, const Vector3 &a_Up);
Matrix4 CreateViewMatrixLH(const Quaternion &a_Orientation, const Vector3 &a_Position);
Matrix4 CreateViewMatrixRH(const Vector3 &a_EyePosition, const Vector3 &a_TargetPosition, const Vector3 &a_Up);
Matrix4 CreateViewMatrixRH(const Quaternion &a_Orientation, const Vector3 &a_Position);

END_NAMESPACE(Math)
