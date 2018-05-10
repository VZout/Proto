#include "Renderer.h"

// #include "Graphics/EVertexFormat.h"
#include "Graphics/Viewer/Camera.h"
// #include "Graphics/Viewer/ProjectionMatrix.h"
// #include "Math/Color.h"
// #include "Math/Matrix4.h"
#include "Platform/Debug/AssertMessage.h"
#include "Platform/Window.h"
#include "RenderPass.h"
#include "RenderTechnique.h"
#include "Scene/ModelSceneNode.h"
#include "Scene/SceneGraph.h"
#include "Scene/SceneGraphVisitor.h"
#include "Utility/HashedString.h"

USING_NAMESPACE(Graphics)
USING_NAMESPACE(Math)
USING_NAMESPACE(Platform)
USING_NAMESPACE(Utility)

BEGIN_UNNAMEDNAMESPACE()

bool OpaquePassSelector(const SceneNode &a_SceneNode)
{
	bool select = false;

	const ModelSceneNode *modelSceneNode = dynamic_cast<const ModelSceneNode*>(&a_SceneNode);
	if (nullptr != modelSceneNode)
	{
		const Model &model = modelSceneNode->GetModel();
		select = true;
		UNUSED(model);
// 		if (model.HasMeshes())
// 		{
// 			const MeshVector &meshes = model.GetMeshes();
// 			for (const auto &mesh : meshes)
// 			{
// 				select = mesh->HasMaterial();
// 			}
// 		}
	}

	return select;
}

END_UNNAMEDNAMESPACE()

Renderer::Renderer()
	: m_Camera(NULLPTR)
	, m_CurrentTechnique(NULLPTR)
{
	m_Selector = CREATE_FUNCTOR(OpaquePassSelector);
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

	m_SceneGraph = new SceneGraph(HashedString("BasicSceneGraph"));
}

void Renderer::Update(const UpdateEvent &a_UpdateEvent)
{
	AssertMessage(NULLPTR != m_SceneGraph, "Attempt to use an invalid scene graph!");
	m_SceneGraph->Update(a_UpdateEvent);

	if (NULLPTR != m_CurrentTechnique)
	{
		for (RenderTechnique::RenderPassListIt pos = m_CurrentTechnique->GetPassListBegin(); pos != m_CurrentTechnique->GetPassListEnd(); ++pos)
		{
			RenderPass &renderPass = **pos;
			renderPass.Update();
		}
	}
}

void Renderer::BeginRender()
{
	AssertMessage(m_Selector.IsBound(), "Renderable selector function not bound!");
	m_SceneNodes.clear();
	SceneGraphVisitor visitor(m_SceneNodes, m_Selector);
	m_SceneGraph->Accept(visitor);

	// for each render pass in the technique
		// select objects to render
		// record command list
// 	GFXStartRecordingCommandList(g_API, g_CommandList, g_PipelineStateObject);
// 	GFXPrepareRenderTargetForDraw(g_API, g_CommandList, g_RenderTarget);
// 
// 	GFXColor clearColor = { 100.0f / 255.0f, 149.0f / 255.0f, 237.0f / 255.0f, 1.0f };
// 	GFXClearRenderTarget(g_API, g_CommandList, g_RenderTarget, clearColor);
// 
// 	GFXPrepareRenderTargetForPresent(g_API, g_CommandList, g_RenderTarget);
// 	GFXStopRecordingCommandList(g_API, g_CommandList);
}

void Renderer::Render()
{
	if (NULLPTR != m_CurrentTechnique)
	{
		for (RenderTechnique::RenderPassListConstIt pos = m_CurrentTechnique->GetPassListBegin(); pos != m_CurrentTechnique->GetPassListEnd(); ++pos)
		{
			const RenderPass &renderPass = **pos;
			UNUSED(renderPass);
			// for every renderpass
				// set render target, and
				// execute command list
			// 	GFXExecuteCommandList(g_API, g_CommandList, g_CommandQueue);
			// 	GFXPresent(g_API, g_SwapChain);
			// 	GFXWaitForCommandQueueCompletion(g_API, g_CommandQueue);
		}
	}
}

void Renderer::EndRender()
{
	//GFXPresent(m_API, m_SwapChain);
}

void Renderer::Terminate()
{
	delete m_Camera;
}