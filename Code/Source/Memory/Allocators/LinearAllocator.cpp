#include "LinearAllocator.h"

#include "Platform/Debug/AssertMessage.h"

USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Memory)

// LinearAllocator::LinearAllocator(size_t size, void* start) : Allocator(size, start), _current_pos(start) { ASSERT(size > 0); }
// 
// LinearAllocator::~LinearAllocator()
// { 
// 	_current_pos = nullptr; 
// }

void* LinearAllocator::Allocate(size_t a_Size, uint8_t a_Alignment)
{
	AssertMessage(0 != a_Size, "Invalid size to allocate");
// 	u8 adjustment = pointer_math::alignForwardAdjustment(_current_pos, alignment);
// 
// 	if (_used_memory + adjustment + size > _size) return nullptr;
// 
// 	uptr aligned_address = (uptr)_current_pos + adjustment;
// 	_current_pos = (void*)(aligned_address + size);
// 	_used_memory += size + adjustment;
// 	_num_allocations++;
// 
// 	return (void*)aligned_address;
	return nullptr;
}

void LinearAllocator::Deallocate(void *a_Ptr)
{
	AssertMessage("Deallocation for linear allocator not supported!");
}

// void LinearAllocator::clear()
// {
// 	_num_allocations = 0;
// 	_used_memory = 0;
// 	_current_pos = _start;
// }

END_NAMESPACE(Memory)
