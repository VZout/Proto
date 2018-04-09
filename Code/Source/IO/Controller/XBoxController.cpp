#include "XBoxController.h"

#include "ControllerState.h"
#include "Platform/Debug/AssertMessage.h"
#include "Utility/UpdateEvent.h"

#include <cmath>
#include <cstdlib>

USING_NAMESPACE(Platform)
USING_NAMESPACE(Utility)

BEGIN_NAMESPACE(IO)

BEGIN_UNNAMEDNAMESPACE()

#if defined(PROTO_PLATFORM_WIN32)

void CopyControllerState(const XINPUT_STATE &a_InputState, ControllerState &a_State)
{
	a_State.m_Buttons = a_InputState.Gamepad.wButtons;
	a_State.m_LeftTrigger = a_InputState.Gamepad.bLeftTrigger;
	a_State.m_RightTrigger = a_InputState.Gamepad.bRightTrigger;
	a_State.m_LeftThumbX = a_InputState.Gamepad.sThumbLX;
	a_State.m_LeftThumbY = a_InputState.Gamepad.sThumbLY;
	a_State.m_RightThumbX = a_InputState.Gamepad.sThumbRX;
	a_State.m_RightThumbY = a_InputState.Gamepad.sThumbRY;
}

#elif defined(PROTO_PLATFORM_RASPBERRY_PI)
#endif


void HandleButtonDown(const ControllerState &a_State, std::vector<ControllerButtonDownCallback*> &a_Callbacks)
{
	if (0 != a_State.m_Buttons)
	{
		for (auto pos = a_Callbacks.begin(); pos != a_Callbacks.end(); ++pos)
		{
			ControllerButtonDownCallback &callback = **pos;
			callback(a_State.m_Buttons);
		}
	}
}

bool IsButtonReleased(unsigned short a_CurrentFlags, unsigned short a_PreviousFlags, EButton a_Button)
{
	return !IsButtonFlagSet(a_CurrentFlags, a_Button) && IsButtonFlagSet(a_PreviousFlags, a_Button);
}

void HandleButtonUp(const ControllerState &a_CurrState, const ControllerState &a_PrevState, std::vector<ControllerButtonDownCallback*> &a_Callbacks)
{
	unsigned short buttonsReleased = 0;
	if (IsButtonReleased(a_CurrState.m_Buttons, a_PrevState.m_Buttons, EButton_A)) { buttonsReleased |= EButton_A; }
	if (IsButtonReleased(a_CurrState.m_Buttons, a_PrevState.m_Buttons, EButton_B)) { buttonsReleased |= EButton_B; }
	if (IsButtonReleased(a_CurrState.m_Buttons, a_PrevState.m_Buttons, EButton_X)) { buttonsReleased |= EButton_X; }
	if (IsButtonReleased(a_CurrState.m_Buttons, a_PrevState.m_Buttons, EButton_Y)) { buttonsReleased |= EButton_Y; }
	if (IsButtonReleased(a_CurrState.m_Buttons, a_PrevState.m_Buttons, EButton_Left)) { buttonsReleased |= EButton_Left; }
	if (IsButtonReleased(a_CurrState.m_Buttons, a_PrevState.m_Buttons, EButton_Right)) { buttonsReleased |= EButton_Right; }
	if (IsButtonReleased(a_CurrState.m_Buttons, a_PrevState.m_Buttons, EButton_Up)) { buttonsReleased |= EButton_Up; }
	if (IsButtonReleased(a_CurrState.m_Buttons, a_PrevState.m_Buttons, EButton_Down)) { buttonsReleased |= EButton_Down; }
	if (IsButtonReleased(a_CurrState.m_Buttons, a_PrevState.m_Buttons, EButton_LeftShoulder)) { buttonsReleased |= EButton_LeftShoulder; }
	if (IsButtonReleased(a_CurrState.m_Buttons, a_PrevState.m_Buttons, EButton_RightShoulder)) { buttonsReleased |= EButton_RightShoulder; }
	if (IsButtonReleased(a_CurrState.m_Buttons, a_PrevState.m_Buttons, EButton_LeftThumb)) { buttonsReleased |= EButton_LeftThumb; }
	if (IsButtonReleased(a_CurrState.m_Buttons, a_PrevState.m_Buttons, EButton_RightThumb)) { buttonsReleased |= EButton_RightThumb; }
	if (IsButtonReleased(a_CurrState.m_Buttons, a_PrevState.m_Buttons, EButton_Start)) { buttonsReleased |= EButton_Start; }
	if (IsButtonReleased(a_CurrState.m_Buttons, a_PrevState.m_Buttons, EButton_Back)) { buttonsReleased |= EButton_Back; }

	if (0 != buttonsReleased)
	{
		for (auto pos = a_Callbacks.begin(); pos != a_Callbacks.end(); ++pos)
		{
			ControllerButtonUpCallback &callback = **pos;
			callback(buttonsReleased);
		}
	}
}

