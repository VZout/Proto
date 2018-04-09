#include "SystemInfo.h"

#include "Platform/PlatformIncludes.h"

BEGIN_UNNAMEDNAMESPACE()

#if defined(PROTO_PLATFORM_WIN32)

SYSTEM_INFO g_SystemInfo;
bool g_SystemInfoValid = false;

#elif defined(PROTO_PLATFORM_RASPBERRY_PI)
#endif

void UpdateSystemInfo()
{
#if defined(PROTO_PLATFORM_WIN32)
	::GetSystemInfo(&g_SystemInfo);
	g_SystemInfoValid = true;
#elif defined(PROTO_PLATFORM_RASPBERRY_PI)
	// not implemented
#endif
}

void CheckSystemInfo()
{
#if defined(PROTO_PLATFORM_WIN32)
	if (!g_SystemInfoValid)
	{
		UpdateSystemInfo();
	}
#elif defined(PROTO_PLATFORM_RASPBERRY_PI)
	// not implemented
#endif
}

END_UNNAMEDNAMESPACE()

BEGIN_NAMESPACE(Platform)

uint32_t SystemInfo::GetPageSize()
{
#if defined(PROTO_PLATFORM_WIN32)
	CheckSystemInfo();
	return static_cast<uint32_t>(g_SystemInfo.dwPageSize);
#elif defined(PROTO_PLATFORM_RASPBERRY_PI)
	return 0;
#endif
}

END_NAMESPACE(Platform)
