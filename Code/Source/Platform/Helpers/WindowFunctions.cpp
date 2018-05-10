#include "WindowFunctions.h"

#include "Platform/Debug/AssertMessage.h"

BEGIN_NAMESPACE(Platform)

BEGIN_UNNAMEDNAMESPACE()

IWindowApplication *g_Application = NULLPTR;

END_UNNAMEDNAMESPACE()

void SetWindowApplication(Platform::IWindowApplication &a_Application)
{
	AssertMessage(NULLPTR == g_Application, "Application interface already stored!");
	g_Application = &a_Application;
}

bool HasWindowApplication()
{
	return NULLPTR != g_Application;
}

IWindowApplication& GetWindowApplication()
{
	AssertMessage(NULLPTR != g_Application, "Attempt to retrieve an invalid application interface!");
	return *g_Application;
}

void ReleaseWindowApplication()
{
	AssertMessage(NULLPTR != g_Application, "Application interface was not stored or already released!");
	g_Application = NULLPTR;
}

END_NAMESPACE(Platform)
