#include "Graphics/API/GFX.h"

#include "Graphics/API/DX12/DX12Includes.h"
#include "Graphics/API/DX12/DX12Structs.h"
#include "Graphics/API/DX12/DX12Translators.h"
#include "Graphics/API/DX12/Helpers/SafeRelease.h"

#include <assert.h>
#include <stdio.h>

#if defined(GFX_API_DX12)

GFXAPI g_API = 0;

void CheckResult(HRESULT a_Result)
{
#if defined(_DEBUG)
	assert(S_OK == a_Result);
#else
	GFX_UNUSED(a_Result);
#endif
}

bool CheckTearingSupport(DX12API *a_API)
{
	IDXGIFactory5 *factory5 = (IDXGIFactory5*)a_API->m_Factory;
	BOOL allowTearing = FALSE;
	CheckResult(factory5->lpVtbl->CheckFeatureSupport(factory5, DXGI_FEATURE_PRESENT_ALLOW_TEARING, &allowTearing, sizeof(allowTearing)));
	return allowTearing == TRUE;
}

void ExtractShaderByteCodeInfo(D3D12_SHADER_BYTECODE *a_ShaderByteCode, DX12Shader *a_Shader)
{
	assert(NULL != a_ShaderByteCode);
	if (NULL != a_Shader)
	{
		a_ShaderByteCode->BytecodeLength = a_Shader->m_BackEnd->lpVtbl->GetBufferSize(a_Shader->m_BackEnd);
		a_ShaderByteCode->pShaderBytecode = a_Shader->m_BackEnd->lpVtbl->GetBufferPointer(a_Shader->m_BackEnd);
	}
}

ID3D12DescriptorHeap* CreateDescriptorHeap(DX12API *a_API, D3D12_DESCRIPTOR_HEAP_TYPE a_Type, uint32_t a_NumDescriptors)
{
	ID3D12DescriptorHeap *descriptorHeap;
	D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc = { 0 };
	descriptorHeapDesc.NumDescriptors = a_NumDescriptors;
	descriptorHeapDesc.Type = a_Type;
	CheckResult(a_API->m_Device->lpVtbl->CreateDescriptorHeap(a_API->m_Device, &descriptorHeapDesc, &IID_ID3D12DescriptorHeap, (void**)&descriptorHeap));
	return descriptorHeap;
}

void GFXInitialize(GFXAPI *a_API, Allocator *a_Allocator, GFXAPIDescriptor *a_Descriptor)
{
	GFX_UNUSED(a_Allocator);

	DX12API *api = ALLOCATE(DX12API);
	assert(0 != api);

	api->m_WindowHandle = a_Descriptor->m_WindowHandle;

	UINT dxgiFactoryFlags = 0;
#if defined(_DEBUG)
	ID3D12Debug *debugController = NULL;

	HRESULT result = D3D12GetDebugInterface(&IID_ID3D12Debug, (void**)&debugController);
	assert(S_OK == result);
	debugController->lpVtbl->EnableDebugLayer(debugController);
	dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
#endif

	result = CreateDXGIFactory2(dxgiFactoryFlags, &IID_IDXGIFactory, (void**)&api->m_Factory);
	assert(S_OK == result);

	if (a_Descriptor->m_UseSoftwareDevice)
	{
		IDXGIAdapter *warpAdapter = NULL;
		CheckResult(api->m_Factory->lpVtbl->EnumWarpAdapter(api->m_Factory, &IID_IDXGIAdapter1, (void**)&warpAdapter));

		CheckResult(D3D12CreateDevice((IUnknown*)warpAdapter, D3D_FEATURE_LEVEL_11_0, &IID_ID3D12Device, (void**)&api->m_Device));
	}
	else
	{
		IDXGIAdapter1 *hardwareAdapter = NULL;
		for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != api->m_Factory->lpVtbl->EnumAdapters1(api->m_Factory, adapterIndex, &hardwareAdapter); ++adapterIndex)
		{
			DXGI_ADAPTER_DESC1 desc;
			hardwareAdapter->lpVtbl->GetDesc1(hardwareAdapter, &desc);

			if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
			{
				continue;
			}
			else
			{
				result = D3D12CreateDevice((IUnknown*)hardwareAdapter, D3D_FEATURE_LEVEL_11_0, &IID_ID3D12Device, (void**)&api->m_Device);
				if (S_OK == result)
				{
					break;
				}
			}
		}
		CheckResult(result);
	}

	api->m_FenceValue = 0;

	g_API = api;
	*a_API = api;
}

