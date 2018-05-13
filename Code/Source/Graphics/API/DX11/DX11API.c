#include "Graphics/API/GFX.h"

#include "Graphics/API/DX11/DX11API.h"
#include "Graphics/API/DX11/DX11Structs.h"
#include "Graphics/API/DX11/DX11Translators.h"
#include "Graphics/API/DX11/Helpers/DetermineAdapterSettings.h"
#include "Graphics/API/DX11/Helpers/InspectVertexShader.h"
#include "Graphics/API/DX11/Helpers/SafeRelease.h"
#include "Graphics/API/DX11/Helpers/SetDebugName.h"
#include "Graphics/API/Helpers/TransposeData.h"

#include <assert.h>
#include <stdio.h>

#if defined(GFX_API_DX11)

GFXAPI g_API = 0;

D3D11_CULL_MODE DetermineCullMode(GFXHandedness a_Handedness)
{
	return Handedness_Left == a_Handedness ? D3D11_CULL_FRONT : D3D11_CULL_BACK;
}

void GFXGetBaseAPIName(char *a_ApiName)
{
	sprintf_s(a_ApiName, 16, "DirectX 11.0\0");
}

char* GFXGetBaseAPICode()
{
	return "dx11";
}

GFXAPI GetAPI()
{
	assert(0 != g_API);
	return g_API;
}

void GetDevice(GFXAPI a_API, ID3D11Device **a_Device)
{
	assert(0 != a_API);
	DX11API *api = a_API;
	*a_Device = api->m_Device;
}

void GetDeviceContext(GFXAPI a_API, ID3D11DeviceContext **a_DeviceContext)
{
	assert(0 != a_API);
	DX11API *api = a_API;
	*a_DeviceContext = api->m_DeviceContext;
}

void GFXInitialize(GFXAPI *a_API, Allocator *a_Allocator, GFXAPIDescriptor *a_Descriptor)
//void GFXInitialize(GFXAPI *a_API, Allocator *a_Allocator, GFXAPIDescriptor *a_Descriptor, GFXParameterHandle a_Parameters)
{
	GFX_UNUSED(a_Allocator);
	//GFX_UNUSED(a_Parameters);

	DX11API *api = ALLOCATE(DX11API);
	assert(0 != api);
	DetermineAdapterSettings(a_Descriptor->m_FrameBufferWidth, a_Descriptor->m_FrameBufferHeight, &api->m_RefreshRateNumerator, &api->m_RefreshRateDenominator, &api->m_VideoCardMemory, &api->m_VideoCardDescription);

	uint32_t deviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#if !defined(NDEBUG)
	deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	HRESULT result = D3D11CreateDevice(0,
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		deviceFlags,
		0, 0,
		D3D11_SDK_VERSION,
		&api->m_Device,
		&api->m_FeatureLevel,
		&api->m_DeviceContext);
#if !defined(NDEBUG)
	assert(S_OK == result);
#else
	GFX_UNUSED(result);
#endif

#if !defined(NDEBUG)
	SETDEBUGNAME(api->m_Device, "DX11Device");
	SETDEBUGNAME(api->m_DeviceContext, "DX11DeviceContext");
#endif

#if !defined(NDEBUG)
	result = api->m_Device->lpVtbl->QueryInterface(api->m_Device, &IID_ID3D11Debug, (void**)&api->m_DebugDevice);
	assert(S_OK == result);
	result = api->m_DebugDevice->lpVtbl->QueryInterface(api->m_DebugDevice, &IID_ID3D11InfoQueue, (void**)&api->m_InfoQueue);
	assert(S_OK == result);
	api->m_InfoQueue->lpVtbl->SetBreakOnCategory(api->m_InfoQueue, D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
	api->m_InfoQueue->lpVtbl->SetBreakOnCategory(api->m_InfoQueue, D3D11_MESSAGE_SEVERITY_ERROR, true);
#endif
	api->m_WindowHandle = a_Descriptor->m_WindowHandle;

	g_API = api;
	*a_API = api;
}

void GFXTerminate(GFXAPI a_API)
{
	assert(0 != a_API);
	DX11API *api = a_API;

	free(api->m_VideoCardDescription);
#if !defined(NDEBUG)
	api->m_DebugDevice->lpVtbl->ReportLiveDeviceObjects(api->m_DebugDevice, D3D11_RLDO_IGNORE_INTERNAL);
	SAFERELEASE(api->m_InfoQueue);
	SAFERELEASE(api->m_DebugDevice);
#endif
	SAFERELEASE(api->m_DeviceContext);
	SAFERELEASE(api->m_Device);
	DEALLOCATE(api);
}

void GFXCreateViewport(GFXAPI a_API, GFXViewportDescriptor *a_Descriptor, GFXViewportHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	DX11Viewport *viewport = ALLOCATE(DX11Viewport);
	assert(0 != viewport);
	viewport->m_Viewport = ALLOCATE(D3D11_VIEWPORT);
	assert(0 != viewport->m_Viewport);

	viewport->m_Viewport->Width = (float)a_Descriptor->m_Width;
	viewport->m_Viewport->Height = (float)a_Descriptor->m_Height;
	viewport->m_Viewport->MinDepth = 0.0f;
	viewport->m_Viewport->MaxDepth = 1.0f;
	viewport->m_Viewport->TopLeftX = (float)a_Descriptor->m_X;
	viewport->m_Viewport->TopLeftY = (float)a_Descriptor->m_Y;
	*a_Handle = viewport;
}

void GFXDestroyViewport(GFXAPI a_API, GFXViewportHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_API);
	DX11Viewport *viewport = a_Handle;
	DEALLOCATE(viewport->m_Viewport);
	DEALLOCATE(viewport);
}

