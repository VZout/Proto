#include "Proto.h"

#include "Graphics/API/GFX.h"
#include "Platform/Debug/AssertMessage.h"
#include "Platform/Window.h"
#include "Renderer.h"
#include "Utility/UpdateEvent.h"

#include <algorithm>
#include <vector>

#if defined(PROTO_PLATFORM_WIN32)
#include <vld.h>

#pragma comment(lib, "winmm")
#endif

USING_NAMESPACE(Platform)
USING_NAMESPACE(Utility)

namespace
{
	GFXAPI g_API = { 0 };
	GFXSwapChainHandle g_SwapChain = { 0 };
	GFXCommandQueueHandle g_CommandQueue = { 0 };
	GFXCommandListHandle g_CommandList = { 0 };
	GFXRenderTargetHandle g_RenderTarget = { 0 };
	GFXShaderHandle g_VertexShader = { 0 };
	GFXShaderHandle g_PixelShader = { 0 };
	GFXPipelineStateObjectHandle g_PipelineStateObject = { 0 };

	const uint32_t windowWidth = 1280;
	const uint32_t windowHeight = 720;
}

void LoadModel()
{
// 	// Define the geometry for a triangle.
// 	Vertex triangleVertices[] =
// 	{
// 		{ { 0.0f, 0.25f * m_aspectRatio, 0.0f },{ 1.0f, 0.0f, 0.0f, 1.0f } },
// 		{ { 0.25f, -0.25f * m_aspectRatio, 0.0f },{ 0.0f, 1.0f, 0.0f, 1.0f } },
// 		{ { -0.25f, -0.25f * m_aspectRatio, 0.0f },{ 0.0f, 0.0f, 1.0f, 1.0f } }
// 	};
// 
// 	const UINT vertexBufferSize = sizeof(triangleVertices);
// 
// 	// Note: using upload heaps to transfer static data like vert buffers is not 
// 	// recommended. Every time the GPU needs it, the upload heap will be marshalled 
// 	// over. Please read up on Default Heap usage. An upload heap is used here for 
// 	// code simplicity and because there are very few verts to actually transfer.
// 	ThrowIfFailed(m_device->CreateCommittedResource(
// 		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
// 		D3D12_HEAP_FLAG_NONE,
// 		&CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize),
// 		D3D12_RESOURCE_STATE_GENERIC_READ,
// 		nullptr,
// 		IID_PPV_ARGS(&m_vertexBuffer)));
// 
// 	// Copy the triangle data to the vertex buffer.
// 	UINT8* pVertexDataBegin;
// 	CD3DX12_RANGE readRange(0, 0);		// We do not intend to read from this resource on the CPU.
// 	ThrowIfFailed(m_vertexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin)));
// 	memcpy(pVertexDataBegin, triangleVertices, sizeof(triangleVertices));
// 	m_vertexBuffer->Unmap(0, nullptr);
// 
// 	// Initialize the vertex buffer view.
// 	m_vertexBufferView.BufferLocation = m_vertexBuffer->GetGPUVirtualAddress();
// 	m_vertexBufferView.StrideInBytes = sizeof(Vertex);
// 	m_vertexBufferView.SizeInBytes = vertexBufferSize;

	const float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
	std::vector<float> vertices;
	vertices.push_back(0.0f); vertices.push_back(0.25f * aspectRatio); vertices.push_back(0.0f); 
	vertices.push_back(1.0f); vertices.push_back(0.0f); vertices.push_back(0.0f); vertices.push_back(1.0f);
	vertices.push_back(0.25f); vertices.push_back(-0.25f * aspectRatio); vertices.push_back(0.0f); 
	vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(0.0f); vertices.push_back(1.0f);	
	vertices.push_back(-0.25f); vertices.push_back(-0.25f * aspectRatio); vertices.push_back(0.0f);
	vertices.push_back(0.0f); vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(1.0f);

// 	GFXVertexBufferDescriptor vertexBufferDescriptor { };
// 	vertexBufferDescriptor.m_ByteOffset;
// 	vertexBufferDescriptor.m_DataByteSize;
// 	vertexBufferDescriptor.m_Usage;
// 	vertexBufferDescriptor.m_Vertices = &vertices.data()[0];
// 	GFXVertexBufferHandle vertexBuffer;
// 	GFXCreateVertexBuffer(g_API, &vertexBufferDescriptor, &vertexBuffer);
}

