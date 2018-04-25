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

	void GetHardwareAdapter(IDXGIFactory2* pFactory, IDXGIAdapter1** ppAdapter)
	{
		IDXGIAdapter1 *adapter;
		*ppAdapter = nullptr;

		for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != pFactory->EnumAdapters1(adapterIndex, &adapter); ++adapterIndex)
		{
			DXGI_ADAPTER_DESC1 desc;
			adapter->GetDesc1(&desc);

			if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
			{
				// Don't select the Basic Render Driver adapter.
				// If you want a software adapter, pass in "/warp" on the command line.
				continue;
			}

			// Check to see if the adapter supports Direct3D 12, but don't create the
			// actual device yet.
			if (SUCCEEDED(D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), 0)))
			{
				break;
			}
		}

		*ppAdapter = adapter;
	}
}

void GFXInitialize(GFXAPI *a_API, Allocator *a_Allocator, GFXAPIDescriptor *a_Descriptor)
{
	GFX_UNUSED(a_Allocator);

	DX12API *api = ALLOCATE(DX12API);
	assert(0 != api);

	UINT dxgiFactoryFlags = 0;
#if defined(_DEBUG)
	ID3D12Debug *debugController = 0;

	HRESULT result = D3D12GetDebugInterface(IID_ID3D12Debug, (void**)&debugController);
	assert(S_OK == result);
	debugController->EnableDebugLayer();
	dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
#endif

	result = CreateDXGIFactory2(dxgiFactoryFlags, IID_IDXGIFactory, (void**)&api->m_Factory);
	assert(S_OK == result);

	if (a_Descriptor->m_UseSoftwareDevice)
	{
		IDXGIAdapter *warpAdapter = 0;
		result = api->m_Factory->EnumWarpAdapter(IID_IDXGIAdapter1, (void**)&warpAdapter);
		assert(S_OK == result);

		result = D3D12CreateDevice((IUnknown*)warpAdapter, D3D_FEATURE_LEVEL_11_0, IID_ID3D12Device, (void**)&api->m_Device);
		assert(S_OK == result);
	}
	else
	{
		IDXGIAdapter1 *hardwareAdapter = 0;
		for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != api->m_Factory->EnumAdapters1(adapterIndex, &hardwareAdapter); ++adapterIndex)
		{
			DXGI_ADAPTER_DESC1 desc;
			hardwareAdapter->GetDesc1(&desc);

			if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
			{
				continue;
			}
			else
			{
				result = D3D12CreateDevice((IUnknown*)hardwareAdapter, D3D_FEATURE_LEVEL_11_0, IID_ID3D12Device, (void**)&api->m_Device);
				if (S_OK == result)
				{
					break;
				}
			}
		}
		assert(S_OK == result);
	}

	g_API = api;
	*a_API = api;
}

void GFXCreateCommandQueue(GFXAPI a_API, GFXCommandQueueDescriptor *a_Descriptor, GFXCommandQueueHandle *a_Handle)
{
	assert(0 != a_API);
	DX12API *api = (DX12API*)a_API;
	DX12CommandQueue *commandQueue = ALLOCATE(DX12CommandQueue);

	D3D12_COMMAND_QUEUE_DESC commandQueueDesc = { };
	commandQueueDesc.Flags = DX12CommandQueueFlags[a_Descriptor->m_Flags];
	commandQueueDesc.Type = DX12CommandListTypes[a_Descriptor->m_Type];

	HRESULT result = api->m_Device->CreateCommandQueue(&commandQueueDesc, IID_ID3D12CommandQueue, (void**)&commandQueue->m_CommandQueue);
#if defined(_DEBUG)
	assert(S_OK == result);
#else
	GFX_UNUSED(result);
#endif
	*a_Handle = commandQueue;
}

void GFXCreateSwapChain(GFXAPI a_API, GFXSwapChainDescriptor *a_Descriptor, GFXSwapChainHandle *a_Handle)
{
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
	assert(0 != a_API);
	DX12API *api = (DX12API *)a_API;
	assert(0 != api->m_Factory);

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
	swapChainDesc.BufferCount = a_Descriptor->m_BufferCount;
	swapChainDesc.Width = a_Descriptor->m_FrameBufferWidth;
	swapChainDesc.Height = a_Descriptor->m_FrameBufferHeight;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.SampleDesc.Count = 1;

	DX12CommandQueue *commandQueue = (DX12CommandQueue*)a_Descriptor->m_CommandQueue;
	IDXGISwapChain3 *swapChain;
	HRESULT result = api->m_Factory->CreateSwapChainForHwnd(
		commandQueue->m_CommandQueue,		// Swap chain needs the queue so that it can force a flush on it.
		api->m_WindowHandle,
		&swapChainDesc,
		nullptr,
		nullptr,
		(IDXGISwapChain1**)&swapChain
	);

#if defined(_DEBUG)
	assert(S_OK == result);
#else
	GFX_UNUSED(result);
#endif

	api->m_Factory->MakeWindowAssociation(api->m_WindowHandle, DXGI_MWA_NO_ALT_ENTER);
	api->m_CurrentBackBufferIndex = swapChain->GetCurrentBackBufferIndex();
	*a_Handle = swapChain;
}

