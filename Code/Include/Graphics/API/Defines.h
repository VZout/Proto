#pragma once

#if defined(PROTO_PLATFORM_WIN32)
#include "Platform/Win32/PlatformDefines.h"
#elif defined(PROTO_PLATFORM_RASPBERRY_PI)
#include "Platform/Pi/PlatformDefines.h"
#elif defined(PROTO_PLATFORM_PSP2)
#include "Platform/PSP2/PlatformDefines.h"
#elif defined(PROTO_PLATFORM_ORBIS)
#include "Platform/ORBIS/PlatformDefines.h"
#endif

#define GFX_UNUSED(a_Variable) (void)a_Variable
#define ALLOCATE(a_Type) (a_Type*)malloc(sizeof(a_Type))
#define ALLOCATEARRAY(a_Type, a_NumItems) (a_Type*)malloc((a_NumItems) * sizeof(a_Type))
#define DEALLOCATE(a_Instance) free(a_Instance)

#define MAX_SHADERS_PER_PROGRAM 2
#define MAX_ATTRIBUTES_PER_PROGRAM 16