void GFXTerminate(GFXAPI a_API)
{
	assert(NULL != a_API);
	DX12API *api = (DX12API*)a_API;
	SAFERELEASE(api->m_Device);
	SAFERELEASE(api->m_Factory);
	DEALLOCATE(api);
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

void GFXCreateSwapChain(GFXAPI a_API, GFXSwapChainDescriptor *a_Descriptor, GFXSwapChainHandle *a_Handle)
{
	assert(NULL != a_API);
	DX12API *api = (DX12API *)a_API;
	assert(NULL != api->m_Factory);

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };
	swapChainDesc.Width = a_Descriptor->m_FrameBufferWidth;
	swapChainDesc.Height = a_Descriptor->m_FrameBufferHeight;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.Stereo = false;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = a_Descriptor->m_BufferCount;
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	swapChainDesc.Flags = CheckTearingSupport(api) ? DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING : 0;

	DX12SwapChain *swapChain = ALLOCATE(DX12SwapChain);
	DX12CommandQueue *commandQueue = (DX12CommandQueue*)a_Descriptor->m_CommandQueue;
	HRESULT result = api->m_Factory->lpVtbl->CreateSwapChainForHwnd(api->m_Factory, (IUnknown*)commandQueue->m_BackEnd, api->m_WindowHandle, &swapChainDesc, NULL, NULL, (IDXGISwapChain1**)&swapChain->m_BackEnd);
	CheckResult(result);
	swapChain->m_BufferCount = a_Descriptor->m_BufferCount;

	api->m_CurrentBackBufferIndex = swapChain->m_BackEnd->lpVtbl->GetCurrentBackBufferIndex(swapChain->m_BackEnd);
	*a_Handle = swapChain;
}


void GFXDestroySwapChain(GFXAPI a_API, GFXSwapChainHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(NULL != a_Handle);
	DX12SwapChain *swapChain = a_Handle;
	SAFERELEASE(swapChain->m_BackEnd);
	DEALLOCATE(swapChain);
}