bool IsTriggerPulled(unsigned char a_TriggerValue)
{
	return 0.0f != static_cast<float>(a_TriggerValue) / 255.0f;
}

void HandleTriggerReleased(const ControllerState &a_State, const ControllerState &a_PrevState, std::vector<ControllerTriggerReleasedCallback*> &a_Callbacks)
{
	const bool lefTriggerReleased = !IsTriggerPulled(a_State.m_LeftTrigger) && IsTriggerPulled(a_PrevState.m_LeftTrigger);
	const bool rightTriggerReleased = !IsTriggerPulled(a_State.m_RightTrigger) && IsTriggerPulled(a_PrevState.m_RightTrigger);
	if (lefTriggerReleased || rightTriggerReleased)
	{
		for (auto pos = a_Callbacks.begin(); pos != a_Callbacks.end(); ++pos)
		{
			ControllerTriggerReleasedCallback &callback = **pos;
			if (lefTriggerReleased)
			{
				callback(ETrigger_Left);
			}
			if (rightTriggerReleased)
			{
				callback(ETrigger_Right);
			}
		}
	}
}

void HandleTriggerPulled(const ControllerState &a_State, std::vector<ControllerTriggerPulledCallback*> &a_Callbacks)
{
	const float leftTrigger = static_cast<float>(a_State.m_LeftTrigger) / 255.0f;
	const float rightTrigger = static_cast<float>(a_State.m_RightTrigger) / 255.0f;

	if (0.0f != leftTrigger || 0.0f != rightTrigger)
	{
		for (auto pos = a_Callbacks.begin(); pos != a_Callbacks.end(); ++pos)
		{
			ControllerTriggerPulledCallback &callback = **pos;
			if (0.0f != leftTrigger)
			{
				callback(ETrigger_Left, leftTrigger);
			}
			if (0.0f != rightTrigger)
			{
				callback(ETrigger_Right, rightTrigger);
			}
		}
	}
}

float GetAdjustedValue(short a_RawValue, float a_DeadZone)
{
	const float normalizedValue = fmaxf(-1.0f, static_cast<float>(a_RawValue) / 32767.0f);
	float bufferedValue = (abs(normalizedValue) < a_DeadZone ? 0 : (abs(normalizedValue) - a_DeadZone) * (normalizedValue / abs(normalizedValue)));
	if (a_DeadZone > 0)
	{
		bufferedValue /= (1.0f - a_DeadZone);
	}
	return bufferedValue;
}

bool IsThumbStickMoved(short a_DeltaX, short a_DeltaY, float a_DeadZoneX, float a_DeadZoneY)
{
	const float deltaX = GetAdjustedValue(a_DeltaX, a_DeadZoneX);
	const float deltaY = GetAdjustedValue(a_DeltaY, a_DeadZoneY);
	return (0.0f != deltaX || 0.0f != deltaY);
}

void HandleThumbSticksReleased(const ControllerState &a_CurrState, const ControllerState &a_PrevState, std::vector<ControllerThumbStickReleasedCallback*> &a_Callbacks, float a_DeadZoneX, float a_DeadZoneY)
{
	const bool leftStickReleased = IsThumbStickMoved(a_PrevState.m_LeftThumbX, a_PrevState.m_LeftThumbY, a_DeadZoneX, a_DeadZoneY) && !IsThumbStickMoved(a_CurrState.m_LeftThumbX, a_CurrState.m_LeftThumbY, a_DeadZoneX, a_DeadZoneY);
	const bool rightStickReleased = IsThumbStickMoved(a_PrevState.m_RightThumbX, a_PrevState.m_RightThumbY, a_DeadZoneX, a_DeadZoneY) && !IsThumbStickMoved(a_CurrState.m_RightThumbX, a_CurrState.m_RightThumbY, a_DeadZoneX, a_DeadZoneY);
	if (leftStickReleased || rightStickReleased)
	{
		for (auto pos = a_Callbacks.begin(); pos != a_Callbacks.end(); ++pos)
		{
			ControllerThumbStickReleasedCallback &callback = **pos;
			if (leftStickReleased)
			{
				callback(EThumbStick_Left);
			}
			if (rightStickReleased)
			{
				callback(EThumbStick_Right);
			}
		}
	}
}

