#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Memory)

extern const uint32_t g_HeaderGuardValue;
extern const uint32_t g_FooterGuardValue;
extern const uint32_t g_MemoryChunkGuardSize;

struct MemoryChunkGuard
{
	uint32_t m_Value;
};

END_NAMESPACE(Memory)
