#pragma once

#include "AllocatorBase.h"

BEGIN_NAMESPACE(Memory)

class LinearAllocator : public AllocatorBase
{
public:
	virtual void* Allocate(size_t a_Size, uint8_t a_Alignment) override;
	virtual void Deallocate(void *a_Ptr) override;
};

END_NAMESPACE(Memory)
