#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Math)

enum ERotationMultiplicationOrder
{
	// proper euler angles
	ERotationMultiplicationOrder_ZXZ,
	ERotationMultiplicationOrder_XYX,
	ERotationMultiplicationOrder_YZY,
	ERotationMultiplicationOrder_ZYZ,
	ERotationMultiplicationOrder_XZX,
	ERotationMultiplicationOrder_YXY,

	// tait–bryan angles
	ERotationMultiplicationOrder_XYZ,
	ERotationMultiplicationOrder_YZX,
	ERotationMultiplicationOrder_ZXY,
	ERotationMultiplicationOrder_XZY,
	ERotationMultiplicationOrder_ZYX,
	ERotationMultiplicationOrder_YXZ,

	ERotationMultiplicationOrder_Invalid
};

END_NAMESPACE(Math)
