#pragma once

#include "Proto.h"
#include "EKeyCode.h"

BEGIN_NAMESPACE(Platform)

struct KeyEvent
{
	enum State
	{
		State_Down,
		State_Up
	};

	KeyEvent(EKeyCode a_KeyCode, uint32_t a_Character, State a_State, bool a_ShiftDown, bool a_ControlDown, bool a_AltDown)
	: m_KeyCode(a_KeyCode)
	, m_Character(a_Character)
	, m_State(a_State)
	, m_ShiftDown(a_ShiftDown)
	, m_ControlDown(a_ControlDown)
	, m_AltDown(a_AltDown)
	{
	}

	const EKeyCode m_KeyCode; 
	const uint32_t m_Character;
	const State m_State;
	const bool m_ShiftDown;
	const bool m_ControlDown;
	const bool m_AltDown;
};

END_NAMESPACE(Platform)
