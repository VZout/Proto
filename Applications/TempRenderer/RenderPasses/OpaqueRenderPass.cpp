#include "OpaqueRenderPass.h"

#include "Graphics/Mesh.h"
#include "Graphics/Model.h"
#include "Platform/Debug/AssertMessage.h"
#include "../Resources/LoadResources.h"
#include "../Resources/ResourceManager.h"
#include "../Scene/ModelSceneNode.h"
#include "../Scene/SceneGraph.h"
#include "../Scene/SceneGraphVisitor.h"
#include "../Resources/Resources/ShaderResource.h"
#include "Utility/HashedString.h"

USING_NAMESPACE(Graphics)
USING_NAMESPACE(Platform)
USING_NAMESPACE(Resources)
USING_NAMESPACE(Utility)

BEGIN_UNNAMEDNAMESPACE()

bool OpaquePassSelector(const SceneNode &a_SceneNode)
{
	bool select = false;

	const ModelSceneNode *modelSceneNode = dynamic_cast<const ModelSceneNode*>(&a_SceneNode);
	if (nullptr != modelSceneNode)
	{
		const Model &model = modelSceneNode->GetModel();
		if (model.HasMeshes())
		{
			const MeshVector &meshes = model.GetMeshes();
			for (const auto &mesh : meshes)
			{
				UNUSED(mesh);
				select = true; // mesh->HasMaterial();
			}
		}
	}

	return select;
}

END_UNNAMEDNAMESPACE()

OpaqueRenderPass::OpaqueRenderPass(GFXAPI a_API, GFXRenderTargetHandle a_RenderTarget)
	: RenderPass(a_API, a_RenderTarget)
{
	m_Selector = CREATE_FUNCTOR(OpaquePassSelector);
}

OpaqueRenderPass::~OpaqueRenderPass()
{
}

void OpaqueRenderPass::Initialize(ResourceManager &a_ResourceManager)
{
	const std::string shaderFilename("TempShader.shader");
	a_ResourceManager.AddResource(shaderFilename, shaderFilename);

	GFXRasterizerStateDescriptor rasterizerStateDescriptor;
	rasterizerStateDescriptor.m_FillMode = FillMode_Solid;
	rasterizerStateDescriptor.m_Handedness = Handedness_Right;
	GFXRasterizerStateHandle rasterizerState;
	GFXCreateRasterizerState(m_API, &rasterizerStateDescriptor, &rasterizerState);

	GFXBlendStateDescriptor blendStateDescriptor;
	blendStateDescriptor.m_Factor[0] = 0.0f;
	blendStateDescriptor.m_Factor[1] = 0.0f;
	blendStateDescriptor.m_Factor[2] = 0.0f;
	blendStateDescriptor.m_Factor[3] = 0.0f;
	blendStateDescriptor.m_SampleMask = 0;
	GFXBlendStateHandle blendState;
	GFXCreateBlendState(m_API, &blendStateDescriptor, &blendState);

	const uint32_t windowWidth = 1280;
	const uint32_t windowHeight = 720;
	GFXViewportDescriptor viewportDescriptor;
	viewportDescriptor.m_X = 0;
	viewportDescriptor.m_Y = 0;
	viewportDescriptor.m_Width = windowWidth;
	viewportDescriptor.m_Height = windowHeight;
	GFXCreateViewport(m_API, &viewportDescriptor, &m_Viewport);

	GFXScissorRectDescriptor scissorRectDescriptor;
	scissorRectDescriptor.m_X = 0;
	scissorRectDescriptor.m_Y = 0;
	scissorRectDescriptor.m_Width = windowWidth;
	scissorRectDescriptor.m_Height = windowHeight;
	GFXCreateScissorRect(m_API, &scissorRectDescriptor, &m_ScissorRect);

	GFXPipelineStateObjectDescriptor pipelineStateObjectDescriptor = { 0 };
	const ShaderResource &shaderResource = a_ResourceManager.GetResource<ShaderResource>(HashedString("TempShader.shader"));
	pipelineStateObjectDescriptor.m_VertexShader = shaderResource.m_VertexShader;
	pipelineStateObjectDescriptor.m_PixelShader = shaderResource.m_PixelShader;
	pipelineStateObjectDescriptor.m_RasterizerState = rasterizerState;
	pipelineStateObjectDescriptor.m_BlendState = blendState;
	pipelineStateObjectDescriptor.m_Viewport = m_Viewport;
	pipelineStateObjectDescriptor.m_ScissorRect = m_ScissorRect;
	pipelineStateObjectDescriptor.m_RenderMode = RenderMode_Triangles;
	GFXCreatePipelineStateObject(m_API, &pipelineStateObjectDescriptor, &m_PipelineStateObject);

	GFXCommandListDescriptor commandListDescriptor;
	commandListDescriptor.m_PipelineStateObject = m_PipelineStateObject;
	commandListDescriptor.m_Type = CommandListType_Direct;
	GFXCreateCommandList(m_API, &commandListDescriptor, &m_CommandList);
}

void OpaqueRenderPass::Prepare(SceneGraph &a_SceneGraph)
{
	AssertMessage(m_Selector.IsBound(), "Renderpass selector function not bound!");
	m_SceneNodes.clear();
	SceneGraphVisitor visitor(m_SceneNodes, m_Selector);
	a_SceneGraph.Accept(visitor);

	GFXStartRecordingCommandList(m_API, m_CommandList, m_PipelineStateObject);
	GFXPrepareRenderTargetForDraw(m_API, m_CommandList, m_RenderTarget);

	// Record commands.
	GFXColor clearColor = { 100.0f / 255.0f, 149.0f / 255.0f, 237.0f / 255.0f, 1.0f };
	GFXClearRenderTarget(m_API, m_CommandList, m_RenderTarget, clearColor);

	if (!m_SceneNodes.empty())
	{
		ModelSceneNode *node = static_cast<ModelSceneNode*>(m_SceneNodes[0]);
		Model &model = node->GetModel();
		Mesh &mesh = *model.m_Meshes[0];
		GFXDrawInstanced(m_API, m_CommandList, mesh.m_VertexBuffer);
	}

	GFXPrepareRenderTargetForPresent(m_API, m_CommandList, m_RenderTarget);
	GFXStopRecordingCommandList(m_API, m_CommandList);
}

void OpaqueRenderPass::Execute(GFXCommandQueueHandle a_CommandQueue)
{
	GFXExecuteCommandList(m_API, m_CommandList, a_CommandQueue);
}

void OpaqueRenderPass::Terminate()
{

}