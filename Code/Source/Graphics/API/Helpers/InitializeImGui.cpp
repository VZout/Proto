#include "InitializeImGui.h"

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
void GFXInitializeImGuiDX11(GFXAPI a_API)
{
	DX11API *api = reinterpret_cast<DX11API*>(a_API);
	AssertMessage(NULLPTR != api, "Failed to cast to DX11 graphics api!");
	AssertMessage(NULLPTR != api->m_WindowHandle, "Attempt to use invalid window handle!");
	AssertMessage(NULLPTR != api->m_Device, "Attempt to use invalid DX11 device!");
	AssertMessage(NULLPTR != api->m_DeviceContext, "Attempt to use invalid DX11 device context!");
	const bool result = ImGui_ImplDX11_Init(api->m_WindowHandle, api->m_Device, api->m_DeviceContext);
	AssertMessage(result, "Failed to initialize ImGui!");
}
#elif defined(GFX_API_DX12)

void GFXInitializeImGuiDX12(GFXAPI a_API)
{
	DX12API *api = reinterpret_cast<DX12API*>(a_API);
	AssertMessage(NULLPTR != api, "Failed to cast to DX12 graphics api!");

	D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle = api->m_CbvSrvUavDescriptorHeap->GetCPUDescriptorHandleForHeapStart();
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = api->m_CbvSrvUavDescriptorHeap->GetGPUDescriptorHandleForHeapStart();
	const int numFramesInFlight = 3;
	const bool result = ImGui_ImplDX12_Init(api->m_WindowHandle, numFramesInFlight, api->m_Device, DXGI_FORMAT_R8G8B8A8_UNORM, cpuHandle, gpuHandle);
	AssertMessage(result, "Failed to initialize ImGui!");
}
#elif defined(GFX_API_OPENGL)
void GFXInitializeImGuiOpenGL(GFXAPI a_API)
{
	OpenGLAPI *api = reinterpret_cast<OpenGLAPI*>(a_API);
	AssertMessage(NULLPTR != api, "Failed to cast to OpenGL graphics api!");
}
#elif defined(GFX_API_VULKAN)
void GFXInitializeImGuiVulkan(GFXAPI a_API)
{
	VulkanAPI *api = reinterpret_cast<VulkanPI*>(a_API);
	AssertMessage(NULLPTR != api, "Failed to cast to Vulkan graphics api!");
}
// #elif defined(GFX_API_OPENGLES)
// #elif defined(GFX_API_ORBIS)
#endif

END_UNNAMEDNAMESPACE()

void GFXInitializeImGui(GFXAPI a_API)
{
	AssertMessage(NULLPTR != a_API, "Attempt to use invalid graphics API!");

#if defined(GFX_API_DX11) || defined(GFX_API_DX12) || defined(GFX_API_OPENGL) || defined(GFX_API_VULKAN)
	ImGui::CreateContext();
#endif

#if defined(GFX_API_DX11)
	GFXInitializeImGuiDX11(a_API);
#elif defined(GFX_API_DX12)
	GFXInitializeImGuiDX12(a_API);
#elif defined(GFX_API_OPENGL)
	GFXInitializeImGuiOpenGL(a_API);
#elif defined(GFX_API_VULKAN)
	GFXInitializeImGuiVulkan(a_API);
// #elif defined(GFX_API_OPENGLES)
// #elif defined(GFX_API_ORBIS)
#endif
}