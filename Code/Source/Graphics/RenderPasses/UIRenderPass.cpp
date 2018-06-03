#include "UIRenderPass.h"

#include "Graphics/API/GFX.h"
#include "Graphics/API/Helpers/InitializeImGui.h"
#include "Platform/Debug/AssertMessage.h"
#include "Platform/Debug/Inspector.h"

USING_NAMESPACE(Platform)
USING_NAMESPACE(Resources)

BEGIN_NAMESPACE(Graphics)

UIRenderPass::UIRenderPass(GFXAPI a_API, GFXRenderTargetHandle a_RenderTarget)
	: RenderPass(a_API, a_RenderTarget)
	, m_Inspector(NULLPTR)
{
}

UIRenderPass::~UIRenderPass()
{
}

void UIRenderPass::Initialize(ResourceManager &a_ResourceManager)
{
	UNUSED(a_ResourceManager);
	m_Inspector = new Inspector();

	GFXInitializeImGui(m_API);
}

void UIRenderPass::Prepare(const Camera &a_Camera, SceneGraph &a_SceneGraph)
{
	UNUSED(a_SceneGraph);
	UNUSED(a_Camera);
}

void UIRenderPass::Execute(GFXCommandQueueHandle a_CommandQueue)
{
	UNUSED(a_CommandQueue);
	AssertMessage(NULLPTR != m_Inspector, "Attempt to use an invalid inspector!");
	m_Inspector->BeginFrame(NULLPTR);
	m_Inspector->EndFrame();
}

void UIRenderPass::Terminate()
{
	m_Inspector->Terminate();
	delete m_Inspector;
}

Inspector& UIRenderPass::GetInspector()
{
	AssertMessage(NULLPTR != m_Inspector, "Attempt to retrieve an invalid Inspector!");
	return *m_Inspector;
}

END_NAMESPACE(Graphics)