void GFXCreateRenderTarget(GFXAPI a_API, GFXRenderTargetDescriptor *a_Descriptor, GFXRenderTargetHandle *a_Handle)
{
	assert(NULL != a_API);
	assert(NULL != a_Descriptor);
	DX12API *api = (DX12API*)a_API;
	DX12SwapChain *swapChain = (DX12SwapChain*)a_Descriptor->m_SwapChain;

	DX12RenderTarget *renderTarget = ALLOCATE(DX12RenderTarget);
	renderTarget->m_BufferCount = swapChain->m_BufferCount;
	renderTarget->m_DescriptorHeap = CreateDescriptorHeap(a_API, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, renderTarget->m_BufferCount);
	renderTarget->m_BackBuffers = ALLOCATEARRAY(ID3D12Resource*, renderTarget->m_BufferCount);

// 	GetGPUDescriptorHandleForHeapStart gpuFunction = (GetGPUDescriptorHandleForHeapStart)renderTarget->m_DescriptorHeap->lpVtbl->GetGPUDescriptorHandleForHeapStart;
// 	gpuFunction(renderTarget->m_DescriptorHeap, &renderTarget->m_GPUHandle);

	renderTarget->m_CPUFunction = (GetCPUDescriptorHandleForHeapStart)renderTarget->m_DescriptorHeap->lpVtbl->GetCPUDescriptorHandleForHeapStart;
	renderTarget->m_CPUFunction(renderTarget->m_DescriptorHeap, &renderTarget->m_CPUHandle);

	api->m_DescriptorHandleInc[D3D12_DESCRIPTOR_HEAP_TYPE_RTV] = api->m_Device->lpVtbl->GetDescriptorHandleIncrementSize(api->m_Device, D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	for (uint32_t i = 0; i < swapChain->m_BufferCount; ++i)
	{
		ID3D12Resource *backBuffer;
		CheckResult(swapChain->m_BackEnd->lpVtbl->GetBuffer(swapChain->m_BackEnd, i, &IID_ID3D12Resource, (void**)&backBuffer));
		api->m_Device->lpVtbl->CreateRenderTargetView(api->m_Device, backBuffer, NULL, renderTarget->m_CPUHandle);
		renderTarget->m_BackBuffers[i] = backBuffer;
		renderTarget->m_CPUHandle.ptr += api->m_DescriptorHandleInc[D3D12_DESCRIPTOR_HEAP_TYPE_RTV];
	}

	*a_Handle = renderTarget;
}

void GFXDestroyRenderTarget(GFXAPI a_API, GFXRenderTargetHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(NULL != a_Handle);
	DX12RenderTarget *renderTarget = a_Handle;
	DEALLOCATE(renderTarget->m_BackBuffers);
	SAFERELEASE(renderTarget->m_DescriptorHeap);
	DEALLOCATE(renderTarget);
}

void GFXCreateRasterizerState(GFXAPI a_API, GFXRasterizerStateDescriptor *a_Descriptor, GFXRasterizerStateHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);

	DX12RasterizerState *rasterizerState = ALLOCATE(DX12RasterizerState);	
	rasterizerState->m_BackEnd.FillMode = D3D12_FILL_MODE_SOLID;
	rasterizerState->m_BackEnd.CullMode = D3D12_CULL_MODE_BACK;
	rasterizerState->m_BackEnd.FrontCounterClockwise = FALSE;
	rasterizerState->m_BackEnd.DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
	rasterizerState->m_BackEnd.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
	rasterizerState->m_BackEnd.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
	rasterizerState->m_BackEnd.DepthClipEnable = TRUE;
	rasterizerState->m_BackEnd.MultisampleEnable = FALSE;
	rasterizerState->m_BackEnd.AntialiasedLineEnable = FALSE;
	rasterizerState->m_BackEnd.ForcedSampleCount = 0;
	rasterizerState->m_BackEnd.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

	*a_Handle = rasterizerState;
}

void GFXDestroyRasterizerState(GFXAPI a_API, GFXRasterizerStateHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(NULL != a_Handle);
	DX12RasterizerState *rasterizerState = (DX12RasterizerState*)a_Handle;
	DEALLOCATE(rasterizerState);
}

void GFXCreateBlendState(GFXAPI a_API, GFXBlendStateDescriptor *a_Descriptor, GFXBlendStateHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	DX12BlendState *blendState = ALLOCATE(DX12BlendState);
	blendState->m_BackEnd.AlphaToCoverageEnable = FALSE;
	blendState->m_BackEnd.IndependentBlendEnable = FALSE;
	const D3D12_RENDER_TARGET_BLEND_DESC defaultRenderTargetBlendDesc =
	{
		FALSE,FALSE,
		D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
		D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
		D3D12_LOGIC_OP_NOOP,
		D3D12_COLOR_WRITE_ENABLE_ALL,
	};
	for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
		blendState->m_BackEnd.RenderTarget[i] = defaultRenderTargetBlendDesc;
	*a_Handle = blendState;
}

void GFXDestroyBlendState(GFXAPI a_API, GFXBlendStateHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(NULL != a_Handle);
	DX12BlendState* blendState = (DX12BlendState*)a_Handle;
	DEALLOCATE(blendState);
}