void GFXCreateSwapChain(GFXAPI a_API, GFXSwapChainDescriptor *a_Descriptor, GFXSwapChainHandle *a_Handle)
{
	assert(0 != a_API);
	DX11API *api = a_API;
	assert(0 != api->m_Device);

	DXGI_SWAP_CHAIN_DESC swapChainDescription;
	swapChainDescription.BufferDesc.Width = a_Descriptor->m_FrameBufferWidth;
	swapChainDescription.BufferDesc.Height = a_Descriptor->m_FrameBufferHeight;
	if (a_Descriptor->m_VSync)
	{
		swapChainDescription.BufferDesc.RefreshRate.Numerator = api->m_RefreshRateNumerator;
		swapChainDescription.BufferDesc.RefreshRate.Denominator = api->m_RefreshRateDenominator;
	}
	else
	{
		swapChainDescription.BufferDesc.RefreshRate.Numerator = 0;
		swapChainDescription.BufferDesc.RefreshRate.Denominator = 1;
	}
	swapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDescription.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	if (a_Descriptor->m_EnableMSAA)
	{
		swapChainDescription.SampleDesc.Count = a_Descriptor->m_MSAASampleCount;
		swapChainDescription.SampleDesc.Quality = a_Descriptor->m_MSAAQuality - 1;
	}
	else
	{
		swapChainDescription.SampleDesc.Count = 1;
		swapChainDescription.SampleDesc.Quality = 0;
	}
	swapChainDescription.BufferUsage = DXGI_USAGE_BACK_BUFFER | DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDescription.BufferCount = a_Descriptor->m_BufferCount;
	swapChainDescription.OutputWindow = api->m_WindowHandle;
	swapChainDescription.Windowed = !a_Descriptor->m_Fullscreen;
	swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDescription.Flags = 0;

	IDXGIDevice *device = 0;
	HRESULT result = api->m_Device->lpVtbl->QueryInterface(api->m_Device, &IID_IDXGIDevice, (void**)&device);
	assert(S_OK == result);

	IDXGIAdapter *adapter = 0;
	result = device->lpVtbl->GetParent(device, &IID_IDXGIAdapter, (void**)&adapter);
	assert(S_OK == result);

	IDXGIFactory *factory = 0;
	result = adapter->lpVtbl->GetParent(adapter, &IID_IDXGIFactory, (void**)&factory);
	assert(S_OK == result);

	result = factory->lpVtbl->CreateSwapChain(factory, (IUnknown*)api->m_Device, &swapChainDescription, &api->m_SwapChain);
	assert(S_OK == result);
#if !defined(NDEBUG)
	SETDEBUGNAME(api->m_SwapChain, "DX11SwapChain");
#endif
	DX11SwapChain *swapChain = ALLOCATE(DX11SwapChain);
	assert(0 != swapChain);
	swapChain->m_SwapChain = api->m_SwapChain;
	swapChain->m_VSyncEnabled = a_Descriptor->m_VSync;
	*a_Handle = swapChain;

	SAFERELEASE(device);
	SAFERELEASE(adapter);
	SAFERELEASE(factory);
}

void GFXDestroySwapChain(GFXAPI a_API, GFXSwapChainHandle a_Handle)
{
	assert(0 != a_API);
	assert(0 != a_Handle);
	DX11API *api = a_API;
	DX11SwapChain *swapChain = a_Handle;
	SAFERELEASE(swapChain->m_SwapChain);	// is this correct; holding two handles so I need to release twice, right?
	SAFERELEASE(api->m_SwapChain);
	DEALLOCATE(swapChain);
}

void GFXCreateRenderTarget(GFXAPI a_API, GFXRenderTargetDescriptor *a_Descriptor, GFXRenderTargetHandle *a_Handle)
{
	assert(0 != a_API);
	DX11API *api = a_API;
	assert(0 != api->m_SwapChain);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);

	DX11RenderTarget *renderTarget = ALLOCATE(DX11RenderTarget);

	ID3D11Texture2D* backBuffer;
	HRESULT result = api->m_SwapChain->lpVtbl->GetBuffer(api->m_SwapChain, 0, &IID_ID3D11Texture2D, (void**)&backBuffer);
	assert(S_OK == result);

	result = api->m_Device->lpVtbl->CreateRenderTargetView(api->m_Device, (ID3D11Resource*)backBuffer, NULL, &renderTarget->m_RenderTargetView);
	assert(S_OK == result);
	SAFERELEASE(backBuffer);

	GFXTextureDescriptor depthBufferDescriptor = { 0 };
	depthBufferDescriptor.m_Format = TextureFormat_DepthStencilR24G8Typeless;
	depthBufferDescriptor.m_ShaderResourceViewFormat = TextureFormat_DepthStencilR24G8;
	depthBufferDescriptor.m_Width = a_Descriptor->m_Width;
	depthBufferDescriptor.m_Height = a_Descriptor->m_Height;
#if !defined(NDEBUG)
	depthBufferDescriptor.m_DebugName = "DX11DepthStencilBuffer";
#endif
	depthBufferDescriptor.m_DepthStencil = true;
	GFXCreateTexture(a_API, &depthBufferDescriptor, &renderTarget->m_DepthStencilBuffer);

	GFXDepthStencilStateDescriptor depthStencilStateDescriptor;
	depthStencilStateDescriptor.m_DepthEnabled = true;
#if !defined(NDEBUG)
	depthStencilStateDescriptor.m_DebugName = "DX11DefaultDepthStencilState";
#endif
	GFXCreateDepthStencilState(a_API, &depthStencilStateDescriptor, &renderTarget->m_DepthStencilState);

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = { 0 };
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	result = api->m_Device->lpVtbl->CreateDepthStencilView(api->m_Device, (ID3D11Resource*)((DX11Texture*)renderTarget->m_DepthStencilBuffer)->m_Texture, &depthStencilViewDesc, &renderTarget->m_DepthStencilView);
	assert(S_OK == result);
#if !defined(NDEBUG)
	SETDEBUGNAME(renderTarget->m_DepthStencilView, "DX11DepthStencilView");
#endif
	*a_Handle = renderTarget;
}

void GFXDestroyRenderTarget(GFXAPI a_API, GFXRenderTargetHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_Handle);
	DX11RenderTarget *renderTarget = a_Handle;

	GFXDestroyTexture(a_API, renderTarget->m_DepthStencilBuffer);
	GFXDestroyDepthStencilState(a_API, renderTarget->m_DepthStencilState);

	SAFERELEASE(renderTarget->m_DepthStencilView);
	SAFERELEASE(renderTarget->m_RenderTargetView);
	DEALLOCATE(renderTarget);
}

