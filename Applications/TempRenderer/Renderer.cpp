#include "Renderer.h"

// #include "Graphics/EVertexFormat.h"
#include "Graphics/Viewer/Camera.h"
// #include "Graphics/Viewer/ProjectionMatrix.h"
// #include "Math/Color.h"
// #include "Math/Matrix4.h"
// #include "Platform/Debug/AssertMessage.h"
#include "Platform/Window.h"
#include "RenderPass.h"
#include "RenderTechnique.h"

USING_NAMESPACE(Graphics)
USING_NAMESPACE(Math)
USING_NAMESPACE(Platform)

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Initialize(Window &a_Window)
{
	const Dimension &windowSize = a_Window.GetSize();

	const float fovY = 60.0f;
	const float aspectRatio = static_cast<float>(windowSize.m_Width) / windowSize.m_Height;
	const float nearZ = 0.01f;
	const float farZ = 10000.0f;
	m_Camera = new Camera();
	m_Camera->CreatePerspectiveLens(fovY, aspectRatio, nearZ, farZ);
	m_Camera->SetLookAt(Vector3(0.0f, 0.0f, 10.0f), Vector3::ORIGIN, Vector3::Y_AXIS);


// 
// 	const uint32_t slices = 32;
// 	const uint32_t stacks = 32;
// 	GenerateSphere(m_API, m_Sphere, 1.0f, slices, stacks, EVertexFormat_Position);
// 	GenerateSphere(m_API, m_SphereTexLit, 1.0f, slices, stacks, EVertexFormat_Position | EVertexFormat_Texture_0 | EVertexFormat_Normal);
}

void Renderer::Update()
{
	if (nullptr != m_CurrentTechnique)
	{
		for (auto pos = m_CurrentTechnique->GetPassListBegin(); pos != m_CurrentTechnique->GetPassListEnd(); ++pos)
		{
			RenderPass &renderPass = **pos;
			renderPass.Update();
		}
	}
}

void Renderer::Render()
{
	if (nullptr != m_CurrentTechnique)
	{
		for (RenderTechnique::RenderPassListConstIt pos = m_CurrentTechnique->GetPassListBegin(); pos != m_CurrentTechnique->GetPassListEnd(); ++pos)
		{
			const RenderPass &renderPass = **pos;
			UNUSED(renderPass);
		}
	}
}

void Renderer::Terminate()
{
	delete m_Camera;
}