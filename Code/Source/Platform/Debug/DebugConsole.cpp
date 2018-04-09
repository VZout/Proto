#include "DebugConsole.h"

#include "Platform/PlatformIncludes.h"

#include <iostream>

BEGIN_NAMESPACE(Platform)

void InitializeDebugConsole()
{
#if defined(PROTO_PLATFORM_WIN32)
	AllocConsole();

	FILE *stdOutHandle;
	freopen_s(&stdOutHandle, "CONOUT$", "w", stdout);

	FILE *stdErrHandle;
	freopen_s(&stdErrHandle, "CONOUT$", "w", stderr);

	FILE *stdInHandle;
	freopen_s(&stdInHandle, "CONIN$", "r", stdin);

	std::ios::sync_with_stdio(true);
#elif defined(PROTO_PLATFORM_RASPBERRY_PI)
	// not implemented
#endif
}

void TerminateDebugConsole()
{
}

END_NAMESPACE(Platform)
