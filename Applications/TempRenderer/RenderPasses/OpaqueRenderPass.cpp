#include "OpaqueRenderPass.h"

#include "../Scene/ModelSceneNode.h"
#include "Graphics/Mesh.h"
#include "Graphics/Model.h"

USING_NAMESPACE(Graphics)

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

void OpaqueRenderPass::Initialize()
{
	GFXRasterizerStateDescriptor rasterizerStateDescriptor;
	GFXRasterizerStateHandle rasterizerState;
	GFXCreateRasterizerState(m_API, &rasterizerStateDescriptor, &rasterizerState);

	GFXBlendStateDescriptor blendStateDescriptor;
	GFXBlendStateHandle blendState;
	GFXCreateBlendState(m_API, &blendStateDescriptor, &blendState);

// 	GFXPipelineStateObjectDescriptor pipelineStateObjectDescriptor = { 0 };
// 	pipelineStateObjectDescriptor.m_VertexShader = m_VertexShader;
// 	pipelineStateObjectDescriptor.m_PixelShader = m_PixelShader;
// 	pipelineStateObjectDescriptor.m_RasterizerState = rasterizerState;
// 	pipelineStateObjectDescriptor.m_BlendState = blendState;
// 	GFXCreatePipelineStateObject(m_API, &pipelineStateObjectDescriptor, &m_PipelineStateObject);

	GFXCommandListDescriptor commandListDescriptor;
	commandListDescriptor.m_PipelineStateObject = m_PipelineStateObject;
	commandListDescriptor.m_Type = CommandListType_Direct;
	GFXCreateCommandList(m_API, &commandListDescriptor, &m_CommandList);
}

void OpaqueRenderPass::Prepare()
{
	// 	AssertMessage(m_Selector.IsBound(), "Renderable selector function not bound!");
	// 	m_SceneNodes.clear();
	// 	SceneGraphVisitor visitor(m_SceneNodes, m_Selector);
	// 	m_SceneGraph->Accept(visitor);

	GFXStartRecordingCommandList(m_API, m_CommandList, m_PipelineStateObject);
	GFXPrepareRenderTargetForDraw(m_API, m_CommandList, m_RenderTarget);

	GFXColor clearColor = { 100.0f / 255.0f, 149.0f / 255.0f, 237.0f / 255.0f, 1.0f };
	GFXClearRenderTarget(m_API, m_CommandList, m_RenderTarget, clearColor);

	GFXPrepareRenderTargetForPresent(m_API, m_CommandList, m_RenderTarget);
	GFXStopRecordingCommandList(m_API, m_CommandList);
}

void OpaqueRenderPass::Execute(GFXCommandQueueHandle a_CommandQueue)
{
	GFXExecuteCommandList(m_API, m_CommandList, a_CommandQueue);
}
