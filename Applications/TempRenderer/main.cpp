#include "Proto.h"

#include "Graphics/API/GFX.h"
#include "Graphics/Mesh.h"
#include "Graphics/Model.h"
#include "Platform/Debug/AssertMessage.h"
#include "Platform/Helpers/SetWorkingDirectory.h"
#include "Platform/Window.h"
#include "Renderer.h"
#include "Resources/LoadResources.h"
#include "Resources/ResourceManager.h"
#include "Utility/HashedString.h"
#include "Utility/UpdateEvent.h"

#include <algorithm>
#include <vector>

#if defined(PROTO_PLATFORM_WIN32)
#include <vld.h>

#pragma comment(lib, "winmm")
#endif

#include <fstream>

USING_NAMESPACE(Graphics)
USING_NAMESPACE(Platform)
USING_NAMESPACE(Utility)

namespace
{
	GFXAPI g_API = { 0 };

	const uint32_t windowWidth = 1280;
	const uint32_t windowHeight = 720;
}



int main(int a_ArgC, const char * a_ArgV[])
{
	UNUSED(a_ArgC);
	UNUSED(a_ArgV);

	SetWorkingDirectory(std::string(a_ArgV[1]));
	CreateResourceManager();

	Window window(std::wstring(L"Forward rendering").c_str(), windowWidth, windowHeight);
	window.Show(EWindowState_Show);

	Renderer renderer;
	renderer.Initialize(window);
	g_API = renderer.m_API;

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
#endif

	int ret = 0;
#if defined(PROTO_PLATFORM_WIN32)
	MSG msg = { 0 };

	static DWORD previousTime = timeGetTime();
	static float totalTime = 0.0f;
	static const float targetFramerate = 30.0f;
	static const float maxTimeStep = 1.0f / targetFramerate;

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			DWORD currentTime = timeGetTime();
			float deltaTime = (currentTime - previousTime) / 1000.0f;
			previousTime = currentTime;

			deltaTime = std::min<float>(deltaTime, maxTimeStep);
			totalTime += deltaTime;

			renderer.Update(UpdateEvent(deltaTime));
			renderer.BeginRender();
			renderer.Render();
			renderer.EndRender();
		}
	}
	ret = static_cast<int>(msg.wParam);
#endif


	ResourceManager &resourceManager = GetResourceManager();
	GFXShaderHandle shader = reinterpret_cast<GFXShaderHandle>(resourceManager.Get(HashedString("TempVertexShader")));
	GFXDestroyShader(g_API, shader);
	shader = reinterpret_cast<GFXShaderHandle>(resourceManager.Get(HashedString("TempPixelShader")));
	GFXDestroyShader(g_API, shader);

	Model *model = reinterpret_cast<Model*>(resourceManager.Get(HashedString("TempModel")));
	delete model;

	renderer.Terminate();

	DestoryResourceManager();

	return ret;
}
