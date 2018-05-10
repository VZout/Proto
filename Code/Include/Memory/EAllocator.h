#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Memory)

ENUM EAllocator
{
	FreeList,
	Linear,
	Pool,
	SegragatedFreeList,
	Stack
};

END_NAMESPACE(Memory)
