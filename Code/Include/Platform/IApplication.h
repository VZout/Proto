#pragma once

#include "Proto.h"

#include "IO/IKeyboardInputHandler.h"
#include "IO/IMouseInputHandler.h"
#include "Utility/IUpdatable.h"

BEGIN_NAMESPACE(Platform)

struct KeyEvent;
struct MouseEvent;
struct MouseMoveEvent;
struct MouseWheelEvent;

class IApplication : public Utility::IUpdatable, public IO::IKeyboardInputHandler, public IO::IMouseInputHandler
{
public:
	virtual void OnResize(const uint32_t a_Width, const uint32_t a_Height) = 0;
};

END_NAMESPACE(Platform)
