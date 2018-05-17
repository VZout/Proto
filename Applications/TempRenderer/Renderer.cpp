#include "Renderer.h"

// #include "Graphics/EVertexFormat.h"
#include "Graphics/Model.h"
#include "Graphics/Viewer/Camera.h"
// #include "Graphics/Viewer/ProjectionMatrix.h"
// #include "Math/Color.h"
// #include "Math/Matrix4.h"
#include "Platform/Debug/AssertMessage.h"
#include "Platform/Window.h"
#include "RenderPass.h"
#include "RenderingTechnique.h"
#include "Resources/ResourceManager.h"
#include "Scene/ModelSceneNode.h"
#include "Scene/SceneGraph.h"
#include "Scene/SceneGraphVisitor.h"
#include "Techniques/ForwardRendering.h"
#include "Utility/HashedString.h"

USING_NAMESPACE(Graphics)
USING_NAMESPACE(Math)
USING_NAMESPACE(Platform)
USING_NAMESPACE(Resources)
USING_NAMESPACE(Utility)

BEGIN_UNNAMEDNAMESPACE()

void LoadModel(GFXAPI a_API, float a_AspectRatio)
{
	std::vector<float> vertices;
	vertices.push_back(0.0f); vertices.push_back(0.25f * a_AspectRatio); vertices.push_back(0.0f);
	vertices.push_back(1.0f); vertices.push_back(0.0f); vertices.push_back(0.0f); vertices.push_back(1.0f);
	vertices.push_back(0.25f); vertices.push_back(-0.25f * a_AspectRatio); vertices.push_back(0.0f);
	vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(0.0f); vertices.push_back(1.0f);
	vertices.push_back(-0.25f); vertices.push_back(-0.25f * a_AspectRatio); vertices.push_back(0.0f);
	vertices.push_back(0.0f); vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(1.0f);
	const uint32_t vertexBufferByteSize = static_cast<uint32_t>(vertices.size() * sizeof(float));


	Mesh *mesh = new Mesh();
	GFXVertexBufferDescriptor vertexBufferDescriptor{};
	vertexBufferDescriptor.m_ByteOffset = 0;
	vertexBufferDescriptor.m_DataByteSize = vertexBufferByteSize;
	vertexBufferDescriptor.m_Stride = 7 * sizeof(float);
	vertexBufferDescriptor.m_Vertices = &vertices.data()[0];
	GFXCreateVertexBuffer(a_API, &vertexBufferDescriptor, &mesh->m_VertexBuffer);

	Model *model = new Model();
	model->m_Meshes.push_back(mesh);

	//ResourceManager &resourceManager = GetResourceManager();
	//resourceManager.Add(model, HashedString("TempModel"));
}

END_UNNAMEDNAMESPACE()

Renderer::Renderer()
	: m_Camera(NULLPTR)
	, m_CurrentTechnique(NULLPTR)
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

// 
// 	const uint32_t slices = 32;
// 	const uint32_t stacks = 32;
// 	GenerateSphere(m_API, m_Sphere, 1.0f, slices, stacks, EVertexFormat_Position);
// 	GenerateSphere(m_API, m_SphereTexLit, 1.0f, slices, stacks, EVertexFormat_Position | EVertexFormat_Texture_0 | EVertexFormat_Normal);

	GFXAPIDescriptor descriptor = { 0 };
	descriptor.m_FrameBufferWidth = windowSize.m_Width;
	descriptor.m_FrameBufferHeight = windowSize.m_Height;
	descriptor.m_WindowHandle = a_Window.GetHandle();
	descriptor.m_UseSoftwareDevice = false;
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
#elif defined(GFX_API_OPENGL)
	descriptor.m_OpenGLMajorVerion = 3;
	descriptor.m_OpenGLMinorVersion = 3;
#endif
	GFXInitialize(&m_API, NULLPTR, &descriptor);

	GFXCommandQueueDescriptor commandQueueDescriptor;
	commandQueueDescriptor.m_Flags = CommandQueueFlags_None;
	commandQueueDescriptor.m_Type = CommandListType_Direct;
	GFXCreateCommandQueue(m_API, &commandQueueDescriptor, &m_CommandQueue);

	GFXSwapChainDescriptor swapChainDescriptor;
	swapChainDescriptor.m_CommandQueue = m_CommandQueue;
	swapChainDescriptor.m_FrameBufferWidth = windowSize.m_Width;
	swapChainDescriptor.m_FrameBufferHeight = windowSize.m_Height;
	swapChainDescriptor.m_EnableMSAA = false;
	// 	swapChainDescriptor.m_MSAASampleCount = 1;
	// 	swapChainDescriptor.m_MSAAQuality = 0;
	swapChainDescriptor.m_BufferCount = 2;
	swapChainDescriptor.m_Fullscreen = false;
	swapChainDescriptor.m_VSync = false;
	GFXCreateSwapChain(m_API, &swapChainDescriptor, &m_SwapChain);

	GFXRenderTargetDescriptor renderTargetDescriptor;
	renderTargetDescriptor.m_SwapChain = m_SwapChain;
	renderTargetDescriptor.m_Width = windowSize.m_Width;
	renderTargetDescriptor.m_Height = windowSize.m_Height;
	GFXCreateRenderTarget(m_API, &renderTargetDescriptor, &m_RenderTarget);

	m_ResourceManager = new ResourceManager(m_API);
	m_ResourceManager->Initialize();

	m_CurrentTechnique = new ForwardRenderingTechnique(m_API, m_RenderTarget);
	m_CurrentTechnique->Initialize(*m_ResourceManager);
	m_SceneGraph = new SceneGraph(HashedString("BasicSceneGraph"));
	
	LoadModel(m_API, aspectRatio);

	//ResourceManager &resourceManager = GetResourceManager();
	//Model *model = reinterpret_cast<Model*>(resourceManager.Get(HashedString("TempModel")));
	//ModelSceneNode *node = new ModelSceneNode(*model);
	//m_SceneGraph->AddNode(*node);
}

void Renderer::Update(const UpdateEvent &a_UpdateEvent)
{
	AssertMessage(NULLPTR != m_SceneGraph, "Attempt to use an invalid scene graph!");
	m_SceneGraph->Update(a_UpdateEvent);
}

void Renderer::BeginRender()
{
	if (NULLPTR != m_CurrentTechnique)
	{
		for (RenderingTechnique::RenderPassListIt pos = m_CurrentTechnique->GetPassListBegin(); pos != m_CurrentTechnique->GetPassListEnd(); ++pos)
		{
			RenderPass &renderPass = **pos;
			renderPass.Prepare(*m_SceneGraph);
		}
	}
}

void Renderer::Render()
{
	if (NULLPTR != m_CurrentTechnique)
	{
		for (RenderingTechnique::RenderPassListIt pos = m_CurrentTechnique->GetPassListBegin(); pos != m_CurrentTechnique->GetPassListEnd(); ++pos)
		{
			RenderPass &renderPass = **pos;
			renderPass.Execute(m_CommandQueue);
		}
	}
}

void Renderer::EndRender()
{
	GFXPresent(m_API, m_SwapChain);
	GFXWaitForCommandQueueCompletion(m_API, m_CommandQueue);
}

void Renderer::Terminate()
{
	delete m_ResourceManager;
	delete m_Camera;
	delete m_SceneGraph;
	delete m_CurrentTechnique;

	GFXDestroyRenderTarget(m_API, m_RenderTarget);
	GFXDestroySwapChain(m_API, m_SwapChain);
	GFXDestroyCommandQueue(m_API, m_CommandQueue);
	GFXTerminate(m_API);
}