void GFXCreateRasterizerState(GFXAPI a_API, GFXRasterizerStateDescriptor *a_Descriptor, GFXRasterizerStateHandle *a_Handle)
{
	assert(0 != a_API);
	DX11API *api = a_API;

	D3D11_RASTERIZER_DESC rasterDesc;
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = DetermineCullMode(a_Descriptor->m_Handedness);
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = TranslateFillMode(a_Descriptor->m_FillMode);
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	DX11RasterizerState *rasterizerState = ALLOCATE(DX11RasterizerState);
	HRESULT result = api->m_Device->lpVtbl->CreateRasterizerState(api->m_Device, &rasterDesc, &rasterizerState->m_RasterizerState);
#if !defined(NDEBUG)
	assert(S_OK == result);
#else
	GFX_UNUSED(result);
#endif
	*a_Handle = rasterizerState;
}

void GFXDestroyRasterizerState(GFXAPI a_API, GFXRasterizerStateHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_Handle);
	DX11RasterizerState *rasterizerState = a_Handle;
	SAFERELEASE(rasterizerState->m_RasterizerState);
	DEALLOCATE(rasterizerState);
}

void GFXCreateBlendState(GFXAPI a_API, GFXBlendStateDescriptor *a_Descriptor, GFXBlendStateHandle *a_Handle)
{
	GFX_UNUSED(a_Descriptor);
	assert(0 != a_API);
	DX11API *api = a_API;

	DX11BlendState *blendState = ALLOCATE(DX11BlendState);
	memset(blendState, 0, sizeof(DX11BlendState));
	memcpy(blendState->m_Factor, a_Descriptor->m_Factor, 4 * sizeof(float));
	blendState->m_SampleMask = a_Descriptor->m_SampleMask;

	D3D11_BLEND_DESC blendStateDesc = { 0 };
	blendStateDesc.RenderTarget[0].BlendEnable = TRUE;
	blendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	blendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	blendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendStateDesc.RenderTarget[0].RenderTargetWriteMask = 0x0F;

	HRESULT result = api->m_Device->lpVtbl->CreateBlendState(api->m_Device, &blendStateDesc, &blendState->m_BlendState);
#if !defined(NDEBUG)
	assert(S_OK == result);
#else
	GFX_UNUSED(result);
#endif
	*a_Handle = blendState;
}

void GFXDestroyBlendState(GFXAPI a_API, GFXBlendStateHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_Handle);
	DX11BlendState *blendState = a_Handle;
	SAFERELEASE(blendState->m_BlendState);
	DEALLOCATE(blendState);
}

void GFXClearRenderTarget(GFXAPI a_API, GFXCommandListHandle a_CommandListHandle, GFXRenderTargetHandle a_RenderTargetHandle, const GFXColor a_ClearColor)
//void GFXClearRenderTarget(GFXAPI a_API, GFXRenderTargetHandle a_RenderTarget, GFXColor a_ClearColor)
{
	GFX_UNUSED(a_CommandListHandle);
	assert(0 != a_API);
	DX11API *api = a_API;
	assert(0 != a_RenderTargetHandle);
	DX11RenderTarget *renderTarget = a_RenderTargetHandle;

	float color[4];
	memcpy(color, &a_ClearColor, 4 * sizeof(float));
	api->m_DeviceContext->lpVtbl->ClearRenderTargetView(api->m_DeviceContext, renderTarget->m_RenderTargetView, color);
	api->m_DeviceContext->lpVtbl->ClearDepthStencilView(api->m_DeviceContext, renderTarget->m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void GFXPresent(GFXAPI a_API, GFXSwapChainHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_Handle);

	DX11SwapChain *swapChain = a_Handle;
	const uint32_t syncInterval = swapChain->m_VSyncEnabled ? 1 : 0;
	const uint32_t flag = 0;
	swapChain->m_SwapChain->lpVtbl->Present(swapChain->m_SwapChain, syncInterval, flag);
}

void GFXCreateVertexBuffer(GFXAPI a_API, GFXVertexBufferDescriptor *a_Descriptor, GFXVertexBufferHandle *a_Handle)
{
	assert(0 != a_API);
	DX11API *api = a_API;
	assert(0 != api->m_Device);

	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = TranslateUsage(a_Descriptor->m_Usage);
	bufferDesc.ByteWidth = (uint32_t)a_Descriptor->m_DataByteSize;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// PROTODO: determine the right cpu access flags
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	DX11VertexBuffer *vertexBuffer = ALLOCATE(DX11VertexBuffer);
	HRESULT result = S_FALSE;
	if (0 == a_Descriptor->m_Vertices)
	{
		result = api->m_Device->lpVtbl->CreateBuffer(api->m_Device, &bufferDesc, 0, &vertexBuffer->m_Buffer);
	}
	else
	{
		D3D11_SUBRESOURCE_DATA subResourceData;
		subResourceData.pSysMem = a_Descriptor->m_Vertices;
		subResourceData.SysMemPitch = 0;
		subResourceData.SysMemSlicePitch = 0;

		result = api->m_Device->lpVtbl->CreateBuffer(api->m_Device, &bufferDesc, &subResourceData, &vertexBuffer->m_Buffer);
	}
#if !defined(NDEBUG)
	assert(S_OK == result);
#else
	GFX_UNUSED(result);
#endif
	*a_Handle = vertexBuffer;
}

void GFXUpdateVertexBuffer(GFXAPI a_API, GFXVertexBufferDescriptor *a_Descriptor, GFXVertexBufferHandle a_Handle)
{
	GFX_UNUSED(a_Descriptor);
	assert(0 != a_API);
	DX11API *api = a_API;
	assert(0 != api->m_DeviceContext);

	assert(0 != a_Handle);
	DX11VertexBuffer *vertexBuffer = a_Handle;

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	const UINT subresource = 0;
	api->m_DeviceContext->lpVtbl->Map(api->m_DeviceContext, (ID3D11Resource*)vertexBuffer->m_Buffer, 0, D3D11_MAP_WRITE_DISCARD, subresource, &mappedResource);
	memcpy(mappedResource.pData, a_Descriptor->m_Vertices, a_Descriptor->m_DataByteSize);
	api->m_DeviceContext->lpVtbl->Unmap(api->m_DeviceContext, (ID3D11Resource*)vertexBuffer->m_Buffer, subresource);
}

void GFXDestroyVertexBuffer(GFXAPI a_API, GFXVertexBufferHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_Handle);
	DX11VertexBuffer *vertexBuffer = a_Handle;
	SAFERELEASE(vertexBuffer->m_Buffer);
	DEALLOCATE(vertexBuffer);
}

