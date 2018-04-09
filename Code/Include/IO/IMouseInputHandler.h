#pragma once

#include "Proto.h"

FORWARD_DECLARE(Platform, struct MouseEvent);
FORWARD_DECLARE(Platform, struct MouseMoveEvent);
FORWARD_DECLARE(Platform, struct MouseWheelEvent);

BEGIN_NAMESPACE(IO)

class IMouseInputHandler
{
public:
	virtual void OnMouseMove(const Platform::MouseMoveEvent &a_MouseMoveEvent) = 0;
	virtual void OnMouseButtonDown(const Platform::MouseEvent &a_MouseEvent) = 0;
	virtual void OnMouseButtonUp(const Platform::MouseEvent &a_MouseEvent) = 0;
	virtual void OnMouseWheel(const Platform::MouseWheelEvent &a_MouseWheelEvent) = 0;
};

END_NAMESPACE(IO)
