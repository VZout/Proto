#pragma once

#if defined(PROTO_PLATFORM_WIN32)
	#include "Win32/PlatformDefines.h"
	#include "Win32/WinIncludes.h"
	#include "Win32/ApplicationLoop.h"
	#include "Win32/WindowProcedure.h"
#elif defined(PROTO_PLATFORM_RASPBERRY_PI)
	#include "Pi/PlatformDefines.h"
	#include "Pi/ApplicationLoop.h"
#endif
