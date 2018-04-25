#include "Graphics/API/GFX.h"

#include "Graphics/API/DX12/DX12Includes.h"
#include "Graphics/API/DX12/DX12Structs.h"
#include "Graphics/API/DX12/DX12Translators.h"
#include "Graphics/API/DX12/Helpers/SafeRelease.h"

#include <assert.h>

#if defined(GFX_API_DX12)

GFXAPI g_API = 0;

// void GFXInitialize(GFXAPI *a_API, Allocator *a_Allocator, GFXAPIDescriptor *a_Descriptor)
// {
// 	GFX_UNUSED(a_Allocator);
// 
// 	DX12API *api = ALLOCATE(DX12API);
// 	assert(0 != api);
// 
// 	UINT dxgiFactoryFlags = 0;
// #if defined(_DEBUG)
// 	ID3D12Debug *debugController = 0;
// 	
// 	HRESULT result = D3D12GetDebugInterface(&IID_ID3D12Debug, &debugController);
// 	assert(S_OK == result);
// 	debugController->lpVtbl->EnableDebugLayer(debugController);
// 	dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
// #endif
// 
// 	result = CreateDXGIFactory2(dxgiFactoryFlags, &IID_IDXGIFactory, (void**)&api->m_Factory);
// 	assert(S_OK == result);
// 
// 	if (a_Descriptor->m_UseSoftwareDevice)
// 	{
// 		IDXGIAdapter *warpAdapter = 0;
// 		result = api->m_Factory->lpVtbl->EnumWarpAdapter(api->m_Factory, &IID_IDXGIAdapter1, (void**)&warpAdapter);
// 		assert(S_OK == result);
// 
// 		result = D3D12CreateDevice((IUnknown*)warpAdapter, D3D_FEATURE_LEVEL_11_0, &IID_ID3D12Device, (void**)&api->m_Device);
// 		assert(S_OK == result);
// 	}
// 	else
// 	{
// 		IDXGIAdapter1 *hardwareAdapter = 0;
// 		for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != api->m_Factory->lpVtbl->EnumAdapters1(api->m_Factory, adapterIndex, &hardwareAdapter); ++adapterIndex)
// 		{
// 			DXGI_ADAPTER_DESC1 desc;
// 			hardwareAdapter->lpVtbl->GetDesc1(hardwareAdapter, &desc);
// 
// 			if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
// 			{
// 				continue;
// 			}
// 			else
// 			{
// 				result = D3D12CreateDevice((IUnknown*)hardwareAdapter, D3D_FEATURE_LEVEL_11_0, &IID_ID3D12Device, (void**)&api->m_Device);
// 				if (S_OK == result)
// 				{
// 					break;
// 				}
// 			}
// 		}
// 		assert(S_OK == result);
// 	}
// 
// 	g_API = api;
// 	*a_API = api;
// }

void GFXTerminate(GFXAPI a_API)
{
	GFX_UNUSED(a_API);
}

void GFXCreateViewport(GFXAPI a_API, GFXViewportDescriptor *a_Descriptor, GFXViewportHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXDestroyViewport(GFXAPI a_API, GFXViewportHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

// void GFXCreateSwapChain(GFXAPI a_API, GFXSwapChainDescriptor *a_Descriptor, GFXSwapChainHandle *a_Handle)
// {
// 	GFX_UNUSED(a_Descriptor);
// 	GFX_UNUSED(a_Handle);
// 	assert(0 != a_API);
// 	DX12API *api = a_API;
// 	assert(0 != api->m_Factory);
// 
// // 	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
// // 	swapChainDesc.BufferCount = a_Descriptor->m_BufferCount;
// // 	swapChainDesc.Width = a_Descriptor->m_FrameBufferWidth;
// // 	swapChainDesc.Height = a_Descriptor->m_FrameBufferHeight;
// // 	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
// // 	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
// // 	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
// // 	swapChainDesc.SampleDesc.Count = 1;
// 
// // 	IDXGISwapChain3 *swapChain = 0;
// // 	IDXGIFactory4 *factory = api->m_Factory;
// // 	HRESULT result = factory->lpVtbl->CreateSwapChainForHwnd(factory, (IUnknown*)api->m_Device, api->m_WindowHandle, &swapChainDesc, 0, 0, (IDXGISwapChain1**)&swapChain);
// // #if defined(_DEBUG)
// // 	assert(S_OK == result);
// // #else
// // 	GFX_UNUSED(result);
// // #endif
// 
// // 	api->m_Factory->lpVtbl->MakeWindowAssociation(api->m_Factory, api->m_WindowHandle, DXGI_MWA_NO_ALT_ENTER);
// // 	api->m_CurrentBackBufferIndex = swapChain->lpVtbl->GetCurrentBackBufferIndex(swapChain);
// // 	*a_Handle = swapChain;
// }

void GFXDestroySwapChain(GFXAPI a_API, GFXSwapChainHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_Handle);
	DX12SwapChain *swapChain = a_Handle;
	SAFERELEASE(swapChain->m_SwapChain);
	DEALLOCATE(swapChain);
}

void GFXClearRenderTarget(GFXAPI a_API, GFXRenderTargetHandle a_RenderTarget, GFXColor a_ClearColor)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_RenderTarget);
	GFX_UNUSED(a_ClearColor);
}

