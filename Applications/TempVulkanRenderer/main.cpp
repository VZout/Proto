#include "Proto.h"

#include "Graphics/API/GFX.h"

#include "Graphics/API/DX12/DX12Includes.h"
#include "Graphics/API/DX12/DX12Structs.h"
#include "Graphics/API/DX12/DX12Translators.h"
#include "Graphics/API/DX12/Helpers/SafeRelease.h"
#include "Platform/Window.h"

#include <assert.h>

#include "Platform/Debug/AssertMessage.h"

#include <iostream>
#include <string>
#include <vector>

USING_NAMESPACE(Platform)

namespace
{
	GFXAPI g_API;
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
	commandQueueDescriptor.m_Type = CommandQueueType_Direct;
	GFXCommandQueueHandle commandQueue;
	GFXCreateCommandQueue(g_API, &commandQueueDescriptor, &commandQueue);

	GFXSwapChainDescriptor swapChainDescriptor;
	swapChainDescriptor.m_CommandQueue = commandQueue;
	swapChainDescriptor.m_FrameBufferWidth = 1280;
	swapChainDescriptor.m_FrameBufferHeight = 720;
	swapChainDescriptor.m_MSAASampleCount;
	swapChainDescriptor.m_MSAAQuality;
	swapChainDescriptor.m_BufferCount = 2;
	swapChainDescriptor.m_Fullscreen;
	swapChainDescriptor.m_VSync;
	swapChainDescriptor.m_EnableMSAA;
	GFXSwapChainHandle swapChain;
	GFXCreateSwapChain(g_API, &swapChainDescriptor, &swapChain);

	// 	// Create descriptor heaps.
// 	{
// 		// Describe and create a render target view (RTV) descriptor heap.
// 		D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
// 		rtvHeapDesc.NumDescriptors = FrameCount;
// 		rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
// 		rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
// 		ThrowIfFailed(api->m_Device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&m_rtvHeap)));
// 
// 		m_rtvDescriptorSize = api->m_Device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
// 	}
// 
// 	// Create frame resources.
// 	{
// 		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart());
// 
// 		// Create a RTV for each frame.
// 		for (UINT n = 0; n < FrameCount; n++)
// 		{
// 			ThrowIfFailed(m_swapChain->GetBuffer(n, IID_PPV_ARGS(&m_renderTargets[n])));
// 			api->m_Device->CreateRenderTargetView(m_renderTargets[n].Get(), nullptr, rtvHandle);
// 			rtvHandle.Offset(1, m_rtvDescriptorSize);
// 		}
// 	}
// 
// 	ThrowIfFailed(api->m_Device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_commandAllocator)));

	GFXDestroyCommandQueue(g_API, commandQueue);
	GFXDestroySwapChain(g_API, swapChain);
	GFXTerminate(g_API);

	return 0;
}
