#include "SystemInfo.h"

#include "Platform/PlatformIncludes.h"

BEGIN_UNNAMEDNAMESPACE()

#if defined(PROTO_PLATFORM_WIN32)
SYSTEM_INFO g_SystemInfo;
#endif
bool g_SystemInfoValid = false;

void UpdateSystemInfo()
{
#if defined(PROTO_PLATFORM_WIN32)
	::GetSystemInfo(&g_SystemInfo);
	g_SystemInfoValid = true;
#else
	g_SystemInfoValid = false;
#endif
}

void CheckSystemInfo()
{
	if (!g_SystemInfoValid)
	{
		UpdateSystemInfo();
	}
}

END_UNNAMEDNAMESPACE()

BEGIN_NAMESPACE(Platform)

uint32_t SystemInfo::GetPageSize()
{
	CheckSystemInfo();
#if defined(PROTO_PLATFORM_WIN32)
	return static_cast<uint32_t>(g_SystemInfo.dwPageSize);
#elif defined(PROTO_PLATFORM_RASPBERRY_PI)
	return 0;
#elif defined(PROTO_PLATFORM_PSP2)
	return 0;
#elif defined(PROTO_PLATFORM_ORBIS)
	return 0;
#endif
}

END_NAMESPACE(Platform)