void HandleThumbSticksMoved(const ControllerState &a_State, std::vector<ControllerThumbStickMovedCallback*> &a_Callbacks, float a_DeadZoneX, float a_DeadZoneY)
{
	const float leftThumbDeltaX = GetAdjustedValue(a_State.m_LeftThumbX, a_DeadZoneX);
	const float leftThumbDeltaY = GetAdjustedValue(a_State.m_LeftThumbY, a_DeadZoneY);
	const float rightThumbDeltaX = GetAdjustedValue(a_State.m_RightThumbX, a_DeadZoneX);
	const float rightThumbDeltaY = GetAdjustedValue(a_State.m_RightThumbY, a_DeadZoneY);
	if (0.0f != leftThumbDeltaX || 0.0f != leftThumbDeltaY || 0.0f != rightThumbDeltaX || 0.0f != rightThumbDeltaY)
	{
		for (auto pos = a_Callbacks.begin(); pos != a_Callbacks.end(); ++pos)
		{
			ControllerThumbStickMovedCallback &callback = **pos;
			if (0.0f != leftThumbDeltaX || 0.0f != leftThumbDeltaY)
			{
				callback(EThumbStick_Left, leftThumbDeltaX, leftThumbDeltaY);
			}
			if (0.0f != rightThumbDeltaX || 0.0f != rightThumbDeltaY)
			{
				callback(EThumbStick_Right, rightThumbDeltaX, rightThumbDeltaY);
			}
		}
	}
}

END_UNNAMEDNAMESPACE()

XBoxController::XBoxController(float a_DeadZoneX /* = 0.05f */, float a_DeadZoneY /* = 0.02f */)
	: m_DeadZoneX(a_DeadZoneX)
	, m_DeadZoneY(a_DeadZoneY)
{
#if defined(PROTO_PLATFORM_WIN32)
	for (uint32_t index = 0; index < XUSER_MAX_COUNT; ++index)
	{
		m_Connected[index] = false;
		::ZeroMemory(&m_State[index], sizeof(ControllerState));
		::ZeroMemory(&m_PrevState[index], sizeof(ControllerState));
	}
#elif defined(PROTO_PLATFORM_RASPBERRY_PI)
#endif
}

XBoxController::~XBoxController()
{
}

void XBoxController::Update(const UpdateEvent &a_UpdateEvent)
{
	UNUSED(a_UpdateEvent);

#if defined(PROTO_PLATFORM_WIN32)
	for (uint32_t index = 0; index < XUSER_MAX_COUNT; ++index)
	{
		XINPUT_STATE inputState;
		ZeroMemory(&inputState, sizeof(XINPUT_STATE));

		if (XInputGetState(index, &inputState) == ERROR_SUCCESS)
		{
			m_Connected[index] = true;
			CopyControllerState(inputState, m_State[index]);

			HandleButtonUp(m_State[index], m_PrevState[index], m_ButtonUpCallbacks);
			HandleButtonDown(m_State[index], m_ButtonDownCallbacks);

			HandleTriggerReleased(m_State[index], m_PrevState[index], m_TriggerReleasedCallbacks);
			HandleTriggerPulled(m_State[index], m_TriggerPulledCallbacks);

			HandleThumbSticksReleased(m_State[index], m_PrevState[index], m_ThumbStickReleasedCallbacks, m_DeadZoneX, m_DeadZoneY);
			HandleThumbSticksMoved(m_State[index], m_ThumbStickMovedCallbacks, m_DeadZoneX, m_DeadZoneY);

			m_PrevState[index] = m_State[index];
		}
		else
		{
			m_Connected[index] = false;
		}
	}
#elif defined(PROTO_PLATFORM_RASPBERRY_PI)
#endif	
}

END_NAMESPACE(IO)
