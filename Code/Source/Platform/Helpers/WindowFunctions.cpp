#include "WindowFunctions.h"

#include "Platform/Debug/AssertMessage.h"

BEGIN_NAMESPACE(Platform)

BEGIN_UNNAMEDNAMESPACE()

IWindowApplication *g_Application = nullptr;

END_UNNAMEDNAMESPACE()

void SetWindowApplication(Platform::IWindowApplication &a_Application)
{
	AssertMessage(nullptr == g_Application, "Application interface already stored!");
	g_Application = &a_Application;
}

bool HasWindowApplication()
{
	return nullptr != g_Application;
}

IWindowApplication& GetWindowApplication()
{
	AssertMessage(nullptr != g_Application, "Attempt to retrieve an invalid application interface!");
	return *g_Application;
}

void ReleaseWindowApplication()
{
	AssertMessage(nullptr != g_Application, "Application interface was not stored or already released!");
	g_Application = nullptr;
}

END_NAMESPACE(Platform)