void GFXPresent(GFXAPI a_API, GFXSwapChainHandle a_Handle)
{
	assert(NULL != a_API);
	assert(NULL != a_Handle);
	DX12API *api = (DX12API*)a_API;
	DX12SwapChain *swapChain = (DX12SwapChain*)a_Handle;
	const UINT a_SyncInterval = 1;
	const UINT a_Flags = 0;
	CheckResult(swapChain->m_BackEnd->lpVtbl->Present(swapChain->m_BackEnd, a_SyncInterval, a_Flags));
	api->m_CurrentBackBufferIndex = swapChain->m_BackEnd->lpVtbl->GetCurrentBackBufferIndex(swapChain->m_BackEnd);
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

	DX12Shader *shader = ALLOCATE(DX12Shader);
	shader->m_Type = a_Descriptor->m_Type;

	D3D_SHADER_MACRO *shaderDefines = NULL;
	ID3DInclude *shaderIncludes = NULL;
	UINT compileFlags = 0;
#if defined(_DEBUG)
	compileFlags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
	UINT advancedFlags = 0;
	ID3DBlob *errors = NULL;
	const char *target = (ShaderType_VertexShader == a_Descriptor->m_Type) ? "vs_5_0" : "ps_5_0";

	HRESULT result = D3DCompile(a_Descriptor->m_Source, strlen(a_Descriptor->m_Source), 0, shaderDefines, shaderIncludes,
		a_Descriptor->m_EntryPoint, target, compileFlags, advancedFlags, &shader->m_BackEnd, &errors);
	if (S_OK != result)
	{
		const char *errorString = (char*)errors->lpVtbl->GetBufferPointer(errors);
		fprintf(stderr, "Shader compilation failed: %s\n", errorString);
		assert(false);
	}
	*a_Handle = shader;
}