void GFXCreateIndexBuffer(GFXAPI a_API, GFXIndexBufferDescriptor *a_Descriptor, GFXIndexBufferHandle *a_Handle)
{
	assert(0 != a_API);
	DX11API *api = a_API;
	assert(0 != api->m_Device);

	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = (uint32_t)a_Descriptor->m_DataByteSize;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = a_Descriptor->m_Indices;
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	DX11IndexBuffer *vertexBuffer = ALLOCATE(DX11IndexBuffer);
	HRESULT result = api->m_Device->lpVtbl->CreateBuffer(api->m_Device, &bufferDesc, &subResourceData, &vertexBuffer->m_Buffer);
#if !defined(NDEBUG)
	assert(S_OK == result);
#else
	GFX_UNUSED(result);
#endif
	*a_Handle = vertexBuffer;
}

void GFXDestroyIndexBuffer(GFXAPI a_API, GFXIndexBufferHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_Handle);
	DX11IndexBuffer *indexBuffer = a_Handle;
	SAFERELEASE(indexBuffer->m_Buffer);
	DEALLOCATE(indexBuffer);
}

void GFXCreateTexture(GFXAPI a_API, GFXTextureDescriptor *a_Descriptor, GFXTextureHandle *a_Handle)
{
	assert(0 != a_API);
	DX11API *api = a_API;

	D3D11_TEXTURE2D_DESC texture2DDesc = { 0 };
	texture2DDesc.Width = a_Descriptor->m_Width;
	texture2DDesc.Height = a_Descriptor->m_Height;
	texture2DDesc.MipLevels = 1;
	texture2DDesc.ArraySize = 1;
	texture2DDesc.Format = TranslateTextureFormat(a_Descriptor->m_Format);
	texture2DDesc.SampleDesc.Count = 1;
	texture2DDesc.SampleDesc.Quality = 0;
	texture2DDesc.Usage = D3D11_USAGE_DEFAULT;
	UINT bindFlags = D3D11_BIND_SHADER_RESOURCE;
	if (a_Descriptor->m_DepthStencil)
	{
		bindFlags |= D3D11_BIND_DEPTH_STENCIL;
	}
	texture2DDesc.BindFlags = bindFlags;
	texture2DDesc.CPUAccessFlags = 0;
	texture2DDesc.MiscFlags = 0;

	DX11Texture *texture = ALLOCATE(DX11Texture);
	assert(0 != texture);
	HRESULT result = api->m_Device->lpVtbl->CreateTexture2D(api->m_Device, &texture2DDesc, 0, &texture->m_Texture);
#if !defined(NDEBUG)
	assert(S_OK == result);
#else
	GFX_UNUSED(result);
#endif

	if (0 != a_Descriptor->m_Data)
	{
		api->m_DeviceContext->lpVtbl->UpdateSubresource(api->m_DeviceContext, (ID3D11Resource*)texture->m_Texture, 0, 0, a_Descriptor->m_Data, (UINT)(a_Descriptor->m_RowPitch), 0);
	}

	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	shaderResourceViewDesc.Format = TranslateTextureFormat(a_Descriptor->m_ShaderResourceViewFormat);
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;
	result = api->m_Device->lpVtbl->CreateShaderResourceView(api->m_Device, (ID3D11Resource*)texture->m_Texture, &shaderResourceViewDesc, &texture->m_ShaderResourceView);
#if !defined(NDEBUG)
	assert(S_OK == result);
#else
	GFX_UNUSED(result);
#endif

#if !defined(NDEBUG)
	if (0 != a_Descriptor->m_DebugName)
	{
		SETDEBUGNAME(texture->m_Texture, a_Descriptor->m_DebugName);
	}
#endif
	*a_Handle = texture;
}

void GFXDestroyTexture(GFXAPI a_API, GFXTextureHandle a_Handle)
{
	GFX_UNUSED(a_API);
	if (0 != a_Handle)
	{
		DX11Texture *texture = a_Handle;
		SAFERELEASE(texture->m_Texture);
		DEALLOCATE(texture);
	}
}

void GFXCreateSamplerState(GFXAPI a_API, GFXSamplerStateDescriptor *a_Descriptor, GFXSamplerStateHandle *a_Handle)
{
	GFX_UNUSED(a_Descriptor);
	assert(0 != a_API);
	DX11API *api = a_API;

	D3D11_SAMPLER_DESC samplerDesc = { 0 };
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	DX11SamplerState *samplerState = ALLOCATE(DX11SamplerState);
	assert(0 != samplerState);
	HRESULT result = api->m_Device->lpVtbl->CreateSamplerState(api->m_Device, &samplerDesc, &samplerState->m_SamplerState);
#if !defined(NDEBUG)
	assert(S_OK == result);
#else
	GFX_UNUSED(result);
#endif
	*a_Handle = samplerState;
}

void GFXDestroySamplerState(GFXAPI a_API, GFXSamplerStateHandle a_Handle)
{
	GFX_UNUSED(a_API);
	if (0 != a_Handle)
	{
		DX11SamplerState *samplerState = a_Handle;
		SAFERELEASE(samplerState->m_SamplerState);
		DEALLOCATE(samplerState);
	}
}

