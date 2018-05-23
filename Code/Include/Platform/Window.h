#pragma once

#include "Proto.h"
#include "EWindowState.h"
#include "Math/Dimension.h"
#include "Platform/PlatformIncludes.h"

#include <string>

BEGIN_NAMESPACE(Platform)

class IApplication;

class Window
{
public:
	Window(int a_Width, int a_Height);
	Window(const wchar_t *a_Title, uint32_t a_Width, uint32_t a_Height);
	~Window();

	void Show(EWindowState a_State);
	void Update();

	const Math::Dimension& GetSize() const;
	const Math::Dimension& GetClientRectSize() const;

	NativeWindowHandle GetHandle() const;

	void SetTitle(const std::string &a_Title);
	std::string GetTitle();
	void SetFullscreen(bool a_Fullscreen);
	void SetApplicationHandle(IApplication &a_Application);

private:
#if defined(PROTO_PLATFORM_WIN32)
	void Register(WNDCLASS &a_WindowClass);
	void Create(DWORD a_ExStyle, LPCWSTR a_Title, int a_Width, int a_Height, HINSTANCE a_Instance);
	void Destroy();
#elif defined(PROTO_PLATFORM_RASPBERRY_PI)
#endif
	void OnResize(uint32_t a_Width, uint32_t a_Height);

	NativeWindowHandle m_Handle;
	Math::Dimension m_WindowSize;
	Math::Dimension m_ClientSize;
	bool m_Fullscreen;

	friend class BaseWindowApplication;
};

END_NAMESPACE(Platform)
