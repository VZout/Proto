#include "Renderer.h"

#include "GenerateGeometry.h"
#include "Graphics/EVertexFormat.h"
#include "Graphics/Viewer/Camera.h"
#include "Graphics/Viewer/ProjectionMatrix.h"
#include "Math/Color.h"
#include "Math/Matrix4.h"
#include "Platform/Debug/AssertMessage.h"
#include "Platform/Window.h"
// #include "ResourceLoading.h"

USING_NAMESPACE(Graphics)
USING_NAMESPACE(Math)
USING_NAMESPACE(Platform)

BEGIN_UNNAMEDNAMESPACE()

uint32_t CalculateStride(uint32_t a_VertexFormat)
{
	uint32_t stride = (a_VertexFormat & EVertexFormat_Position ? 3 * sizeof(float) : 0);
	stride += (a_VertexFormat & EVertexFormat_Texture_0 ? 2 * sizeof(float) : 0);
	stride += (a_VertexFormat & EVertexFormat_Normal ? 3 * sizeof(float) : 0);
	stride += (a_VertexFormat & EVertexFormat_Tangent ? 3 * sizeof(float) : 0);
	stride += (a_VertexFormat & EVertexFormat_Bitangent ? 3 * sizeof(float) : 0);		
	return stride;
}

void CreateInputLayout(GFXAPI a_API, GFXShaderHandle a_Shader, GFXInputLayoutHandle *a_InputLayout, uint32_t a_VertexFormat)
{
	GFXInputLayoutElementDescriptor inputLayout[EVertexFormat_Count];
	const uint32_t stride = CalculateStride(a_VertexFormat);

	uint32_t index = 0;
	if (EVertexFormat_Position & a_VertexFormat)
	{
		inputLayout[index++] = { "in_Position", index, 3, DataType_Float, false, stride };
	}
	if (EVertexFormat_Texture_0 & a_VertexFormat)
	{
		inputLayout[index++] = { "in_TexCoord0", index, 2, DataType_Float, false, stride };
	}
	if (EVertexFormat_Normal & a_VertexFormat)
	{
		inputLayout[index++] = { "in_Normal", index, 3, DataType_Float, false, stride };
	}
	if (EVertexFormat_Tangent & a_VertexFormat)
	{
		inputLayout[index++] = { "in_Tangent", index, 3, DataType_Float, false, stride };
	}
	if (EVertexFormat_Bitangent & a_VertexFormat)
	{
		inputLayout[index++] = { "in_Bitangent", index, 3, DataType_Float, false, stride };
	}
	
	GFXInputLayoutDescriptor inputLayoutDescriptor;
	inputLayoutDescriptor = { inputLayout, index, stride, a_Shader };
	GFXCreateInputLayout(a_API, &inputLayoutDescriptor, a_InputLayout);
}

