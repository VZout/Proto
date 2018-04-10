#include "AllocatorBase.h"

BEGIN_NAMESPACE(Memory)

AllocatorBase::AllocatorBase(uintptr_t a_BaseAddress, uint64_t a_ByteSize)
	: m_BaseAddress(a_BaseAddress)
	, m_ByteSize(a_ByteSize)
{
}

AllocatorBase::~AllocatorBase()
{
}

END_NAMESPACE(Memory)