void GFXDestroyShader(GFXAPI a_API, GFXShaderHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(NULL != a_Handle);
	DX12Shader *shader = a_Handle;
	SAFERELEASE(shader->m_BackEnd);
	DEALLOCATE(shader);
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

void GFXCreateCommandQueue(GFXAPI a_API, GFXCommandQueueDescriptor *a_Descriptor, GFXCommandQueueHandle *a_Handle)
{
	assert(NULL != a_API);
	assert(NULL != a_Descriptor);
	DX12API *api = (DX12API*)a_API;
	DX12CommandQueue *commandQueue = ALLOCATE(DX12CommandQueue);

	D3D12_COMMAND_QUEUE_DESC commandQueueDesc = { 0 };
	commandQueueDesc.Flags = DX12CommandQueueFlags[a_Descriptor->m_Flags];
	commandQueueDesc.Type = DX12CommandListTypes[a_Descriptor->m_Type];

	CheckResult(api->m_Device->lpVtbl->CreateCommandQueue(api->m_Device, &commandQueueDesc, &IID_ID3D12CommandQueue, (void**)&commandQueue->m_BackEnd));
	CheckResult(api->m_Device->lpVtbl->CreateFence(api->m_Device, 0, D3D12_FENCE_FLAG_NONE, &IID_ID3D12Fence, (void**)&commandQueue->m_Fence));
	commandQueue->m_FenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	*a_Handle = commandQueue;
}

void GFXWaitForCommandQueueCompletion(GFXAPI a_API, GFXCommandQueueHandle a_Handle)
{
	assert(NULL != a_API);
	assert(NULL != a_Handle);
	DX12API *api = (DX12API*)a_API;
	DX12CommandQueue* commandQueue = (DX12CommandQueue*)a_Handle;
	const uint64_t fenceValue = commandQueue->m_Fence->lpVtbl->GetCompletedValue(commandQueue->m_Fence);
	if (fenceValue < api->m_FenceValue)
	{
		CheckResult(commandQueue->m_Fence->lpVtbl->SetEventOnCompletion(commandQueue->m_Fence, api->m_FenceValue, commandQueue->m_FenceEvent));
		WaitForSingleObject(commandQueue->m_FenceEvent, INFINITE);
	}
	api->m_FenceValue++;
}

void GFXDestroyCommandQueue(GFXAPI a_API, GFXCommandQueueHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(NULL != a_Handle);
	DX12CommandQueue *commandQueue = a_Handle;
	SAFERELEASE(commandQueue->m_BackEnd);
	SAFERELEASE(commandQueue->m_Fence);
	CloseHandle(commandQueue->m_FenceEvent);
	DEALLOCATE(commandQueue);
}

void GFXCreateCommandList(GFXAPI a_API, GFXCommandListDescriptor *a_Descriptor, GFXCommandListHandle *a_Handle)
{
	assert(NULL != a_API);
	DX12API *api = (DX12API*)a_API;
	assert(NULL != api->m_Device);

	DX12CommandList *commandList = ALLOCATE(DX12CommandList);
	const UINT gpuNode = 0;
	CheckResult(api->m_Device->lpVtbl->CreateCommandAllocator(api->m_Device, DX12CommandListTypes[a_Descriptor->m_Type], &IID_ID3D12CommandAllocator, (void**)&commandList->m_Allocator));

	ID3D12PipelineState *pipelineStateObject = (NULL != a_Descriptor->m_PipelineStateObject) ? ((DX12PipelineStateObject*)a_Descriptor->m_PipelineStateObject)->m_BackEnd : NULL;
	CheckResult(api->m_Device->lpVtbl->CreateCommandList(api->m_Device, gpuNode, a_Descriptor->m_Type, commandList->m_Allocator, pipelineStateObject, &IID_ID3D12CommandList, (void**)&commandList->m_BackEnd));
	CheckResult(commandList->m_BackEnd->lpVtbl->Close(commandList->m_BackEnd));
	*a_Handle = commandList;
}

void GFXStartRecordingCommandList(GFXAPI a_API, GFXCommandListHandle a_CommandListHandle, GFXPipelineStateObjectHandle a_PipelineStateObjectHandle)
{
	GFX_UNUSED(a_API);
	assert(NULL != a_CommandListHandle);
	DX12CommandList *commandList = (DX12CommandList*)a_CommandListHandle;
	CheckResult(commandList->m_Allocator->lpVtbl->Reset(commandList->m_Allocator));
	ID3D12PipelineState *pipelineStateObject = (NULL != a_PipelineStateObjectHandle) ? ((DX12PipelineStateObject*)a_PipelineStateObjectHandle)->m_BackEnd : NULL;
	CheckResult(commandList->m_BackEnd->lpVtbl->Reset(commandList->m_BackEnd, commandList->m_Allocator, pipelineStateObject));
}

void GFXStopRecordingCommandList(GFXAPI a_API, GFXCommandListHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(NULL != a_Handle);
	DX12CommandList *commandList = (DX12CommandList*)a_Handle;
	CheckResult(commandList->m_BackEnd->lpVtbl->Close(commandList->m_BackEnd));
}

void GFXExecuteCommandList(GFXAPI a_API, GFXCommandListHandle a_CommandListHandle, GFXCommandQueueHandle a_CommandQueueHandle)
{
	assert(NULL != a_API);
	assert(NULL != a_CommandListHandle);
	assert(NULL != a_CommandQueueHandle);
	DX12API *api = (DX12API*)a_API;
	DX12CommandList *commandList = (DX12CommandList*)a_CommandListHandle;
	DX12CommandQueue *commandQueue = (DX12CommandQueue*)a_CommandQueueHandle;

	ID3D12CommandList *commandLists[1];
	commandLists[0] = (ID3D12CommandList*)commandList->m_BackEnd;
	commandQueue->m_BackEnd->lpVtbl->ExecuteCommandLists(commandQueue->m_BackEnd, 1, commandLists);
	CheckResult(commandQueue->m_BackEnd->lpVtbl->Signal(commandQueue->m_BackEnd, commandQueue->m_Fence, api->m_FenceValue));
}

void GFXDestroyCommandList(GFXAPI a_API, GFXCommandListHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(NULL != a_Handle);
	DX12CommandList *commandList = a_Handle;
	SAFERELEASE(commandList->m_Allocator);
	SAFERELEASE(commandList->m_BackEnd);
	DEALLOCATE(commandList);
}

void GFXCreatePipelineStateObject(GFXAPI a_API, GFXPipelineStateObjectDescriptor *a_Descriptor, GFXPipelineStateObjectHandle *a_Handle)
{
	assert(NULL != a_API);
	DX12API *api = (DX12API*)a_API;
	GFX_UNUSED(a_Descriptor);

	DX12PipelineStateObject *pipelineStateObject = ALLOCATE(DX12PipelineStateObject);

	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.NumParameters = 0;
	rootSignatureDesc.pParameters = NULL;
	rootSignatureDesc.NumStaticSamplers = 0;
	rootSignatureDesc.pStaticSamplers = NULL;
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	ID3DBlob *signature = NULL;
	ID3DBlob *error = NULL;
	CheckResult(D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error));
	void *bufferPtr = signature->lpVtbl->GetBufferPointer(signature);
	const size_t bufferSize = signature->lpVtbl->GetBufferSize(signature);
	CheckResult(api->m_Device->lpVtbl->CreateRootSignature(api->m_Device, 0, bufferPtr, bufferSize, &IID_ID3D12RootSignature, (void**)&pipelineStateObject->m_RootSignature));
	SAFERELEASE(signature);
	SAFERELEASE(error);

	D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};

	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineStateObjectDesc = { 0 };
	pipelineStateObjectDesc.pRootSignature = pipelineStateObject->m_RootSignature;
	ExtractShaderByteCodeInfo(&pipelineStateObjectDesc.VS, (DX12Shader*)a_Descriptor->m_VertexShader);
	ExtractShaderByteCodeInfo(&pipelineStateObjectDesc.PS, (DX12Shader*)a_Descriptor->m_PixelShader);
	ExtractShaderByteCodeInfo(&pipelineStateObjectDesc.DS, (DX12Shader*)a_Descriptor->m_DomainShader);
	ExtractShaderByteCodeInfo(&pipelineStateObjectDesc.HS, (DX12Shader*)a_Descriptor->m_HullShader);
	ExtractShaderByteCodeInfo(&pipelineStateObjectDesc.GS, (DX12Shader*)a_Descriptor->m_GeometryShader);
