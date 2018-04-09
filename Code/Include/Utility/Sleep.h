#pragma once

#include "Platform/PlatformIncludes.h"
// #if defined(PROTO_PLATFORM_WIN32)
// #  include <Windows.h>
// #else
// #  include <unistd.h>
// #endif
// #include <stdint.h>

BEGIN_NAMESPACE(Utility)

class Sleep
{
public:
	static void MilliSeconds(uint32_t a_MilliSeconds);
};

END_NAMESPACE(Utility)