void GFXCreateShader(GFXAPI a_API, GFXShaderDescriptor *a_Descriptor, GFXShaderHandle *a_Handle)
{
	GFX_UNUSED(a_Descriptor);

	assert(0 != a_API);
	DX11API *api = a_API;
	assert(0 != api->m_Device);

// 	D3D_SHADER_MACRO *shaderDefines = 0;
// 	ID3DInclude *shaderIncludes = 0;
// 	UINT compileFlags = 0;
// #if !defined(NDEBUG)
// 	compileFlags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
// #endif
// 	UINT advancedFlags = 0;
// 	ID3DBlob *errors = 0;
// 
	DX11Shader *shader = ALLOCATE(DX11Shader);
// 	uint32_t i;
// 	for (i = 0; i < (uint32_t)a_Descriptor->m_NumShaders; ++i)
// 	{
// 		const char *shaderSource = a_Descriptor->m_Source[i];
// 		const size_t shaderSourceDataSize = strlen(shaderSource);
// 		char *entryPoint = 0;
// 
// 		switch (a_Descriptor->m_Type[i])
// 		{
// 		case ShaderType_VertexShader:
// 			{
// 				entryPoint = "vs_5_0";
// 				break;
// 			}
// 		case ShaderType_FragmentShader:
// 			{
// 				entryPoint = "ps_5_0";
// 				break;
// 			}
// 		default:
// 			{
// 				fprintf(stderr, "Unsupported shader type encountered!");
// 				assert(false);
// 				break;
// 			}
// 		}
// 
// 		ID3DBlob *shaderByteCode;
// 		HRESULT result = D3DCompile(shaderSource, shaderSourceDataSize, 0, shaderDefines, shaderIncludes,
// 			"main", entryPoint, compileFlags, advancedFlags, &shaderByteCode, &errors);
// 		if (S_OK != result)
// 		{
// 			const char *errorString = (char*)errors->lpVtbl->GetBufferPointer(errors);
// 			fprintf(stderr, "Shader compilation failed: %s\n", errorString);
// 			assert(false);
// 		}
// 
// 		assert(0 != shaderByteCode);
// 		const void *shaderBufferPointer = shaderByteCode->lpVtbl->GetBufferPointer(shaderByteCode);
// 		const size_t shaderBufferSize = shaderByteCode->lpVtbl->GetBufferSize(shaderByteCode);
// 		switch (a_Descriptor->m_Type[i])
// 		{
// 		case ShaderType_VertexShader:
// 			{
// 				result = api->m_Device->lpVtbl->CreateVertexShader(api->m_Device, shaderBufferPointer, shaderBufferSize, 0, &shader->m_VertexShader);
// 				shader->m_ByteCode = shaderByteCode;
// 				//InspectVertexShader(shader->m_ByteCode, &shader->m_ConstantBuffer);
// 				assert(S_OK == result);
// 				break;
// 			}
// 		case ShaderType_FragmentShader:
// 			{
// 				result = api->m_Device->lpVtbl->CreatePixelShader(api->m_Device, shaderBufferPointer, shaderBufferSize, 0, &shader->m_PixelShader);
// 				assert(S_OK == result);
// 				break;
// 			}
// 		default:
// 			{
// 				fprintf(stderr, "Unsupported shader type encountered!");
// 				assert(false);
// 				break;
// 			}
// 		}
// 	}
	*a_Handle = shader;
}

void GFXDestroyShader(GFXAPI a_API, GFXShaderHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_Handle);
	DX11Shader *shader = a_Handle;

	SAFERELEASE(shader->m_VertexShader);
	SAFERELEASE(shader->m_PixelShader);
	SAFERELEASE(shader->m_ByteCode);
	DEALLOCATE(shader);
}