END_UNNAMEDNAMESPACE()

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Initialize(Window &a_Window)
{
	const Dimension &windowSize = a_Window.GetSize();

	const float fovY = 60.0f;
	const float aspectRatio = static_cast<float>(windowSize.m_Width) / windowSize.m_Height;
	const float nearZ = 0.01f;
	const float farZ = 10000.0f;
	m_Camera = new Camera();
	m_Camera->CreatePerspectiveLens(fovY, aspectRatio, nearZ, farZ);
	m_Camera->SetLookAt(Vector3(0.0f, 0.0f, 10.0f), Vector3::ORIGIN, Vector3::Y_AXIS);

	GFXAPIDescriptor descriptor;
	descriptor.m_FrameBufferHeight = 720;
	descriptor.m_FrameBufferWidth = 1280;
	descriptor.m_WindowHandle = a_Window.GetHandle();

// 	GFXParameterHandle parameters {};
// 	GFXInitialize(&m_API, 0, &descriptor, parameters);
// 	m_EarthTexture = LoadTexture(m_API, "Textures/earth.png");
// 	m_MoonTexture = LoadTexture(m_API, "Textures/moon.png");
// 	m_SimpleShader = LoadShader(m_API, "Shaders/simpleShader.vert", "Shaders/simpleShader.frag");

// 	m_DiffuseShader = LoadShader(m_API, "Shaders/texturedDiffuse.vert", "Shaders/texturedDiffuse.frag");

	m_ClearColor = { Color::CornflowerBlue.GetR(), Color::CornflowerBlue.GetG(), Color::CornflowerBlue.GetB(), Color::CornflowerBlue.GetA() };

	GFXViewportDescriptor viewportDescriptor;
	viewportDescriptor.m_X = 0;
	viewportDescriptor.m_Y = 0;
	viewportDescriptor.m_Width = windowSize.m_Width;
	viewportDescriptor.m_Height = windowSize.m_Height;
	GFXCreateViewport(m_API, &viewportDescriptor, &m_Viewport);

	GFXRenderTargetDescriptor renderTargetDescriptor;
	renderTargetDescriptor.m_Width = windowSize.m_Width;
	renderTargetDescriptor.m_Height = windowSize.m_Height;
	GFXCreateRenderTarget(m_API, &renderTargetDescriptor, &m_RenderTarget);

	{
		GFXConstantBufferElementDescriptor constantBuffer[] = {
			"u_ModelMatrix", 16 * sizeof(float), DataType_Float, false,
			"u_ViewMatrix", 16 * sizeof(float), DataType_Float, false,
			"u_ProjectionMatrix", 16 * sizeof(float), DataType_Float, false
		};
		GFXConstantBufferDescriptor constantBufferDescriptor;
		constantBufferDescriptor = {
			3 * 16 * sizeof(float), constantBuffer, 3
		};
#if !defined(NDEBUG)
		constantBufferDescriptor.m_DebugName = "MatrixConstantBuffer";
#endif
		GFXCreateConstantBuffer(m_API, &constantBufferDescriptor, &m_MatrixConstantBuffer);
	}

	{
		GFXConstantBufferElementDescriptor constantBuffer[] = {
			"u_MaterialEmissive", 4 * sizeof(float), DataType_Float, false,
			"u_MaterialDiffuse", 4 * sizeof(float), DataType_Float, false,
			"u_MaterialSpecular", 4 * sizeof(float), DataType_Float, false,
			"u_MaterialShininess", sizeof(float), DataType_Float, false
		};
		GFXConstantBufferDescriptor constantBufferDescriptor;
		constantBufferDescriptor = {
			(1 + 3 * 4) * sizeof(float), constantBuffer, 4
		};
#if !defined(NDEBUG)
		constantBufferDescriptor.m_DebugName = "MaterialConstantBuffer";
#endif
		GFXCreateConstantBuffer(m_API, &constantBufferDescriptor, &m_MaterialConstantBuffer);
	}

	{
		GFXConstantBufferElementDescriptor constantBuffer[] = {
			"u_EyePosW", 4 * sizeof(float), DataType_Float, false,
			"u_Ambient", 4 * sizeof(float), DataType_Float, false,
			"u_LightPosW", 4 * sizeof(float), DataType_Float, false,
			"u_LightColor", 4 * sizeof(float), DataType_Float, false
		};
		GFXConstantBufferDescriptor constantBufferDescriptor;
		constantBufferDescriptor = {
			4 * 4 * sizeof(float), constantBuffer, 4
		};
#if !defined(NDEBUG)
		constantBufferDescriptor.m_DebugName = "LightConstantBuffer";
#endif
		GFXCreateConstantBuffer(m_API, &constantBufferDescriptor, &m_LightConstantBuffer);
	}

	CreateInputLayout(m_API, m_SimpleShader, &m_SimpleShaderInputLayout, EVertexFormat_Position);
	CreateInputLayout(m_API, m_DiffuseShader, &m_DiffuseShaderInputLayout, EVertexFormat_Position | EVertexFormat_Normal | EVertexFormat_Texture_0);

	GFXRasterizerStateDescriptor rasterizerStateDescriptor;
	rasterizerStateDescriptor.m_FillMode = FillMode_Solid;
	rasterizerStateDescriptor.m_Handedness = Handedness_Right;
	GFXCreateRasterizerState(m_API, &rasterizerStateDescriptor, &m_RasterizerState);

	GFXPipelineStateObjectDescriptor pipelineStateObjectDescriptor = { 0 };
// 	pipelineStateObjectDescriptor.m_Shader = m_SimpleShader;
// 	pipelineStateObjectDescriptor.m_RasterizerState = m_RasterizerState;
// 	pipelineStateObjectDescriptor.m_RenderTarget = m_RenderTarget;
// 	pipelineStateObjectDescriptor.m_InputLayout = m_SimpleShaderInputLayout;
	GFXCreatePipelineStateObject(m_API, &pipelineStateObjectDescriptor, &m_PipelineStateObject);

	GFXSamplerStateDescriptor samplerStateDescriptor;
	GFXCreateSamplerState(m_API, &samplerStateDescriptor, &m_SamplerState);

	GFXSwapChainDescriptor swapChainDescriptor = { 0 };
	swapChainDescriptor.m_FrameBufferWidth = windowSize.m_Width;
	swapChainDescriptor.m_FrameBufferHeight = windowSize.m_Height;
	swapChainDescriptor.m_BufferCount = 1;
	swapChainDescriptor.m_EnableMSAA = false;
	swapChainDescriptor.m_Fullscreen = false;
	swapChainDescriptor.m_VSync = true;
	GFXCreateSwapChain(m_API, &swapChainDescriptor, &m_SwapChain);

// 	GFXCommandListDescriptor commandListDescriptor = { 0 };
// 	commandListDescriptor.m_RenderMode = RenderMode_Triangles;
// 	commandListDescriptor.m_PipelineStateObject = m_PipelineStateObject;
// 	GFXConstantBufferHandle constantBuffers[] = {
// 		m_MatrixConstantBuffer
// 	};
// 	commandListDescriptor.m_ConstantBuffers = constantBuffers;
// 	commandListDescriptor.m_NumConstantBuffers = 1;
// 	commandListDescriptor.m_SamplerState = m_SamplerState;
// 	GFXCreateCommandList(m_API, &commandListDescriptor, &m_CommandList);

	const uint32_t slices = 32;
	const uint32_t stacks = 32;
	GenerateSphere(m_API, m_Sphere, 1.0f, slices, stacks, EVertexFormat_Position);
	GenerateSphere(m_API, m_SphereTexLit, 1.0f, slices, stacks, EVertexFormat_Position | EVertexFormat_Texture_0 | EVertexFormat_Normal);
}

