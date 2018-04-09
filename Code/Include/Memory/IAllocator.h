#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Memory)

class IAllocator
{
public:
	virtual void* Allocate(size_t a_Size, uint8_t a_Alignment) = 0;
	virtual void Deallocate(void *a_Ptr) = 0;
};

END_NAMESPACE(Memory)