void GFXCreateInputLayout(GFXAPI a_API, GFXInputLayoutDescriptor *a_Descriptor, GFXInputLayoutHandle *a_Handle)
{
	assert(0 != a_API);
	DX11API *api = a_API;
	assert(0 != api->m_Device);

	D3D11_INPUT_ELEMENT_DESC *inputLayoutDesc = malloc(sizeof(D3D11_INPUT_ELEMENT_DESC) * a_Descriptor->m_NumElements);
	uint32_t i;
	for (i = 0; i < a_Descriptor->m_NumElements; ++i)
	{
		inputLayoutDesc[i].SemanticName = TranslateSemantic(a_Descriptor->m_Elements[i].m_Name);
		inputLayoutDesc[i].SemanticIndex = 0;
		inputLayoutDesc[i].Format = TranslateFormat(a_Descriptor->m_Elements[i].m_Type, a_Descriptor->m_Elements[i].m_Size);
		inputLayoutDesc[i].InputSlot = 0;
		inputLayoutDesc[i].AlignedByteOffset = i == 0 ? 0 : D3D11_APPEND_ALIGNED_ELEMENT;
		inputLayoutDesc[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		inputLayoutDesc[i].InstanceDataStepRate = 0;
	}

	DX11Shader *shader = a_Descriptor->m_Shader;
	assert(0 != shader->m_ByteCode);
	const void *shaderBufferPointer = shader->m_ByteCode->lpVtbl->GetBufferPointer(shader->m_ByteCode);
	const size_t shaderBufferSize = shader->m_ByteCode->lpVtbl->GetBufferSize(shader->m_ByteCode);

	DX11InputLayout *inputLayout = ALLOCATE(DX11InputLayout);
	HRESULT result = api->m_Device->lpVtbl->CreateInputLayout(api->m_Device, inputLayoutDesc, a_Descriptor->m_NumElements, shaderBufferPointer, shaderBufferSize, &inputLayout->m_InputLayout);
#if !defined(NDEBUG)
	assert(S_OK == result);
#else
	GFX_UNUSED(result);
#endif
	free(inputLayoutDesc);
	inputLayout->m_VertexByteSize = a_Descriptor->m_VertexByteSize;

	*a_Handle = inputLayout;
}

void GFXDestroyInputLayout(GFXAPI a_API, GFXInputLayoutHandle a_Handle)
{
	GFX_UNUSED(a_API);
	if (0 != a_Handle)
	{
		DX11PipelineStateObject *pipelineStateObject = a_Handle;
		DEALLOCATE(pipelineStateObject);
	}
}

void GFXCreateConstantBuffer(GFXAPI a_API, GFXConstantBufferDescriptor *a_Descriptor, GFXConstantBufferHandle *a_Handle)
{
	assert(0 != a_API);
	DX11API *api = a_API;
	assert(0 != api->m_Device);

	DX11ConstantBuffer *constantBuffer = ALLOCATE(DX11ConstantBuffer);
	size_t length;
#if !defined(NDEBUG)
	length = strlen(a_Descriptor->m_DebugName) + 1;
	constantBuffer->m_Name = (char*)malloc(length * sizeof(char));
	strcpy_s(constantBuffer->m_Name, length, a_Descriptor->m_DebugName);
#endif
	constantBuffer->m_Size = a_Descriptor->m_ByteSize;
	constantBuffer->m_Data = (char*)malloc(constantBuffer->m_Size * sizeof(char));
	constantBuffer->m_NumElements = a_Descriptor->m_NumElements;
	constantBuffer->m_Elements = (DX11ConstantBufferElement*)malloc(constantBuffer->m_NumElements * sizeof(DX11ConstantBufferElement));

	uint32_t offset = 0;
	uint32_t i = 0;
	for (i = 0; i < a_Descriptor->m_NumElements; ++i)
	{
		GFXConstantBufferElementDescriptor *element = &a_Descriptor->m_Elements[i];
		length = strlen(a_Descriptor->m_Elements[i].m_Name) + 1;
		constantBuffer->m_Elements[i].m_Name = (char*)malloc(length * sizeof(char));
		strcpy_s(constantBuffer->m_Elements[i].m_Name, length, element->m_Name);

		constantBuffer->m_Elements[i].m_Size = element->m_Size;
		constantBuffer->m_Elements[i].m_Offset = offset;
		constantBuffer->m_Elements[i].m_Transpose = element->m_Transpose;
		constantBuffer->m_Elements[i].m_Type = element->m_Type;

		offset += element->m_Size;
	}

	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = a_Descriptor->m_ByteSize;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA *initialData = 0;
	HRESULT result = api->m_Device->lpVtbl->CreateBuffer(api->m_Device, &bufferDesc, initialData, &constantBuffer->m_Buffer);
#if !defined(NDEBUG)
	assert(S_OK == result);
#else
	GFX_UNUSED(result);
#endif

#if !defined(NDEBUG)
	if (0 != a_Descriptor->m_DebugName)
	{
		SETDEBUGNAME(constantBuffer->m_Buffer, a_Descriptor->m_DebugName);
	}
#endif
	*a_Handle = constantBuffer;
}

void GFXCopyConstantBufferData(GFXAPI a_API, GFXConstantBufferHandle a_Handle, const char *a_VariableName, const void *a_Data)
{
	GFX_UNUSED(a_API);

	assert(0 != a_Handle);
	DX11ConstantBuffer *constantBuffer = a_Handle;

	bool copied = false;
	uint32_t i = 0;
	for (i; i < constantBuffer->m_NumElements && !copied; ++i)
	{
		DX11ConstantBufferElement *element = &constantBuffer->m_Elements[i];
		if (0 == strcmp(element->m_Name, a_VariableName))
		{
			if (element->m_Transpose)
			{
				void *data = malloc(element->m_Size);
				TransposeData(a_Data, data, element->m_Size, element->m_Type);
				memcpy(&constantBuffer->m_Data[element->m_Offset], data, element->m_Size);
				DEALLOCATE((void*)data);
			}
			else
			{
				memcpy(&constantBuffer->m_Data[element->m_Offset], a_Data, element->m_Size);
			}
			copied = true;
		}
	}
}

void GFXDestroyConstantBuffer(GFXAPI a_API, GFXConstantBufferHandle a_Handle)
{
	GFX_UNUSED(a_API);
	if (0 != a_Handle)
	{
		DX11ConstantBuffer *constantBuffer = a_Handle;
		uint32_t i = 0;
		for (i = 0; i < constantBuffer->m_NumElements; ++i)
		{
			free(constantBuffer->m_Elements[i].m_Name);
		}
#if !defined(NDEBUG)
		free(constantBuffer->m_Name);
#endif
		free(constantBuffer->m_Elements);
		free(constantBuffer->m_Data);
		DEALLOCATE(constantBuffer);
	}
}

void GFXCreateResource(GFXAPI a_API, GFXResourceDescriptor *a_Descriptor, GFXResourceHandle *a_Handle)
{
	assert(false);
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXDestroyResource(GFXAPI a_API, GFXResourceHandle a_Handle)
{
	assert(false);
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

bool EqualViewports(D3D11_VIEWPORT *a_CurrentViewport, D3D11_VIEWPORT *a_RequestedViewport)
{
	return a_CurrentViewport->TopLeftX == a_RequestedViewport->TopLeftX &&
		a_CurrentViewport->TopLeftY == a_RequestedViewport->TopLeftY &&
		a_CurrentViewport->Width == a_RequestedViewport->Width &&
		a_CurrentViewport->Height == a_RequestedViewport->Height &&
		a_CurrentViewport->MinDepth == a_RequestedViewport->MinDepth &&
		a_CurrentViewport->MaxDepth == a_RequestedViewport->MaxDepth;
}

void GFXDrawIndexed(GFXAPI a_API, GFXCommandListHandle a_Handle, uint32_t a_NumVertices)
{
	assert(0 != a_API);
	DX11API *api = a_API;
	assert(0 != a_Handle);
	DX11CommandList *commandList = a_Handle;

	assert(0 != commandList->m_PipelineStateObject);
	DX11PipelineStateObject *pipelineStateObject = commandList->m_PipelineStateObject;

	unsigned int stride = pipelineStateObject->m_InputLayout->m_VertexByteSize;
	unsigned int offset = 0;
	api->m_DeviceContext->lpVtbl->IASetVertexBuffers(api->m_DeviceContext, 0, 1, &commandList->m_VertexBuffer->m_Buffer, &stride, &offset);
	api->m_DeviceContext->lpVtbl->IASetIndexBuffer(api->m_DeviceContext, commandList->m_IndexBuffer->m_Buffer, DXGI_FORMAT_R32_UINT, 0);
	api->m_DeviceContext->lpVtbl->IASetPrimitiveTopology(api->m_DeviceContext, commandList->m_RenderMode);

	uint32_t i;
	for (i = 0; i < commandList->m_NumConstantBuffers; ++i)
	{
		DX11ConstantBuffer *constantBuffer = commandList->m_ConstantBuffers[i];
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		UINT subResource = 0;
		D3D11_MAP mapType = D3D11_MAP_WRITE_DISCARD;
		UINT flags = 0;
		HRESULT result = api->m_DeviceContext->lpVtbl->Map(api->m_DeviceContext, (ID3D11Resource*)constantBuffer->m_Buffer, subResource, mapType, flags, &mappedResource);
#if !defined(NDEBUG)
		assert(S_OK == result);
#else
		GFX_UNUSED(result);
#endif
		char *buffer = (char*)mappedResource.pData;
		memcpy(buffer, constantBuffer->m_Data, constantBuffer->m_Size);
		api->m_DeviceContext->lpVtbl->Unmap(api->m_DeviceContext, (ID3D11Resource*)constantBuffer->m_Buffer, subResource);
	}

	UINT constantBufferStartSlot = 0;
	UINT numConstantBuffers = commandList->m_NumConstantBuffers;
	api->m_DeviceContext->lpVtbl->IASetInputLayout(api->m_DeviceContext, pipelineStateObject->m_InputLayout->m_InputLayout);
	for (i = 0; i < numConstantBuffers; ++i, ++constantBufferStartSlot)
	{
		api->m_DeviceContext->lpVtbl->VSSetConstantBuffers(api->m_DeviceContext, constantBufferStartSlot, 1, &commandList->m_ConstantBuffers[i]->m_Buffer);
		api->m_DeviceContext->lpVtbl->PSSetConstantBuffers(api->m_DeviceContext, constantBufferStartSlot, 1, &commandList->m_ConstantBuffers[i]->m_Buffer);
	}
	api->m_DeviceContext->lpVtbl->VSSetShader(api->m_DeviceContext, pipelineStateObject->m_Shader->m_VertexShader, 0, 0);

	if (!EqualViewports(&api->m_CurrentViewport, commandList->m_Viewport->m_Viewport))
	{
		api->m_DeviceContext->lpVtbl->RSSetViewports(api->m_DeviceContext, 1, commandList->m_Viewport->m_Viewport);
		api->m_CurrentViewport = *commandList->m_Viewport->m_Viewport;
	}
	api->m_DeviceContext->lpVtbl->PSSetShader(api->m_DeviceContext, pipelineStateObject->m_Shader->m_PixelShader, 0, 0);

	if (0 != commandList->m_DiffuseTexture)
	{
		api->m_DeviceContext->lpVtbl->PSSetShaderResources(api->m_DeviceContext, 0, 1, &commandList->m_DiffuseTexture->m_ShaderResourceView);
		api->m_DeviceContext->lpVtbl->PSSetSamplers(api->m_DeviceContext, 0, 1, &commandList->m_SamplerState->m_SamplerState);
	}
	// bind material

	api->m_DeviceContext->lpVtbl->DrawIndexed(api->m_DeviceContext, a_NumVertices, 0, 0);

	// NB: DX11 Graphics Pipeline stage order:
	//	 1. Input-Assembler Stage
	//	 1. Vertex Shader Stage
	//	 1. Hull Shader Stage
	//	 1. Tessallator Stage
	//	 1. Domain Shader Stage
	//	 1. Geometry Shader Stage
	//	 1. Stream Output Stage
	//	 1. Rasterizer Stage
	//	 1. Pixel-Shader Stage
	//	 1. Output-Merger Stage
}

void GFXCreateCommandList(GFXAPI a_API, GFXCommandListDescriptor *a_Descriptor, GFXCommandListHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_API);
	assert(0 != a_Descriptor);
	DX11CommandList *commandList = ALLOCATE(DX11CommandList);
	memset(commandList, 0, sizeof(DX11CommandList));
// 	if (0 != a_Descriptor->m_VertexBuffer)
// 	{
// 		commandList->m_VertexBuffer = (DX11VertexBuffer*)a_Descriptor->m_VertexBuffer;
// 	}
// 	if (0 != a_Descriptor->m_IndexBuffer)
// 	{
// 		commandList->m_IndexBuffer = (DX11IndexBuffer*)a_Descriptor->m_IndexBuffer;
// 	}
// 	commandList->m_Viewport = (DX11Viewport*)a_Descriptor->m_Viewport;
// 	commandList->m_RenderMode = TranslateRenderMode(a_Descriptor->m_RenderMode);
// 	commandList->m_PipelineStateObject = (DX11PipelineStateObject*)a_Descriptor->m_PipelineStateObject;
// 	commandList->m_NumConstantBuffers = a_Descriptor->m_NumConstantBuffers;
// 	commandList->m_ConstantBuffers = (DX11ConstantBuffer**)malloc(sizeof(DX11ConstantBuffer*) * a_Descriptor->m_NumConstantBuffers);
// 	if (0 != a_Descriptor->m_NumConstantBuffers)	// be careful with how these are copied; always all of 'em or not...?!?!?
// 	{
// 		for (uint32_t i = 0; i < a_Descriptor->m_NumConstantBuffers; ++i)
// 		{
// 			commandList->m_ConstantBuffers[i] = (DX11ConstantBuffer*)a_Descriptor->m_ConstantBuffers[i];
// 		}
// 	}
// 
// 	commandList->m_SamplerState = (DX11SamplerState*)a_Descriptor->m_SamplerState;
// 	commandList->m_DiffuseTexture = (DX11Texture*)a_Descriptor->m_DiffuseTexture;

	*a_Handle = commandList;
}

void GFXUpdateCommandList(GFXAPI a_API, GFXCommandListDescriptor *a_Descriptor, GFXCommandListHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_API);
	assert(0 != a_API);
	assert(0 != a_Descriptor);
	assert(0 != a_Handle);
// 	DX11CommandList *commandList = a_Handle;
// 	if (0 != a_Descriptor->m_VertexBuffer) { commandList->m_VertexBuffer = (DX11VertexBuffer*)a_Descriptor->m_VertexBuffer; }
// 	if (0 != a_Descriptor->m_IndexBuffer) { commandList->m_IndexBuffer = (DX11IndexBuffer*)a_Descriptor->m_IndexBuffer; }
// 	if (0 != a_Descriptor->m_Viewport) { commandList->m_Viewport = ((DX11Viewport*)(a_Descriptor->m_Viewport)); }
// 	if (RenderMode_Invalid != a_Descriptor->m_RenderMode) { commandList->m_RenderMode = TranslateRenderMode(a_Descriptor->m_RenderMode); }
// 	if (0 != a_Descriptor->m_PipelineStateObject) { commandList->m_PipelineStateObject = (DX11PipelineStateObject*)a_Descriptor->m_PipelineStateObject; }
// 	//if (0 != a_Descriptor->m_ConstantBuffer) { commandList->m_ConstantBuffer = (DX11ConstantBuffer*)a_Descriptor->m_ConstantBuffer; }
// 	if (0 != a_Descriptor->m_NumConstantBuffers)	// be careful with how these are copied; always all of 'em or not...?!?!?
// 	{
// 		for (uint32_t i = 0; i < a_Descriptor->m_NumConstantBuffers; ++i)
// 		{
// 			commandList->m_ConstantBuffers[i] = (DX11ConstantBuffer*)a_Descriptor->m_ConstantBuffers[i];
// 		}
// 	}
// 	if (0 != a_Descriptor->m_DiffuseTexture) { commandList->m_DiffuseTexture = (DX11Texture*)a_Descriptor->m_DiffuseTexture; }
// 	if (0 != a_Descriptor->m_SamplerState) { commandList->m_SamplerState = (DX11SamplerState*)a_Descriptor->m_SamplerState; }
}

void GFXDestroyCommandList(GFXAPI a_API, GFXCommandListHandle a_Handle)
{
	GFX_UNUSED(a_API);
	if(0 != a_Handle)
	{
		DX11CommandList *commandList = a_Handle;
		DEALLOCATE(commandList->m_ConstantBuffers);
		DEALLOCATE(commandList);
	}
}

void GFXCreatePipelineStateObject(GFXAPI a_API, GFXPipelineStateObjectDescriptor *a_Descriptor, GFXPipelineStateObjectHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_API);
	assert(0 != a_Descriptor);
	DX11PipelineStateObject *pipelineStateObject = ALLOCATE(DX11PipelineStateObject);
	memset(pipelineStateObject, 0, sizeof(DX11PipelineStateObject));
// 	pipelineStateObject->m_Shader = (DX11Shader*)a_Descriptor->m_Shader;
// 	pipelineStateObject->m_BlendState = (DX11BlendState*)a_Descriptor->m_BlendState;
// 	pipelineStateObject->m_RasterizerState = (DX11RasterizerState*)a_Descriptor->m_RasterizerState;
// 	pipelineStateObject->m_InputLayout = (DX11InputLayout*)a_Descriptor->m_InputLayout;
// 	pipelineStateObject->m_RenderTarget = (DX11RenderTarget*)a_Descriptor->m_RenderTarget;

	*a_Handle = pipelineStateObject;
}

