#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Platform)

struct MouseEvent
{
	enum EMouseButton
	{
		EMouseButton_Left,
		EMouseButton_Middle,
		EMouseButton_Right,

		EMouseButton_Invalid
	};

	MouseEvent(EMouseButton a_MouseButton, bool a_LeftButtonDown, bool a_MiddleButtonDown, bool a_RightButtonDown, bool a_ShiftDown, bool a_ControlDown, int a_X, int a_Y)
	: m_MouseButton(a_MouseButton)
	, m_LeftButtonDown(a_LeftButtonDown)
	, m_MiddleButtonDown(a_MiddleButtonDown)
	, m_RightButtonDown(a_RightButtonDown)
	, m_ShiftDown(a_ShiftDown)
	, m_ControlDown(a_ControlDown)
	, m_X(a_X)
	, m_Y(a_Y)
	{
	}

	const EMouseButton m_MouseButton;
	const bool m_LeftButtonDown;
	const bool m_MiddleButtonDown;
	const bool m_RightButtonDown;
	const bool m_ShiftDown;
	const bool m_ControlDown;
	const int m_X;
	const int m_Y;
};

struct MouseMoveEvent
{
	MouseMoveEvent(bool a_LeftButtonDown, bool a_MiddleButtonDown, bool a_RightButtonDown, bool a_ShiftDown, bool a_ControlDown, int a_X, int a_Y)
	: m_LeftButtonDown(a_LeftButtonDown)
	, m_MiddleButtonDown(a_MiddleButtonDown)
	, m_RightButtonDown(a_RightButtonDown)
	, m_ShiftDown(a_ShiftDown)
	, m_ControlDown(a_ControlDown)
	, m_X(a_X)
	, m_Y(a_Y)
	{
	}

	const bool m_LeftButtonDown;
	const bool m_MiddleButtonDown;
	const bool m_RightButtonDown;
	const bool m_ShiftDown;
	const bool m_ControlDown;
	const int m_X;
	const int m_Y;
};

struct MouseWheelEvent
{
	MouseWheelEvent(float a_DeltaZ, bool a_LeftButtonDown, bool a_MiddleButtonDown, bool a_RightButtonDown, bool a_ShiftDown, bool a_ControlDown, int a_X, int a_Y)
	: m_DeltaZ(a_DeltaZ)
	, m_LeftButtonDown(a_LeftButtonDown)
	, m_MiddleButtonDown(a_MiddleButtonDown)
	, m_RightButtonDown(a_RightButtonDown)
	, m_ShiftDown(a_ShiftDown)
	, m_ControlDown(a_ControlDown)
	, m_X(a_X)
	, m_Y(a_Y)
	{
	}

	const float m_DeltaZ;
	const bool m_LeftButtonDown;
	const bool m_MiddleButtonDown;
	const bool m_RightButtonDown;
	const bool m_ShiftDown;
	const bool m_ControlDown;
	const int m_X;
	const int m_Y;
};

END_NAMESPACE(Platform)