int main(int a_ArgC, const char * a_ArgV[])
{
	UNUSED(a_ArgC);
	UNUSED(a_ArgV);

	const uint32_t windowWidth = 1280;
	const uint32_t windowHeight = 720;
	Window window(std::wstring(L"Forward rendering").c_str(), windowWidth, windowHeight);
	
// #if defined(GFX_API_VULKAN)
// 	VulkanParameters parameters = {};
// 	parameters.m_ApplicationName = "TempVulkanRenderer";
// 	parameters.m_EngineName = "Proto";
// 	parameters.m_NumEnabledExtensions = 2;
// 	const char * const extensions[] = { VK_KHR_SURFACE_EXTENSION_NAME, VK_KHR_WIN32_SURFACE_EXTENSION_NAME };
// 	parameters.m_EnabledExtensions = extensions;
// 	parameters.m_NumEnabledLayers = 1;
// 	const char * const layers[] = { "VK_LAYER_LUNARG_api_dump" };
// 	parameters.m_EnabledLayers = layers;
// #endif
// 

// 
// 
// 	GFXSwapChainDescriptor swapChainDescriptor;
// 	swapChainDescriptor.m_CommandQueue = commandQueue;
// 	swapChainDescriptor.m_FrameBufferWidth = 1280;
// 	swapChainDescriptor.m_FrameBufferHeight = 720;
// 	swapChainDescriptor.m_MSAASampleCount;
// 	swapChainDescriptor.m_MSAAQuality;
// 	swapChainDescriptor.m_BufferCount = 2;
// 	swapChainDescriptor.m_Fullscreen;
// 	swapChainDescriptor.m_VSync;
// 	swapChainDescriptor.m_EnableMSAA;
// 	GFXSwapChainHandle swapChain;
// 	GFXCreateSwapChain(g_API, &swapChainDescriptor, &swapChain);
// 
// 	GFXDestroyCommandQueue(g_API, commandQueue);
// 	//GFXDestroySwapChain(g_API, swapChain);
// 	GFXTerminate(g_API);

#if 1
	GFXAPIDescriptor descriptor { };
	descriptor.m_FrameBufferHeight = 720;
	descriptor.m_FrameBufferWidth = 1280;
	descriptor.m_WindowHandle = window.GetHandle();
	descriptor.m_UseSoftwareDevice = false;
	GFXInitialize(&g_API, nullptr, &descriptor);
	DX12API *api = (DX12API*)g_API;

	GFXCommandQueueDescriptor commandQueueDescriptor;
	commandQueueDescriptor.m_Flags = CommandQueueFlags_None;
	commandQueueDescriptor.m_Type = CommandQueueType_Direct;
	GFXCommandQueueHandle commandQueue;
	GFXCreateCommandQueue(g_API, &commandQueueDescriptor, &commandQueue);
#else
	UINT dxgiFactoryFlags = 0;

#if defined(_DEBUG)
	// Enable the debug layer (requires the Graphics Tools "optional feature").
	// NOTE: Enabling the debug layer after device creation will invalidate the active device.
	{
		ID3D12Debug *debugController;
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
		{
			debugController->EnableDebugLayer();

			// Enable additional debug layers.
			dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
		}
	}
#endif

	IDXGIFactory4 *factory;
	CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory));
	ID3D12Device *m_device;
	if (false)
	{
		IDXGIAdapter *warpAdapter;
		factory->EnumWarpAdapter(IID_PPV_ARGS(&warpAdapter));

		D3D12CreateDevice(
			warpAdapter,
			D3D_FEATURE_LEVEL_11_0,
			IID_PPV_ARGS(&m_device)
		);
	}
	else
	{
		IDXGIAdapter1 *hardwareAdapter;
		GetHardwareAdapter(factory, &hardwareAdapter);

		D3D12CreateDevice(
			hardwareAdapter,
			D3D_FEATURE_LEVEL_11_0,
			IID_PPV_ARGS(&m_device)
		);
	}

#endif
	// Describe and create the command queue.
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;

// 	ID3D12CommandQueue *m_commandQueue;
// 	api->m_Device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_commandQueue));
	ID3D12CommandQueue *m_commandQueue = ((DX12CommandQueue*)commandQueue)->m_CommandQueue;

	// Describe and create the swap chain.
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	swapChainDesc.BufferCount = 2;
	swapChainDesc.Width = 1280;
	swapChainDesc.Height = 720;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.SampleDesc.Count = 1;

	IDXGISwapChain3 *swapChain;
	api->m_Factory->CreateSwapChainForHwnd(
		m_commandQueue,		// Swap chain needs the queue so that it can force a flush on it.
		window.GetHandle(),
		&swapChainDesc,
		nullptr,
		nullptr,
		(IDXGISwapChain1**)&swapChain
	);

	// This sample does not support fullscreen transitions.
	api->m_Factory->MakeWindowAssociation(window.GetHandle(), DXGI_MWA_NO_ALT_ENTER);

	uint32_t m_frameIndex = swapChain->GetCurrentBackBufferIndex();
	UNUSED(m_frameIndex);
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

	return 0;
}
