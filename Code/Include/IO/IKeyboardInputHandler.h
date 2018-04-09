#pragma once

#include "Proto.h"

FORWARD_DECLARE(Platform, struct KeyEvent);

BEGIN_NAMESPACE(IO)

class IKeyboardInputHandler
{
public:
	virtual void OnKeyDown(const Platform::KeyEvent &a_KeyEvent) = 0;
	virtual void OnKeyUp(const Platform::KeyEvent &a_KeyEvent) = 0;
};

END_NAMESPACE(IO)