// 	pipelineStateObjectDesc.StreamOutput;
	pipelineStateObjectDesc.BlendState = ((DX12BlendState*)a_Descriptor->m_BlendState)->m_BackEnd;
 	pipelineStateObjectDesc.SampleMask = UINT_MAX;
	pipelineStateObjectDesc.RasterizerState = ((DX12RasterizerState*)a_Descriptor->m_RasterizerState)->m_BackEnd;
	pipelineStateObjectDesc.DepthStencilState.DepthEnable = FALSE;
	pipelineStateObjectDesc.DepthStencilState.StencilEnable = FALSE;
	pipelineStateObjectDesc.InputLayout.pInputElementDescs = inputElementDescs;
	pipelineStateObjectDesc.InputLayout.NumElements = 2;
// 	pipelineStateObjectDesc.IBStripCutValue;
 	pipelineStateObjectDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
 	pipelineStateObjectDesc.NumRenderTargets = 1;
	pipelineStateObjectDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
// 	pipelineStateObjectDesc.DSVFormat;
	pipelineStateObjectDesc.SampleDesc.Count = 1;
// 	pipelineStateObjectDesc.NodeMask;
// 	pipelineStateObjectDesc.CachedPSO;
// 	pipelineStateObjectDesc.Flags;

	CheckResult(api->m_Device->lpVtbl->CreateGraphicsPipelineState(api->m_Device, &pipelineStateObjectDesc, &IID_ID3D12PipelineState, (void**)&pipelineStateObject->m_BackEnd));
	*a_Handle = pipelineStateObject;
}

