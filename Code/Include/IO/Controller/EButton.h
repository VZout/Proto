#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(IO)

enum EButton
{
	EButton_A				= 0x1000,
	EButton_B				= 0x2000,
	EButton_X				= 0x4000,
	EButton_Y				= 0x8000,
	EButton_Left			= 0x0004,
	EButton_Right			= 0x0008,
	EButton_Up				= 0x0001,
	EButton_Down			= 0x0002,
	EButton_LeftShoulder	= 0x0100,
	EButton_RightShoulder	= 0x0200,
	EButton_LeftThumb		= 0x0040,
	EButton_RightThumb		= 0x0080,
	EButton_Start			= 0x0010,
	EButton_Back			= 0x0020,
	EButton_Count			= 14,

	EButton_Invalid
};

END_NAMESPACE(IO)
