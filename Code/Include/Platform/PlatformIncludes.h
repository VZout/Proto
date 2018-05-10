#pragma once

#if defined(PROTO_PLATFORM_WIN32)
	#include "Win32/PlatformDefines.h"
	#include "Win32/WinIncludes.h"
	#include "Win32/ApplicationLoop.h"
	#include "Win32/WindowProcedure.h"
#elif defined(PROTO_PLATFORM_RASPBERRY_PI)
	#include "Pi/PlatformDefines.h"
	#include "Pi/ApplicationLoop.h"
#elif defined(PROTO_PLATFORM_PSP2)
	#include "PSP2/PlatformDefines.h"
#elif defined(PROTO_PLATFORM_ORBIS)
	#include "ORBIS/PlatformDefines.h"
#endif