void GFXSetPipelineStateObject(GFXAPI a_API, GFXPipelineStateObjectHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXDestroyPipelineStateObject(GFXAPI a_API, GFXPipelineStateObjectHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(NULL != a_Handle);
	DX12PipelineStateObject *pipelineStateObject = a_Handle;
	SAFERELEASE(pipelineStateObject->m_BackEnd);
	DEALLOCATE(pipelineStateObject);
}

void GFXPrepareRenderTargetForDraw(GFXAPI a_API, GFXCommandListHandle a_CommandListHandle, GFXRenderTargetHandle a_RenderTargetHandle)
{
	assert(NULL != a_API);
	assert(NULL != a_CommandListHandle);
	assert(NULL != a_RenderTargetHandle);

	DX12API *api = (DX12API*)a_API;
	DX12CommandList *commandList = (DX12CommandList*)a_CommandListHandle;
	DX12RenderTarget *renderTarget = (DX12RenderTarget*)a_RenderTargetHandle;

	D3D12_RESOURCE_TRANSITION_BARRIER resourceTransitionBarrier = { 0 };
	resourceTransitionBarrier.pResource = renderTarget->m_BackBuffers[api->m_CurrentBackBufferIndex];
	resourceTransitionBarrier.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	resourceTransitionBarrier.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

	D3D12_RESOURCE_BARRIER resourceBarrier = { 0 };
	resourceBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	resourceBarrier.Transition = resourceTransitionBarrier;

	commandList->m_BackEnd->lpVtbl->ResourceBarrier(commandList->m_BackEnd, 1, &resourceBarrier);
}

void GFXClearRenderTarget(GFXAPI a_API, GFXCommandListHandle a_CommandListHandle, GFXRenderTargetHandle a_RenderTargetHandle, const GFXColor a_ClearColor)
{
	assert(NULL != a_API);
	assert(NULL != a_CommandListHandle);
	assert(NULL != a_RenderTargetHandle);

	DX12API *api = (DX12API*)a_API;
	DX12RenderTarget *renderTarget = (DX12RenderTarget*)a_RenderTargetHandle;
	renderTarget->m_CPUFunction(renderTarget->m_DescriptorHeap, &renderTarget->m_CPUHandle);
	renderTarget->m_CPUHandle.ptr += api->m_CurrentBackBufferIndex * api->m_DescriptorHandleInc[D3D12_DESCRIPTOR_HEAP_TYPE_RTV];;

	DX12CommandList *commandList = (DX12CommandList*)a_CommandListHandle;
	commandList->m_BackEnd->lpVtbl->ClearRenderTargetView(commandList->m_BackEnd, renderTarget->m_CPUHandle, a_ClearColor.m_F, 0, NULL);
}

void GFXPrepareRenderTargetForPresent(GFXAPI a_API, GFXCommandListHandle a_CommandListHandle, GFXRenderTargetHandle a_RenderTargetHandle)
{
	assert(NULL != a_API);
	assert(NULL != a_CommandListHandle);
	assert(NULL != a_RenderTargetHandle);

	DX12API *api = (DX12API*)a_API;
	DX12CommandList *commandList = (DX12CommandList*)a_CommandListHandle;
	DX12RenderTarget *renderTarget = (DX12RenderTarget*)a_RenderTargetHandle;

	D3D12_RESOURCE_TRANSITION_BARRIER resourceTransitionBarrier = { 0 };
	resourceTransitionBarrier.pResource = renderTarget->m_BackBuffers[api->m_CurrentBackBufferIndex];
	resourceTransitionBarrier.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	resourceTransitionBarrier.StateAfter = D3D12_RESOURCE_STATE_PRESENT;

	D3D12_RESOURCE_BARRIER resourceBarrier = { 0 };
	resourceBarrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	resourceBarrier.Transition = resourceTransitionBarrier;

	commandList->m_BackEnd->lpVtbl->ResourceBarrier(commandList->m_BackEnd, 1, &resourceBarrier);
}

#endif
