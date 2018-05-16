#include "PathTracer.h"

#include "Math/Dimension.h"
#include "Platform/Window.h"

USING_NAMESPACE(Math)
USING_NAMESPACE(Platform)

PathTracer::PathTracer()
{
}

PathTracer::~PathTracer()
{
}

void PathTracer::Initialize(Window &a_Window)
{
	const Dimension &windowSize = a_Window.GetSize();

	GFXAPIDescriptor descriptor = { 0 };
	descriptor.m_FrameBufferWidth = windowSize.m_Width;
	descriptor.m_FrameBufferHeight = windowSize.m_Height;
	descriptor.m_WindowHandle = a_Window.GetHandle();
	descriptor.m_UseSoftwareDevice = false;
	GFXInitialize(&m_API, NULLPTR, &descriptor);
}

void PathTracer::Terminate()
{
	GFXTerminate(m_API);
}
