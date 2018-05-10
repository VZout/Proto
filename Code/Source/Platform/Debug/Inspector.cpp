#include "Inspector.h"

#include "Graphics/API/GFX.h"
#include "Inspect.h"

#include <iostream>

#if defined(GFX_API_DX11)
extern LRESULT ImGui_ImplDX11_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif

BEGIN_NAMESPACE(Platform)

Inspector::Inspector()
{
}

Inspector::~Inspector()
{
	Terminate();
}

void Inspector::Initialize(GFXAPI a_Api, NativeWindowHandle a_WindowHandle)
{
	UNUSED(a_WindowHandle);
	UNUSED(a_Api);

#if defined(GFX_API_DX11)
	ID3D11Device *device = NULLPTR;
	ID3D11DeviceContext *deviceContext = NULLPTR;
	GetDevice(a_Api, &device);
	GetDeviceContext(a_Api, &deviceContext);
	ImGui_ImplDX11_Init(a_WindowHandle, device, deviceContext);
#elif defined(GFX_API_DX12)
#elif defined(GFX_API_OPENGL)
	ImGui_ImplGL3_Init(a_WindowHandle);
#elif defined(GFX_API_OPENGLES)
#elif defined(GFX_API_VULKAN)
#elif defined(GFX_API_ORBIS)
#endif

// 	ImGuiIO &io = ImGui::GetIO();
// 	io.DisplaySize;
// 	io.DeltaTime;
// 	io.IniSavingRate;
// 	io.IniFilename;
// 	io.LogFilename;
// 	io.MouseDoubleClickTime;
// 	io.MouseDoubleClickMaxDist;
// 	io.MouseDragThreshold;
// 	io.KeyMap[ImGuiKey_COUNT];
// 	io.KeyRepeatDelay;
// 	io.KeyRepeatRate;
// 	io.UserData;
// 	io.Fonts;
// 	io.FontGlobalScale;
// 	io.FontAllowUserScaling;
// 	io.DisplayFramebufferScale;
// 	io.DisplayVisibleMin;
// 	io.DisplayVisibleMax;

#if defined(__APPLE__)
// 	io.OSXBehaviors;
#endif
}

void Inspector::BeginFrame()
{
#if defined(GFX_API_DX11)
	ImGui_ImplDX11_NewFrame();
#elif defined(GFX_API_DX12)
#elif defined(GFX_API_OPENGL)
	ImGui_ImplGL3_NewFrame();
#elif defined(GFX_API_OPENGLES)
#elif defined(GFX_API_VULKAN)
#elif defined(GFX_API_ORBIS)
#endif
}

void Inspector::EndFrame()
{
	ImGui::Render();
}

void Inspector::Terminate()
{
#if defined(GFX_API_DX11)
	ImGui_ImplDX11_Shutdown();
#elif defined(GFX_API_DX12)
#elif defined(GFX_API_OPENGL)
	ImGui_ImplGL3_Shutdown();
#elif defined(GFX_API_OPENGLES)
#elif defined(GFX_API_VULKAN)
#elif defined(GFX_API_ORBIS)
#endif
}

#if defined(PROTO_PLATFORM_WIN32)
bool Inspector::AbsorbInput(NativeWindowHandle a_WindowHandle, UINT a_Msg, WPARAM a_WParam, LPARAM a_LParam)
{
	UNUSED(a_WindowHandle);
#if defined(GFX_API_DX11)
#elif defined(GFX_API_DX12)
#elif defined(GFX_API_OPENGL)
#elif defined(GFX_API_OPENGLES)
#elif defined(GFX_API_VULKAN)
#elif defined(GFX_API_ORBIS)
#endif
	
	ImGuiIO &io = ImGui::GetIO();
	switch (a_Msg)
	{
	case WM_MOUSEMOVE:
		io.MousePos = ImVec2(static_cast<float>(LOWORD(a_LParam)), static_cast<float>(HIWORD(a_LParam)));
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
		io.MouseDown[0] = (a_WParam & MK_LBUTTON) != 0;
		io.MouseDown[1] = (a_WParam & MK_RBUTTON) != 0;
		io.MouseDown[2] = (a_WParam & MK_MBUTTON) != 0;
		io.KeyCtrl = (a_WParam & MK_SHIFT) != 0;
		io.KeyShift = (a_WParam & MK_CONTROL) != 0;
		break;
	case WM_MOUSEWHEEL:
		io.MouseWheel = static_cast<int>(static_cast<short>(HIWORD(a_WParam))) / static_cast<float>(WHEEL_DELTA);
		break;
	case WM_KEYDOWN:
	case WM_KEYUP:
		io.KeyShift = ::GetAsyncKeyState(VK_SHIFT) > 0;
		io.KeyCtrl = ::GetAsyncKeyState(VK_CONTROL) > 0;
		io.KeyAlt = ::GetAsyncKeyState(VK_MENU) > 0;
		io.KeySuper = ::GetAsyncKeyState(VK_LWIN) > 0;
		//io.KeysDown[512];
		break;
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
		io.KeyShift = ::GetAsyncKeyState(VK_SHIFT) > 0;
		io.KeyCtrl = ::GetAsyncKeyState(VK_CONTROL) > 0;
		io.KeyAlt = ::GetAsyncKeyState(VK_MENU) > 0;
		io.KeySuper = ::GetAsyncKeyState(VK_LWIN) > 0;
		break;
	default:
		break;
	}

	return io.WantCaptureMouse;
}
#endif

END_NAMESPACE(Platform)
