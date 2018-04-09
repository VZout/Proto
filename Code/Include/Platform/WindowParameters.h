#pragma once

#include "Platform/PlatformIncludes.h"

#include <stdint.h>
#include <string>

struct WindowParameters
{
	uint32_t m_WindowWidth;
	uint32_t m_WindowHeight;
	std::string m_Title;
	bool m_Fullscreen;
	//void *m_Window;
	//NativeWindowHandle m_Handle;
};
