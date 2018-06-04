#include "RenderTargetTransitionRenderPass.h"

#include "Platform/Debug/AssertMessage.h"

USING_NAMESPACE(Platform)
USING_NAMESPACE(Resources)

BEGIN_NAMESPACE(Graphics)

RenderTargetTransitionRenderPass::RenderTargetTransitionRenderPass(GFXAPI a_API, GFXResourceHandle a_Resource, GFXResourceTransitionState a_State)
	: RenderPass(a_API, a_Resource)
	, m_DestinationState(a_State)
{
}

RenderTargetTransitionRenderPass::~RenderTargetTransitionRenderPass()
{
}

void RenderTargetTransitionRenderPass::Initialize(ResourceManager &a_ResourceManager)
{
	UNUSED(a_ResourceManager);
	GFXCommandListDescriptor commandListDescriptor { 0 };
	commandListDescriptor.m_Type = CommandListType_Direct;
	GFXCreateCommandList(m_API, &commandListDescriptor, &m_CommandList);
}

void RenderTargetTransitionRenderPass::Prepare(const Camera &a_Camera, SceneGraph &a_SceneGraph)
{
	UNUSED(a_SceneGraph);
	UNUSED(a_Camera);

	GFXStartRecordingCommandList(m_API, m_CommandList, m_PipelineStateObject);
	switch (m_DestinationState)
	{
	case ResourceState_RenderTarget:
		{
			GFXPrepareRenderTargetForDraw(m_API, m_CommandList, m_RenderTarget);
			break;
		}
	case ResourceState_Present:
		{
			GFXPrepareRenderTargetForPresent(m_API, m_CommandList, m_RenderTarget);
			break;
		}
	default:
		{
			AssertMessage("Invalid resource state encountered!");
			break;
		}
	}
	GFXStopRecordingCommandList(m_API, m_CommandList);
}

void RenderTargetTransitionRenderPass::Execute(GFXCommandQueueHandle a_CommandQueue)
{
	GFXExecuteCommandList(m_API, m_CommandList, a_CommandQueue);
}

void RenderTargetTransitionRenderPass::Terminate()
{
}

END_NAMESPACE(Graphics)