void Renderer::Update()
{
}

void Renderer::Render()
{
// 	GFXClearRenderTarget(m_API, m_RenderTarget, m_ClearColor);
// 
// 	const Matrix4 &projectionMatrix = m_Camera->GetProjectionMatrix().GetMatrix();
// 	const Matrix4 &viewMatrix = m_Camera->GetViewMatrix();
// 
// 	GFXCopyConstantBufferData(m_API, m_MatrixConstantBuffer, "u_ProjectionMatrix", projectionMatrix.f);
// 	GFXCopyConstantBufferData(m_API, m_MatrixConstantBuffer, "u_ViewMatrix", viewMatrix.f);
// 
// 	// draw earth
// 	{
// 		const Math::Matrix4 modelMatrix = Matrix4();
// 		GFXCopyConstantBufferData(m_API, m_MatrixConstantBuffer, "u_ModelMatrix", modelMatrix.f);
// 
// 		GFXCommandListDescriptor commandListDescriptor = { 0 };
// 		commandListDescriptor.m_IndexBuffer = m_SphereTexLit.m_IndexBuffer;
// 		commandListDescriptor.m_VertexBuffer = m_SphereTexLit.m_VertexBuffer;
// 		commandListDescriptor.m_DiffuseTexture = m_EarthTexture;
// 		commandListDescriptor.m_Viewport = m_Viewport;
// 		GFXUpdateCommandList(m_API, &commandListDescriptor, m_CommandList);
// 
// 		GFXSetPipelineStateObject(m_API, m_PipelineStateObject);
// 
// 		AssertMessage(m_SphereTexLit.m_NumIndices != 0, "Invalid number of indices to render!");
// 		GFXDrawIndexed(m_API, m_CommandList, m_SphereTexLit.m_NumIndices);
// 	}
// 
// 	// draw moon
// 	{
// 		const Math::Matrix4 modelMatrix = Matrix4();
// 		GFXCopyConstantBufferData(m_API, m_MatrixConstantBuffer, "u_ModelMatrix", modelMatrix.f);
// 
// 		GFXCommandListDescriptor commandListDescriptor = { 0 };
// 		commandListDescriptor.m_IndexBuffer = m_SphereTexLit.m_IndexBuffer;
// 		commandListDescriptor.m_VertexBuffer = m_SphereTexLit.m_VertexBuffer;
// 		commandListDescriptor.m_DiffuseTexture = m_MoonTexture;
// 		commandListDescriptor.m_Viewport = m_Viewport;
// 		GFXUpdateCommandList(m_API, &commandListDescriptor, m_CommandList);
// 
// 		GFXSetPipelineStateObject(m_API, m_PipelineStateObject);
// 
// 		AssertMessage(m_SphereTexLit.m_NumIndices != 0, "Invalid number of indices to render!");
// 		GFXDrawIndexed(m_API, m_CommandList, m_SphereTexLit.m_NumIndices);
// 	}

// 	// draw light
// 	{
// 		const Math::Matrix4 modelMatrix = Matrix4();
// 		GFXCopyConstantBufferData(m_API, m_MatrixConstantBuffer, "u_ModelMatrix", modelMatrix.f);
// 
// 		GFXCommandListDescriptor commandListDescriptor = { 0 };
// 		commandListDescriptor.m_IndexBuffer = m_Sphere.m_IndexBuffer;
// 		commandListDescriptor.m_VertexBuffer = m_Sphere.m_VertexBuffer;
// 		commandListDescriptor.m_Viewport = m_Viewport;
// 		GFXUpdateCommandList(m_API, &commandListDescriptor, m_CommandList);
// 
// 		GFXSetPipelineStateObject(m_API, m_PipelineStateObject);
// 
// 		AssertMessage(m_Sphere.m_NumIndices != 0, "Invalid number of indices to render!");
// 		GFXDrawIndexed(m_API, m_CommandList, m_Sphere.m_NumIndices);
// 	}
// 
// 	GFXPresent(m_API, m_SwapChain);
}

