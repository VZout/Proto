#include "Proto.h"

#include "Platform/Debug/AssertMessage.h"
#include "Platform/Helpers/SetWorkingDirectory.h"
#include "Platform/Window.h"
#include "Graphics/Renderer.h"
#include "Resources/LoadResources.h"
#include "Resources/Resources/MeshResource.h"
#include "Resources/Resources/ModelResource.h"
#include "Resources/ResourceManager.h"
#include "SimpleScene.h"
#include "Utility/HashedString.h"
#include "Utility/UpdateEvent.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

#if defined(PROTO_PLATFORM_WIN32)
#if !defined(NDEBUG)
//#include <vld.h>
#endif
#endif

#include <fstream>

USING_NAMESPACE(Graphics)
USING_NAMESPACE(Platform)
USING_NAMESPACE(Resources)
USING_NAMESPACE(Utility)

namespace
{
	const uint32_t windowWidth = 1280;
	const uint32_t windowHeight = 720;

	void LoadModel(GFXAPI a_API, float a_AspectRatio, ResourceManager &a_ResourceManager)
	{
		std::vector<float> vertices;
		vertices.push_back(0.0f); vertices.push_back(0.25f * a_AspectRatio); vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(0.0f); vertices.push_back(0.0f); vertices.push_back(1.0f);
		vertices.push_back(0.25f); vertices.push_back(-0.25f * a_AspectRatio); vertices.push_back(0.0f); vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(0.0f); vertices.push_back(1.0f);
		vertices.push_back(-0.25f); vertices.push_back(-0.25f * a_AspectRatio); vertices.push_back(0.0f); vertices.push_back(0.0f); vertices.push_back(0.0f); vertices.push_back(1.0f); vertices.push_back(1.0f);
		const uint32_t vertexBufferByteSize = static_cast<uint32_t>(vertices.size() * sizeof(float));

		MeshResource *meshResource = new MeshResource();
		GFXVertexBufferDescriptor vertexBufferDescriptor{};
		vertexBufferDescriptor.m_ByteOffset = 0;
		vertexBufferDescriptor.m_DataByteSize = vertexBufferByteSize;
		vertexBufferDescriptor.m_Stride = 7 * sizeof(float);
		vertexBufferDescriptor.m_Vertices = &vertices[0];
		GFXCreateVertexBuffer(a_API, &vertexBufferDescriptor, &meshResource->m_VertexBuffer);

		ModelResource *modelResource = new ModelResource();
		modelResource->m_Meshes.push_back(meshResource);

		a_ResourceManager.AddResource(modelResource, "SimpleTriangle");
	}
}

int main(int a_ArgC, const char * a_ArgV[])
{
	UNUSED(a_ArgC);
	UNUSED(a_ArgV);

	SetWorkingDirectory(std::string(a_ArgV[1]));

	Window window(std::wstring(L"Forward rendering").c_str(), windowWidth, windowHeight);
	window.Show(EWindowState_Show);

	Renderer renderer;
	renderer.Initialize(window);

	const float aspectRatio = static_cast<float>(windowWidth) / windowHeight;
	LoadModel(renderer.GetAPI(), aspectRatio, renderer.GetResourceManager());

	SimpleScene *simpleScene = new SimpleScene(renderer.GetAPI());
	renderer.SetScene(*simpleScene);

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

	renderer.Terminate();

	return ret;
}
