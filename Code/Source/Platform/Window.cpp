#include "Window.h"

#include "Platform/Debug/AssertMessage.h"
#include "Platform/Helpers/StringFunctions.h"

#if defined(PROTO_PLATFORM_RASPBERRY_PI)
#include "bcm_host.h"
#endif

USING_NAMESPACE(Math)

BEGIN_NAMESPACE(Platform)

BEGIN_UNNAMEDNAMESPACE()

#if defined(PROTO_PLATFORM_WIN32)

WNDCLASS GetDefaultWindowClass(HINSTANCE a_Instance, LPCWSTR a_ClassName)
{
	WNDCLASS windowClass;
	windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	windowClass.lpfnWndProc = (WNDPROC)WindowProcedure;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = a_Instance;
	windowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = a_ClassName;

	return windowClass;
}

Dimension GetClientRect(HWND a_Handle)
{
	RECT r;
	::GetClientRect(a_Handle, &r);
	Dimension clientRect;
	clientRect.m_Width = r.right;
	clientRect.m_Height = r.bottom;
	return clientRect;
}

#endif

END_UNNAMEDNAMESPACE()

Window::Window(int a_Width, int a_Height)
	: m_Handle(NULLPTR)
	, m_WindowSize(a_Width, a_Height)
	, m_ClientSize()
	, m_Fullscreen(false)
{
#if defined(PROTO_PLATFORM_WIN32)
	DWORD style = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
	HINSTANCE instance = GetModuleHandle(NULL);

	WNDCLASS wndClass = GetDefaultWindowClass(instance, L"ApplicationWindow");
	Register(wndClass);
	Create(style, L"ApplicationWindow", a_Width, a_Height, instance);
#else
	AssertMessage("Not implemented on this platform!");
#endif
}

Window::Window(const wchar_t *a_Title, uint32_t a_Width, uint32_t a_Height)
	: m_Handle(NULLPTR)
	, m_WindowSize(a_Width, a_Height)
	, m_ClientSize()
	, m_Fullscreen(false)
{
#if defined(PROTO_PLATFORM_WIN32)
	WNDCLASS windowClass;
	DWORD style = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;

	HINSTANCE hInstance = GetModuleHandle(NULL);

	windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	windowClass.lpfnWndProc = (WNDPROC)WindowProcedure;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = hInstance;
	windowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = a_Title;

	if (!RegisterClass(&windowClass)) 
	{
		AssertMessage("Registering window class failed!");
	}

	RECT adjustedWindowSize = { 0, 0, static_cast<LONG>(a_Width), static_cast<LONG>(a_Height) };
	AdjustWindowRect(&adjustedWindowSize, WS_OVERLAPPEDWINDOW, FALSE);
	m_Handle = CreateWindowEx(style, a_Title, a_Title, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 
		adjustedWindowSize.right - adjustedWindowSize.left,
		adjustedWindowSize.bottom - adjustedWindowSize.top,
		NULL, NULL, hInstance, NULL);
	AssertMessage(0 != m_Handle, ("Error creating window!"));
#else
	AssertMessage("Not implemented on this platform!");
	UNUSED(a_Title);
#endif
}

Window::~Window()
{
#if defined(PROTO_PLATFORM_WIN32)
	Destroy();
#endif
}

void Window::Show(EWindowState a_State)
{
#if defined(PROTO_PLATFORM_WIN32)
	int cmdShow = -1;
	switch (a_State)
	{
	case Platform::EWindowState_Hide:
		{
			cmdShow = SW_HIDE;
			break;
		}
	case Platform::EWindowState_Show:
		{
			cmdShow = SW_SHOW;
			break;
		}
	case Platform::EWindowState_ForceMinimize:
	case Platform::EWindowState_Maximize:
	case Platform::EWindowState_Minimize:
	case Platform::EWindowState_Restore:
	case Platform::EWindowState_Default:
	case Platform::EWindowState_Maximized:
	case Platform::EWindowState_Minimized:
	case Platform::EWindowState_MinNoActive:
	case Platform::EWindowState_NA:
	case Platform::EWindowState_NoActive:
	case Platform::EWindowState_Normal:
	case Platform::EWindowState_Invalid:
	default:
		{
			AssertMessage("Invalid window show state encountered!");
		}
		break;
	}
	::ShowWindow(m_Handle, cmdShow);
#else
	AssertMessage("Not implemented on this platform!");
#endif
}

void Window::Update()
{
#if defined(PROTO_PLATFORM_WIN32)
	::UpdateWindow(m_Handle);
#else
	AssertMessage("Not implemented on this platform!");
#endif
}

const Dimension& Window::GetSize() const
{
	return m_WindowSize;
}

const Dimension& Window::GetClientRectSize() const
{
	return m_ClientSize;
}

NativeWindowHandle Window::GetHandle() const
{
	return m_Handle;
}

void Window::SetTitle(const std::string &a_Title)
{
#if defined(PROTO_PLATFORM_WIN32)
	AssertMessage(0 != m_Handle, ("Attempt to use an invalid window handle!"));

	std::wstring title = StringToWideString(a_Title);
	::SetWindowText(m_Handle, title.c_str());
#else
	AssertMessage("Not implemented on this platform!");
#endif
}

std::string Window::GetTitle()
{
	wchar_t title[128];
	::GetWindowText(m_Handle, title, 128);
	return WideStringToString(std::wstring(title));;
}

void Window::SetFullscreen(bool a_Fullscreen)
{
	m_Fullscreen = a_Fullscreen;
}

void Window::SetApplicationHandle(IApplication &a_Application)
{
#if defined(PROTO_PLATFORM_WIN32)
	LONG_PTR applicationPointer = reinterpret_cast<LONG_PTR>(&a_Application);
	::SetWindowLongPtr(m_Handle, GWLP_USERDATA, applicationPointer);
#else
	AssertMessage("Not implemented on this platform!");
#endif
}

#if defined(PROTO_PLATFORM_WIN32)
void Window::Register(WNDCLASS &a_WindowClass)
{
	if (!RegisterClass(&a_WindowClass))
	{
		AssertMessage("Registering window class failed!");
	}
}
#endif

#if defined(PROTO_PLATFORM_WIN32)
void Window::Create(DWORD a_ExStyle, LPCWSTR a_Title, int a_Width, int a_Height, HINSTANCE a_Instance)
{
	RECT adjustedWindowSize = { 0, 0, static_cast<LONG>(a_Width), static_cast<LONG>(a_Height) };
	AdjustWindowRect(&adjustedWindowSize, WS_OVERLAPPEDWINDOW, FALSE);
	m_Handle = CreateWindowEx(a_ExStyle, a_Title, a_Title, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 
		adjustedWindowSize.right - adjustedWindowSize.left,
		adjustedWindowSize.bottom - adjustedWindowSize.top,
		NULL, NULL, a_Instance, NULL);
	AssertMessage(0 != m_Handle, ("Error creating window!"));
}
#endif

#if defined(PROTO_PLATFORM_WIN32)
void Window::Destroy()
{
	DestroyWindow(m_Handle);
}
#endif

void Window::OnResize(uint32_t a_Width, uint32_t a_Height)
{
	m_WindowSize.m_Width = a_Width;
	m_WindowSize.m_Height = a_Height;
#if defined(PROTO_PLATFORM_WIN32)
	m_ClientSize = GetClientRect(m_Handle);
#else
	AssertMessage("Not implemented on this platform!");
#endif
}

END_NAMESPACE(Platform)
