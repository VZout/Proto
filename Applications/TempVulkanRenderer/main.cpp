#include "Proto.h"

#include "Graphics/API/GFX.h"

#include "Graphics/API/DX12/DX12Includes.h"
#include "Graphics/API/DX12/DX12Structs.h"
#include "Graphics/API/DX12/DX12Translators.h"
#include "Graphics/API/DX12/Helpers/SafeRelease.h"
#include "Platform/Window.h"

#include <assert.h>

#include "Platform/Debug/AssertMessage.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#pragma comment(lib, "winmm")

USING_NAMESPACE(Platform)

namespace
{
	GFXAPI g_API;
	GFXSwapChainHandle g_SwapChain;
	GFXCommandQueueHandle g_CommandQueue;
	GFXCommandListHandle g_CommandList;
	GFXRenderTargetHandle g_RenderTarget;
}

void PopulateCommandList()
{
	GFXStartRecordingCommandList(g_API, g_CommandList);
	GFXPrepareRenderTargetForDraw(g_API, g_CommandList, g_RenderTarget);

	GFXColor clearColor = { 0.0f, 0.2f, 0.4f, 1.0f };
	GFXClearRenderTarget(g_API, g_CommandList, g_RenderTarget, clearColor);

	GFXPrepareRenderTargetForPresent(g_API, g_CommandList, g_RenderTarget);
	GFXStopRecordingCommandList(g_API, g_CommandList);
}

void update()
{
	PopulateCommandList();
}

void render()
{
	GFXExecuteCommandList(g_API, g_CommandList, g_CommandQueue);
	GFXPresent(g_API, g_SwapChain);
}

void waitForFrameEnd()
{
// 	// Signal and increment the fence value.
// 	const UINT64 fence = m_fenceValue;
// 	ThrowIfFailed(m_commandQueue->Signal(m_fence.Get(), fence));
// 	m_fenceValue++;
// 
// 	// Wait until the previous frame is finished.
// 	if (m_fence->GetCompletedValue() < fence)
// 	{
// 		ThrowIfFailed(m_fence->SetEventOnCompletion(fence, m_fenceEvent));
// 		WaitForSingleObject(m_fenceEvent, INFINITE);
// 	}
// 
// 	m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();
}

int main(int a_ArgC, const char * a_ArgV[])
{
	UNUSED(a_ArgC);
	UNUSED(a_ArgV);

	const uint32_t windowWidth = 1280;
	const uint32_t windowHeight = 720;
	Window window(std::wstring(L"Forward rendering").c_str(), windowWidth, windowHeight);
	
#if defined(GFX_API_VULKAN)
	VulkanParameters parameters = {};
	parameters.m_ApplicationName = "TempVulkanRenderer";
	parameters.m_EngineName = "Proto";
	parameters.m_NumEnabledExtensions = 2;
	const char * const extensions[] = { VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME };
	parameters.m_EnabledExtensions = extensions;
	parameters.m_NumEnabledLayers = 1;
	const char * const layers[] = { "VK_LAYER_LUNARG_api_dump" };
	parameters.m_EnabledLayers = layers;
#endif

	GFXAPIDescriptor descriptor { };
	descriptor.m_FrameBufferHeight = 720;
	descriptor.m_FrameBufferWidth = 1280;
	descriptor.m_WindowHandle = window.GetHandle();
	descriptor.m_UseSoftwareDevice = false;
	GFXInitialize(&g_API, nullptr, &descriptor);

	GFXCommandQueueDescriptor commandQueueDescriptor;
	commandQueueDescriptor.m_Flags = CommandQueueFlags_None;
	commandQueueDescriptor.m_Type = CommandListType_Direct;
	GFXCreateCommandQueue(g_API, &commandQueueDescriptor, &g_CommandQueue);

	GFXSwapChainDescriptor swapChainDescriptor;
	swapChainDescriptor.m_CommandQueue = g_CommandQueue;
	swapChainDescriptor.m_FrameBufferWidth = 1280;
	swapChainDescriptor.m_FrameBufferHeight = 720;
// 	swapChainDescriptor.m_EnableMSAA;
// 	swapChainDescriptor.m_MSAASampleCount;
// 	swapChainDescriptor.m_MSAAQuality;
	swapChainDescriptor.m_BufferCount = 2;
	swapChainDescriptor.m_Fullscreen = false;
	swapChainDescriptor.m_VSync = false;
	GFXCreateSwapChain(g_API, &swapChainDescriptor, &g_SwapChain);

	GFXRenderTargetDescriptor renderTargetDescriptor;
	renderTargetDescriptor.m_SwapChain = g_SwapChain;
	GFXCreateRenderTarget(g_API, &renderTargetDescriptor, &g_RenderTarget);

	GFXCommandListDescriptor commandListDescriptor;
	commandListDescriptor.m_Type = CommandListType_Direct;
	GFXCreateCommandList(g_API, &commandListDescriptor, &g_CommandList);

	HANDLE fenceEventHandle = CreateEvent(nullptr, false, false, nullptr);
	UNUSED(fenceEventHandle);

	MSG msg = { 0 };

	static DWORD previousTime = timeGetTime();
	static float totalTime = 0.0f;
	static const float targetFramerate = 30.0f;
	static const float maxTimeStep = 1.0f / targetFramerate;

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			DWORD currentTime = timeGetTime();
			float deltaTime = (currentTime - previousTime) / 1000.0f;
			previousTime = currentTime;

			deltaTime = std::min<float>(deltaTime, maxTimeStep);
			totalTime += deltaTime;

			//UpdateEventArgs updateEventArgs(deltaTime, totalTime);
			//RenderEventArgs renderEventArgs(deltaTime, totalTime);

			update();
			render();

			waitForFrameEnd();
		}
	}

	GFXDestroyCommandList(g_API, g_CommandList);
	GFXDestroyRenderTarget(g_API, g_RenderTarget);
	GFXDestroySwapChain(g_API, g_SwapChain);
	GFXDestroyCommandQueue(g_API, g_CommandQueue);
	GFXTerminate(g_API);

	return static_cast<int>(msg.wParam);
}