void GFXSetPipelineStateObject(GFXAPI a_API, GFXPipelineStateObjectHandle a_Handle)
{
	assert(0 != a_API);
	DX11API *api = a_API;
	assert(0 != api->m_DeviceContext);
	assert(0 != a_Handle);

	DX11PipelineStateObject *pipelineStateObject = a_Handle;
	pipelineStateObject->m_Shader;

	if (0 != pipelineStateObject->m_BlendState)
	{
		DX11BlendState *blendState = pipelineStateObject->m_BlendState;
		api->m_DeviceContext->lpVtbl->OMSetBlendState(api->m_DeviceContext, blendState->m_BlendState, blendState->m_Factor, blendState->m_SampleMask);
	}
	if (0 != pipelineStateObject->m_RasterizerState)
	{
		DX11RasterizerState *rasterizerState = pipelineStateObject->m_RasterizerState;
		api->m_DeviceContext->lpVtbl->RSSetState(api->m_DeviceContext, rasterizerState->m_RasterizerState);
	}
	if (0 != pipelineStateObject->m_InputLayout)
	{
		DX11InputLayout *inputLayout = pipelineStateObject->m_InputLayout;
		api->m_DeviceContext->lpVtbl->IASetInputLayout(api->m_DeviceContext, inputLayout->m_InputLayout);
	}
	if (0 != pipelineStateObject->m_RenderTarget)
	{
		DX11RenderTarget *renderTarget = pipelineStateObject->m_RenderTarget;
		api->m_DeviceContext->lpVtbl->OMSetRenderTargets(api->m_DeviceContext, 1, &renderTarget->m_RenderTargetView, renderTarget->m_DepthStencilView);
	}
}

