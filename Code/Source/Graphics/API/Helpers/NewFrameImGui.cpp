#include "NewFrameImGui.h"

#include "Platform/Debug/AssertMessage.h"

#include "imgui.h"

#if defined(GFX_API_DX11)
#include "Impl/imgui_impl_dx11.h"
#include "Graphics/API/DX11/DX11Structs.h"
#elif defined(GFX_API_DX12)
#include "Impl/imgui_impl_dx12.h"
#include "Graphics/API/DX12/DX12Structs.h"
#elif defined(GFX_API_OPENGL)
#elif defined(GFX_API_VULKAN)
// #elif defined(GFX_API_OPENGLES)
// #elif defined(GFX_API_ORBIS)
#endif

USING_NAMESPACE(Platform)

BEGIN_UNNAMEDNAMESPACE()

#if defined(GFX_API_DX11)
void GFXNewFrameImGuiDX11(GFXAPI a_API)
{
	DX11API *api = reinterpret_cast<DX11API*>(a_API);
	AssertMessage(NULLPTR != api, "Failed to cast to DX11 graphics api!");
}
#elif defined(GFX_API_DX12)

void GFXNewFrameImGuiDX12(GFXCommandListHandle a_CommandList)
{
	DX12CommandList *commandList = reinterpret_cast<DX12CommandList*>(a_CommandList);
	AssertMessage(NULLPTR != commandList, "Failed to cast to DX12 command list!");
	ImGui_ImplDX12_NewFrame(commandList->m_BackEnd);
}
#elif defined(GFX_API_OPENGL)
void GFXNewFrameImGuiOpenGL(GFXAPI a_API)
{
	OpenGLAPI *api = reinterpret_cast<OpenGLAPI*>(a_API);
	AssertMessage(NULLPTR != api, "Failed to cast to OpenGL graphics api!");
}
#elif defined(GFX_API_VULKAN)
void GFXNewFrameImGuiVulkan(GFXAPI a_API)
{
	VulkanAPI *api = reinterpret_cast<VulkanPI*>(a_API);
	AssertMessage(NULLPTR != api, "Failed to cast to Vulkan graphics api!");
}
// #elif defined(GFX_API_OPENGLES)
// #elif defined(GFX_API_ORBIS)
#endif

END_UNNAMEDNAMESPACE()

void GFXNewFrameImGui(GFXCommandListHandle a_CommandList)
{
	AssertMessage(NULLPTR != a_CommandList, "Attempt to use invalid graphics command list!");

#if defined(GFX_API_DX11)
	GFXNewFrameImGuiDX11(a_API);
#elif defined(GFX_API_DX12)
	GFXNewFrameImGuiDX12(a_CommandList);
#elif defined(GFX_API_OPENGL)
	GFXNewFrameImGuiOpenGL(a_API);
#elif defined(GFX_API_VULKAN)
	GFXNewFrameImGuiVulkan(a_API);
	// #elif defined(GFX_API_OPENGLES)
	// #elif defined(GFX_API_ORBIS)
#endif
}