void Renderer::Terminate()
{
	GFXDestroyViewport(m_API, m_Viewport);
	GFXDestroySwapChain(m_API, m_SwapChain);
	GFXDestroyRenderTarget(m_API, m_RenderTarget);
	GFXDestroyTexture(m_API, m_EarthTexture);
	GFXDestroyTexture(m_API, m_MoonTexture);
	GFXDestroyShader(m_API, m_SimpleShader);
	GFXDestroyShader(m_API, m_DiffuseShader);
	GFXDestroyConstantBuffer(m_API, m_MatrixConstantBuffer);
	GFXDestroyConstantBuffer(m_API, m_MaterialConstantBuffer);
	GFXDestroyConstantBuffer(m_API, m_LightConstantBuffer);

	GFXDestroyRasterizerState(m_API, m_RasterizerState);
	GFXDestroyPipelineStateObject(m_API, m_PipelineStateObject);
	GFXDestroySamplerState(m_API, m_SamplerState);
	GFXDestroyCommandList(m_API, m_CommandList);
	GFXDestroyInputLayout(m_API, m_SimpleShaderInputLayout);
	GFXDestroyInputLayout(m_API, m_DiffuseShaderInputLayout);
	GFXDestroyVertexBuffer(m_API, m_Sphere.m_VertexBuffer);
	GFXDestroyIndexBuffer(m_API, m_Sphere.m_IndexBuffer);
	GFXDestroyVertexBuffer(m_API, m_SphereTexLit.m_VertexBuffer);
	GFXDestroyIndexBuffer(m_API, m_SphereTexLit.m_IndexBuffer);

	GFXTerminate(m_API);

	delete m_Camera;
}