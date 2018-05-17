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
#if !defined(NDEBUG)
#include <vld.h>
#endif
#endif

#include <fstream>

USING_NAMESPACE(Graphics)
USING_NAMESPACE(Platform)
USING_NAMESPACE(Resources)
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
