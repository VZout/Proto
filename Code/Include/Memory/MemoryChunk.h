#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Memory)

struct MemoryChunk
{
	MemoryChunk *m_Next = nullptr;
	size_t m_Size;
};

END_NAMESPACE(Memory)
