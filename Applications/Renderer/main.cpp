#include "Proto.h"

#include "Graphics/Material.h"
#include "Platform/Helpers/SetWorkingDirectory.h"
#include "Platform/Win32/WinIncludes.h"
#include "Platform/Window.h"
#include "Renderer.h"
// #include "ResourceLoading.h"

#include <algorithm>
#include <string>
#include <vector>
#include <vld.h>

#pragma comment(lib, "winmm")

/*
Owens, B. (2013, 10 28). Forward Rendering vs Deferred Rendering. Retrieved from Tutsplus: https://gamedevelopment.tutsplus.com/articles/forward-rendering-vs-deferred-rendering--gamedev-12342

Vries, J. d. (n.d.). Deferred Shading. Retrieved from Learnopengl: https://learnopengl.com/Advanced-Lighting/Deferred-Shading
*/

USING_NAMESPACE(Platform)

int main(int a_ArgC, const char * a_ArgV[])
{
	UNUSED(a_ArgC);
	UNUSED(a_ArgV);

	SetWorkingDirectory(std::string(a_ArgV[1]));

	const uint32_t windowWidth = 1280;
	const uint32_t windowHeight = 720;
	Window window(std::wstring(L"Forward rendering").c_str(), windowWidth, windowHeight);
	window.Show(EWindowState_Show);

	Renderer renderer;
	renderer.Initialize(window);

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

			//UpdateEventArgs updateEventArgs(deltaTime, totalTime);
			//RenderEventArgs renderEventArgs(deltaTime, totalTime);

			renderer.Update();
			renderer.Render();
		}
	}

	renderer.Terminate();

	return static_cast<int>(msg.wParam);
}
