#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Memory)

enum class EAllocator
{
	FreeList,
	Linear,
	Pool,
	SegragatedFreeList,
	Stack
};

END_NAMESPACE(Memory)
