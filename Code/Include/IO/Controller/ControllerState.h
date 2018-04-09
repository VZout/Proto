#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(IO)

struct ControllerState
{
	unsigned short m_Buttons;
	unsigned char m_LeftTrigger;
	unsigned char m_RightTrigger;
	short m_LeftThumbX;
	short m_LeftThumbY;
	short m_RightThumbX;
	short m_RightThumbY;
};

END_NAMESPACE(IO)