void PopulateCommandList()
{
	GFXStartRecordingCommandList(g_API, g_CommandList, g_PipelineStateObject);
	GFXPrepareRenderTargetForDraw(g_API, g_CommandList, g_RenderTarget);

	GFXColor clearColor = { 100.0f / 255.0f, 149.0f / 255.0f, 237.0f / 255.0f, 1.0f };
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
	GFXWaitForCommandQueueCompletion(g_API, g_CommandQueue);
}

int main(int a_ArgC, const char * a_ArgV[])
{
	UNUSED(a_ArgC);
	UNUSED(a_ArgV);

	Window window(std::wstring(L"Forward rendering").c_str(), windowWidth, windowHeight);
	window.Show(EWindowState_Show);

	Renderer renderer;
	renderer.Initialize(window);

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

	GFXAPIDescriptor descriptor = { 0 };
	descriptor.m_FrameBufferHeight = 720;
	descriptor.m_FrameBufferWidth = 1280;
	descriptor.m_WindowHandle = window.GetHandle();
	descriptor.m_UseSoftwareDevice = false;
	GFXInitialize(&g_API, NULLPTR, &descriptor);

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

	const char *shaderSource = "struct PSInput"
		"{"
		"	float4 position : SV_POSITION;"
		"	float4 color : COLOR;"
		"};"
		"PSInput VSMain(float4 position : POSITION, float4 color : COLOR)"
		"{"
		"	PSInput result;"
		"	result.position = position;"
		"	result.color = color;"
		"	return result;"
		"}"
		"float4 PSMain(PSInput input) : SV_TARGET"
		"{"
		"	return input.color;"
		"}";

	GFXShaderDescriptor shaderDescriptor;
	shaderDescriptor.m_Type = ShaderType_VertexShader;
	shaderDescriptor.m_Source = shaderSource;
	shaderDescriptor.m_EntryPoint = "VSMain";
	GFXCreateShader(g_API, &shaderDescriptor, &g_VertexShader);

	shaderDescriptor.m_Type = ShaderType_FragmentShader;
	shaderDescriptor.m_Source = shaderSource;
	shaderDescriptor.m_EntryPoint = "PSMain";
	GFXCreateShader(g_API, &shaderDescriptor, &g_PixelShader);

	GFXRasterizerStateDescriptor rasterizerStateDescriptor;
	GFXRasterizerStateHandle rasterizerState;
	GFXCreateRasterizerState(g_API, &rasterizerStateDescriptor, &rasterizerState);

	GFXBlendStateDescriptor blendStateDescriptor;
	GFXBlendStateHandle blendState;
	GFXCreateBlendState(g_API, &blendStateDescriptor, &blendState);

	GFXPipelineStateObjectDescriptor pipelineStateObjectDescriptor = { 0 };
	pipelineStateObjectDescriptor.m_VertexShader = g_VertexShader;
	pipelineStateObjectDescriptor.m_PixelShader = g_PixelShader;
	pipelineStateObjectDescriptor.m_RasterizerState = rasterizerState;
	pipelineStateObjectDescriptor.m_BlendState = blendState;
	GFXCreatePipelineStateObject(g_API, &pipelineStateObjectDescriptor, &g_PipelineStateObject);

	GFXCommandListDescriptor commandListDescriptor;
	commandListDescriptor.m_PipelineStateObject = g_PipelineStateObject;
	commandListDescriptor.m_Type = CommandListType_Direct;
	GFXCreateCommandList(g_API, &commandListDescriptor, &g_CommandList);

	int ret = 0;
#if defined(PROTO_PLATFORM_WIN32)
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

			renderer.Update(UpdateEvent(deltaTime));
			renderer.BeginRender();
			renderer.Render();
			renderer.EndRender();
		}
	}
	ret = static_cast<int>(msg.wParam);
#endif

	renderer.Terminate();

	GFXDestroyPipelineStateObject(g_API, g_PipelineStateObject);
	GFXDestroyRasterizerState(g_API, rasterizerState);
	GFXDestroyBlendState(g_API, blendState);
	GFXDestroyShader(g_API, g_VertexShader);
	GFXDestroyShader(g_API, g_PixelShader);
	GFXDestroyCommandList(g_API, g_CommandList);
	GFXDestroyRenderTarget(g_API, g_RenderTarget);
	GFXDestroySwapChain(g_API, g_SwapChain);
	GFXDestroyCommandQueue(g_API, g_CommandQueue);
	GFXTerminate(g_API);

	return ret;
}
