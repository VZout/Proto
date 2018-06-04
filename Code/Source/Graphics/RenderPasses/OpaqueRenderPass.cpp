#include "OpaqueRenderPass.h"

#include "Graphics/Mesh.h"
#include "Graphics/Model.h"
#include "Graphics/Viewer/Camera.h"
#include "Graphics/Viewer/ProjectionMatrix.h"
#include "Math/Matrix4.h"
#include "Memory/Memory.h"
#include "Platform/Debug/AssertMessage.h"
#include "Resources/ResourceManager.h"
#include "Scene/ModelSceneNode.h"
#include "Scene/SceneGraph.h"
#include "Scene/SceneGraphVisitor.h"
#include "Resources/Resources/ShaderResource.h"
#include "Utility/HashedString.h"

USING_NAMESPACE(Math)
USING_NAMESPACE(Platform)
USING_NAMESPACE(Resources)
USING_NAMESPACE(Utility)

BEGIN_NAMESPACE(Graphics)

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

	GFXConstantBufferDescriptor constantBufferDescriptor;
	constantBufferDescriptor.m_ByteSize = 4 * sizeof(float);
	GFXCreateConstantBuffer(m_API, &constantBufferDescriptor, &m_ConstantBuffer);

	m_BufferData.m_Offset[0] = 0.0f;
	m_BufferData.m_Offset[1] = 0.0f;
	m_BufferData.m_Offset[2] = 0.0f;
	m_BufferData.m_Offset[3] = 0.0f;
}

void OpaqueRenderPass::Prepare(const Graphics::Camera &a_Camera, SceneGraph &a_SceneGraph)
{
	UNUSED(a_Camera);

	AssertMessage(m_Selector.IsBound(), "Renderpass selector function not bound!");
	m_SceneNodes.clear();
	SceneGraphVisitor visitor(m_SceneNodes, m_Selector);
	a_SceneGraph.Accept(visitor);

	GFXStartRecordingCommandList(m_API, m_CommandList, m_PipelineStateObject);
	//GFXPrepareRenderTargetForDraw(m_API, m_CommandList, m_RenderTarget);

	GFXColor clearColor = { 100.0f / 255.0f, 149.0f / 255.0f, 237.0f / 255.0f, 1.0f };
	GFXClearRenderTarget(m_API, m_CommandList, m_RenderTarget, clearColor);

	//const Matrix4 &projectionMatrix = a_Camera.GetProjectionMatrix().GetMatrix();
	//const Matrix4 &viewMatrix = a_Camera.GetViewMatrix();
	//GFXWriteConstantBufferData(m_API, m_ConstantBuffer, projectionMatrix.f, 16 * sizeof(float));
	//GFXWriteConstantBufferData(m_API, m_ConstantBuffer, viewMatrix.f, 16 * sizeof(float));

	// constant buffer stuff
	// https://msdn.microsoft.com/en-us/library/windows/desktop/dn903911.aspx

	if (!m_SceneNodes.empty())
	{
		ModelSceneNode *node = static_cast<ModelSceneNode*>(m_SceneNodes[0]);
		Model &model = node->GetModel();
		Mesh &mesh = *model.m_Meshes[0];

		//const Matrix4 modelMatrix = model.GetTransformNode().GetTransform();
		//GFXWriteConstantBufferData(m_API, m_ConstantBuffer, modelMatrix, 16 * sizeof(float));

		{
			const float translationSpeed = 0.005f;
			const float offsetBounds = 1.25f;

			m_BufferData.m_Offset[0] += translationSpeed;
			if (m_BufferData.m_Offset[0] > offsetBounds)
			{
				m_BufferData.m_Offset[0] = -offsetBounds;
			}
			GFXWriteConstantBufferData(m_API, m_CommandList, m_ConstantBuffer, &m_BufferData, 4 * sizeof(float));
		}

		GFXInstancedDrawDescriptor instancedDrawDescriptor;
		instancedDrawDescriptor.m_VertexCountPerInstance = 3;
		instancedDrawDescriptor.m_InstanceCount = 1;
		instancedDrawDescriptor.m_StartVertexLocation = 0;
		instancedDrawDescriptor.m_VertexBuffer = mesh.m_VertexBuffer;
		GFXDrawInstanced(m_API, m_CommandList, m_ConstantBuffer, instancedDrawDescriptor);
	}

	//GFXPrepareRenderTargetForPresent(m_API, m_CommandList, m_RenderTarget);
	GFXStopRecordingCommandList(m_API, m_CommandList);
}

void OpaqueRenderPass::Execute(GFXCommandQueueHandle a_CommandQueue)
{
	GFXExecuteCommandList(m_API, m_CommandList, a_CommandQueue);
}

void OpaqueRenderPass::Terminate()
{

}

END_NAMESPACE(Graphics)
