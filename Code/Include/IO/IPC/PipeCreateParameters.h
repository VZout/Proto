#pragma once

#include "PipeConstants.h"

#include <string>
#include <windows.h>

BEGIN_NAMESPACE(IO)

struct PipeCreateParameters
{
	uint32_t m_OpenMode;
	uint32_t m_PipeMode;
	std::string m_Name;
	uint32_t m_MaxInstances = g_PipeMaxNumInstances;
	uint32_t m_InBufferByteSize = 1024;
	uint32_t m_OutBufferByteSize = 1024;
	uint32_t m_TimeOutMilliSeconds = 50;
};

END_NAMESPACE(IO)