void GFXDestroyPipelineStateObject(GFXAPI a_API, GFXPipelineStateObjectHandle a_Handle)
{
	GFX_UNUSED(a_API);
	if (0 != a_Handle)
	{
		DX11PipelineStateObject *pipelineStateObject = a_Handle;
		DEALLOCATE(pipelineStateObject);
	}
}

void GFXCreateDepthStencilState(GFXAPI a_API, GFXDepthStencilStateDescriptor *a_Descriptor, GFXDepthStencilStateHandle *a_Handle)
{
	assert(a_API);
	DX11API *api = a_API;

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = { 0 };
	depthStencilDesc.DepthEnable = a_Descriptor->m_DepthEnabled;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	DX11DepthStencilState *depthStencilState = ALLOCATE(DX11DepthStencilState);
	HRESULT result = api->m_Device->lpVtbl->CreateDepthStencilState(api->m_Device, &depthStencilDesc, &depthStencilState->m_DepthStencilState);
#if !defined(NDEBUG)
	assert(S_OK == result);
#else
	GFX_UNUSED(result);
#endif
	*a_Handle = depthStencilState;
}

void GFXDestroyDepthStencilState(GFXAPI a_API, GFXDepthStencilStateHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_Handle);
	DX11DepthStencilState *depthStencilState = a_Handle;
	SAFERELEASE(depthStencilState->m_DepthStencilState);
	DEALLOCATE(depthStencilState);
}

#endif