void GFXPresent(GFXAPI a_API, GFXSwapChainHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXCreateVertexBuffer(GFXAPI a_API, GFXVertexBufferDescriptor *a_Descriptor, GFXVertexBufferHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXDestroyVertexBuffer(GFXAPI a_API, GFXVertexBufferHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXCreateIndexBuffer(GFXAPI a_API, GFXIndexBufferDescriptor *a_Descriptor, GFXIndexBufferHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXDestroyIndexBuffer(GFXAPI a_API, GFXIndexBufferHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXCreateTexture(GFXAPI a_API, GFXTextureDescriptor *a_Descriptor, GFXTextureHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXDestroyTexture(GFXAPI a_API, GFXTextureHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}


void GFXCreateShader(GFXAPI a_API, GFXShaderDescriptor *a_Descriptor, GFXShaderHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXDestroyShader(GFXAPI a_API, GFXShaderHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXCreateInputLayout(GFXAPI a_API, GFXInputLayoutDescriptor *a_Descriptor, GFXInputLayoutHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXDestroyInputLayout(GFXAPI a_API, GFXInputLayoutHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXCreateConstantBuffer(GFXAPI a_API, GFXConstantBufferDescriptor *a_Descriptor, GFXConstantBufferHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXCopyConstantBufferData(GFXAPI a_API, GFXConstantBufferHandle a_Handle, const char *a_VariableName, const void *a_Data)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
	GFX_UNUSED(a_VariableName);
	GFX_UNUSED(a_Data);
}

void GFXDestroyConstantBuffer(GFXAPI a_API, GFXConstantBufferHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXCreateResource(GFXAPI a_API, GFXResourceDescriptor *a_Descriptor, GFXResourceHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXDestroyResource(GFXAPI a_API, GFXResourceHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXDrawIndexed(GFXAPI a_API, GFXCommandListHandle a_Handle, uint32_t a_NumVertices)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
	GFX_UNUSED(a_NumVertices);
}

// void GFXCreateCommandQueue(GFXAPI a_API, GFXCommandQueueDescriptor *a_Descriptor, GFXCommandQueueHandle *a_Handle)
// {
// 	assert(0 != a_API);
// 	DX12API *api = a_API;
// 	DX12CommandQueue *commandQueue = ALLOCATE(DX12CommandQueue);
// 
// 	ID3D12CommandQueue *iCommandQueue;
// 	D3D12_COMMAND_QUEUE_DESC commandQueueDesc = { 0 };
// 	commandQueueDesc.Flags = DX12CommandQueueFlags[a_Descriptor->m_Flags];
// 	commandQueueDesc.Type = DX12CommandListTypes[a_Descriptor->m_Type];
// 
// 	HRESULT result = api->m_Device->lpVtbl->CreateCommandQueue(api->m_Device, &commandQueueDesc, &IID_ID3D12CommandQueue, (void**)&iCommandQueue);
// #if defined(_DEBUG)
// 	assert(S_OK == result);
// #else
// 	GFX_UNUSED(result);
// #endif
// 	*a_Handle = commandQueue;
// 
// 	{
// 		DXGI_SWAP_CHAIN_DESC1 desc = {0};
// 
// 		desc.BufferCount = 2;
// 		desc.Width = 1280;
// 		desc.Height = 720;
// 		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
// 		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
// 		desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
// 		desc.SampleDesc.Count = 1;
// 
// 		IDXGISwapChain1* swapChain = 0;
// 		assert(api->m_Factory != 0);
// 		result = api->m_Factory->lpVtbl->CreateSwapChainForHwnd(
// 			api->m_Factory,
// 			(IUnknown*)iCommandQueue,
// 			api->m_WindowHandle,
// 			&desc,
// 			0,
// 			0,
// 			&swapChain);
// 		assert(S_OK == result);
// 	}
// }

void GFXDestroyCommandQueue(GFXAPI a_API, GFXCommandQueueHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_Handle);
	DX12CommandQueue *commandQueue = a_Handle;
	SAFERELEASE(commandQueue->m_CommandQueue);
	DEALLOCATE(commandQueue);
}

void GFXCreateCommandList(GFXAPI a_API, GFXCommandListDescriptor *a_Descriptor, GFXCommandListHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXUpdateCommandList(GFXAPI a_API, GFXCommandListDescriptor *a_Descriptor, GFXCommandListHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXDestroyCommandList(GFXAPI a_API, GFXCommandListHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXCreatePipelineStateObject(GFXAPI a_API, GFXPipelineStateObjectDescriptor *a_Descriptor, GFXPipelineStateObjectHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXSetPipelineStateObject(GFXAPI a_API, GFXPipelineStateObjectHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXDestroyPipelineStateObject(GFXAPI a_API, GFXPipelineStateObjectHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

#endif
