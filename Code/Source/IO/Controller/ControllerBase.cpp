#include "ControllerBase.h"

#include "Platform/Debug/AssertMessage.h"
#include "Utility/ClearContainerContents.h"

USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(IO)

ControllerBase::ControllerBase()
{
}

ControllerBase::~ControllerBase()
{
	ClearContainerContents(m_ButtonDownCallbacks);
}

uint32_t ControllerBase::GetButtonIndex(EButton a_Button)
{
	uint32_t buttonIndex = 0;
	switch (a_Button)
	{
	case EButton_A:
		{
			buttonIndex = 0;
			break;
		}
	case EButton_B:
		{
			buttonIndex = 1;
			break;
		}
	case EButton_X:
		{
			buttonIndex = 2;
			break;
		}
	case EButton_Y:
		{
			buttonIndex = 3;
			break;
		}
	case EButton_Left:
		{
			buttonIndex = 4;
			break;
		}
	case EButton_Right:
		{
			buttonIndex = 5;
			break;
		}
	case EButton_Up:
		{
			buttonIndex = 6;
			break;
		}
	case EButton_Down:
		{
			buttonIndex = 7;
			break;
		}
	case EButton_LeftShoulder:
		{
			buttonIndex = 8;
			break;
		}
	case EButton_RightShoulder:
		{
			buttonIndex = 9;
			break;
		}
	case EButton_LeftThumb:
		{
			buttonIndex = 10;
			break;
		}
	case EButton_RightThumb:
		{
			buttonIndex = 11;
			break;
		}
	case EButton_Start:
		{
			buttonIndex = 12;
			break;
		}
	case EButton_Back:
		{
			buttonIndex = 13;
			break;
		}
	case EButton_Count:
	case EButton_Invalid:
		default:
		{
			AssertMessage("Invalid button index encountered!");
			break;
		}
	}
	return buttonIndex;
}

bool IsButtonFlagSet(short a_Flags, EButton a_ButtonCode)
{
	return 0 != (a_Flags & a_ButtonCode);
}

END_NAMESPACE(IO)

