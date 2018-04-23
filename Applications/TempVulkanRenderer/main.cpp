#include "Proto.h"

#include "Graphics/API/GFX.h"
#include "Platform/Debug/AssertMessage.h"

#include <iostream>
#include <string>
#include <vector>

USING_NAMESPACE(Platform)

namespace
{
	GFXAPI g_API;
}

int main(int a_ArgC, const char * a_ArgV[])
{
	UNUSED(a_ArgC);
	UNUSED(a_ArgV);

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
#else
	GFXParameterHandle parameters;
#endif

	GFXAPIDescriptor descriptor;
	descriptor.m_FrameBufferHeight = 720;
	descriptor.m_FrameBufferWidth = 1280;
	descriptor.m_WindowHandle = nullptr;
	GFXInitialize(&g_API, nullptr, &descriptor, &parameters);

	GFXTerminate(g_API);

	return 0;
}
