#pragma once

#include "Utility/NoCopy.h"

BEGIN_NAMESPACE(Memory)

class IAllocator : public Utility::NoCopy
{
public:
	virtual ~IAllocator() { }

	virtual void* Allocate(size_t a_Size, uint8_t a_Alignment) = 0;
	virtual void Deallocate(void *a_Ptr) = 0;

#if !defined(NDEBUG)
	virtual void CheckCoherence() = 0;
#endif
};

END_NAMESPACE(Memory)
