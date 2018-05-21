#include "WindowProcedure.h"

#include "Platform/Debug/AssertMessage.h"
#if defined(PROTO_USE_INSPECTOR)
#include "Platform/Debug/Inspect.h"
#include "Platform/Debug/Inspector.h"
#endif
#include "Platform/EKeyCode.h"
#include "Platform/Helpers/WindowFunctions.h"
#include "Platform/IApplication.h"
#include "Platform/KeyEvent.h"
#include "Platform/MouseEvent.h"

BEGIN_NAMESPACE(Platform)

BEGIN_UNNAMEDNAMESPACE()

MouseEvent::EMouseButton Convert(uint32_t a_Msg)
{
	MouseEvent::EMouseButton button = MouseEvent::EMouseButton_Invalid;

	switch (a_Msg)
	{
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	{
		button = MouseEvent::EMouseButton_Left;
		break;
	}
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
	{
		button = MouseEvent::EMouseButton_Right;
		break;
	}
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MBUTTONDBLCLK:
	{
		button = MouseEvent::EMouseButton_Middle;
		break;
	}

	default:
	{
		AssertMessage("Invalid mouse button message encountered!");
		break;
	}
	}
	return button;
}

END_UNNAMEDNAMESPACE()

LRESULT CALLBACK WindowProcedure(HWND a_WindowHandle, UINT a_Msg, WPARAM a_WParam, LPARAM a_LParam)
{
#if defined(PROTO_USE_INSPECTOR)
	if (Inspector::AbsorbInput(a_WindowHandle, a_Msg, a_WParam, a_LParam))
	{
		return ::DefWindowProc(a_WindowHandle, a_Msg, a_WParam, a_LParam);
	}
#endif

	LRESULT result = 0;
	IApplication *applicationPointer = nullptr;
	LONG_PTR userData = ::GetWindowLongPtr(a_WindowHandle, GWLP_USERDATA);
	if (0 != userData)
	{
		applicationPointer = reinterpret_cast<IApplication*>(userData);
		AssertMessage(nullptr != applicationPointer, "Failed to get application interface pointer.");
	}

	PAINTSTRUCT paintStruct;

	switch (a_Msg)
	{
		case WM_DESTROY:
		{
			::PostQuitMessage(0);
			break;
		}
		case WM_MOUSEMOVE:
		{
			const bool leftButtonDown = (a_WParam & MK_LBUTTON) != 0;
			const bool rightButtonDown = (a_WParam & MK_RBUTTON) != 0;
			const bool middleButtonDown = (a_WParam & MK_MBUTTON) != 0;
			const bool shiftDown = (a_WParam & MK_SHIFT) != 0;
			const bool controlDown = (a_WParam & MK_CONTROL) != 0;

			const int x = static_cast<int>(static_cast<short>(LOWORD(a_LParam)));
			const int y = static_cast<int>(static_cast<short>(HIWORD(a_LParam)));

			if (nullptr != applicationPointer)
			{
				applicationPointer->OnMouseMove(MouseMoveEvent(leftButtonDown, middleButtonDown, rightButtonDown, shiftDown, controlDown, x, y));
			}
			break;
		}
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		{
			const bool leftButtonDown = (a_WParam & MK_LBUTTON) != 0;
			const bool rightButtonDown = (a_WParam & MK_RBUTTON) != 0;
			const bool middleButtonDown = (a_WParam & MK_MBUTTON) != 0;
			const bool shiftDown = (a_WParam & MK_SHIFT) != 0;
			const bool controlDown = (a_WParam & MK_CONTROL) != 0;

			const int x = static_cast<int>(static_cast<short>(LOWORD(a_LParam)));
			const int y = static_cast<int>(static_cast<short>(HIWORD(a_LParam)));

			if (nullptr != applicationPointer)
			{
				applicationPointer->OnMouseButtonDown(MouseEvent(Convert(a_Msg), leftButtonDown, middleButtonDown, rightButtonDown, shiftDown, controlDown, x, y));
			}
			break;
		}
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		{
			const bool leftButtonDown = (a_WParam & MK_LBUTTON) != 0;
			const bool rightButtonDown = (a_WParam & MK_RBUTTON) != 0;
			const bool middleButtonDown = (a_WParam & MK_MBUTTON) != 0;
			const bool shiftDown = (a_WParam & MK_SHIFT) != 0;
			const bool controlDown = (a_WParam & MK_CONTROL) != 0;

			const int x = static_cast<int>(static_cast<short>(LOWORD(a_LParam)));
			const int y = static_cast<int>(static_cast<short>(HIWORD(a_LParam)));

			if (nullptr != applicationPointer)
			{
				applicationPointer->OnMouseButtonUp(MouseEvent(Convert(a_Msg), leftButtonDown, middleButtonDown, rightButtonDown, shiftDown, controlDown, x, y));
			}
			break;
		}
		case WM_MOUSEWHEEL:
		{
			const float deltaZ = static_cast<int>(static_cast<short>(HIWORD(a_WParam))) / static_cast<float>(WHEEL_DELTA);
			const short keyStates = static_cast<short>(LOWORD(a_WParam));

			const bool leftButtonDown = (a_WParam & MK_LBUTTON) != 0;
			const bool rightButtonDown = (a_WParam & MK_RBUTTON) != 0;
			const bool middleButtonDown = (a_WParam & MK_MBUTTON) != 0;
			const bool shiftDown = (a_WParam & MK_SHIFT) != 0;
			const bool controlDown = (a_WParam & MK_CONTROL) != 0;

			const int x = static_cast<int>(static_cast<short>(LOWORD(a_LParam)));
			const int y = static_cast<int>(static_cast<short>(HIWORD(a_LParam)));

			POINT clientToScreenPoint;
			clientToScreenPoint.x = x;
			clientToScreenPoint.y = y;
			::ScreenToClient(a_WindowHandle, &clientToScreenPoint);

			if (nullptr != applicationPointer)
			{
				applicationPointer->OnMouseWheel(MouseWheelEvent(deltaZ, leftButtonDown, middleButtonDown, rightButtonDown, shiftDown, controlDown, static_cast<int>(clientToScreenPoint.x), static_cast<int>(clientToScreenPoint.y)));
			}
			break;
		}
		case WM_KEYDOWN:
		{
			MSG charMsg;
			unsigned int character = 0;
			if (::PeekMessage(&charMsg, a_WindowHandle, 0, 0, PM_NOREMOVE) && charMsg.message == WM_CHAR)
			{
				::GetMessage(&charMsg, a_WindowHandle, 0, 0);
				character = static_cast<unsigned int>(charMsg.wParam);
			}
			const bool shiftDown = ::GetAsyncKeyState(VK_SHIFT) > 0;
			const bool controlDown = ::GetAsyncKeyState(VK_CONTROL) > 0;
			const bool altDown = ::GetAsyncKeyState(VK_MENU) > 0;
			EKeyCode keyCode = static_cast<EKeyCode>(a_WParam);
			const uint32_t scanCode = (a_LParam & 0x00ff0000) >> 16;

			if (nullptr != applicationPointer)
			{
				applicationPointer->OnKeyDown(KeyEvent(keyCode, character, KeyEvent::State_Down, shiftDown, controlDown, altDown));
			}
			break;
		}
		case WM_KEYUP:
		{
			switch (a_WParam)
			{
			case VK_ESCAPE:
			{
				::PostQuitMessage(0);
				break;
			}
			}

			const bool shiftDown = ::GetAsyncKeyState(VK_SHIFT) > 0;
			const bool controlDown = ::GetAsyncKeyState(VK_CONTROL) > 0;
			const bool altDown = ::GetAsyncKeyState(VK_MENU) > 0;
			EKeyCode keyCode = static_cast<EKeyCode>(a_WParam);
			const uint32_t scanCode = (a_LParam & 0x00ff0000) >> 16;

			unsigned int character = 0;
			unsigned char keyboardState[256];
			::GetKeyboardState(keyboardState);
			wchar_t translatedCharacters[4];
			if (::ToUnicodeEx(static_cast<UINT>(a_WParam), scanCode, keyboardState, translatedCharacters, 4, 0, NULL) > 0)
			{
				character = translatedCharacters[0];
			}

			if (nullptr != applicationPointer)
			{
				applicationPointer->OnKeyUp(KeyEvent(keyCode, character, KeyEvent::State_Up, shiftDown, controlDown, altDown));
			}
			break;
		}
		case WM_PAINT:
		{
			::BeginPaint(a_WindowHandle, &paintStruct);
			::EndPaint(a_WindowHandle, &paintStruct);
			break;
		}
		case WM_SIZE:
		{
			switch (a_WParam)
			{
			case SIZE_MAXHIDE:
				break;
			case SIZE_MAXIMIZED:
				break;
			case SIZE_MAXSHOW:
				break;
			case SIZE_MINIMIZED:
				break;
			case SIZE_RESTORED:
				break;
			}
			if (nullptr != applicationPointer)
			{
				applicationPointer->OnResize(LOWORD(a_LParam), HIWORD(a_LParam));
			}
		}
	default:
		{
			result = ::DefWindowProc(a_WindowHandle, a_Msg, a_WParam, a_LParam);
			break;
		}
	}

	return result;
}

END_NAMESPACE(Platform)
