#include "Alignment.h"

#include "Math/Helpers/IsPowerOfTwo.h"
#include "Platform/Debug/AssertMessage.h"

USING_NAMESPACE(Math)
USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Memory)

bool IsAligned(void *a_Address, uint8_t a_Alignment)
{
	AssertMessage(IsPowerOfTwo(a_Alignment), "Alignment is no power of two!");
	const bool aligned = (reinterpret_cast<uintptr_t>(a_Address) & (a_Alignment - 1)) == 0;
	return aligned;
}

void* AlignAddress(void *a_Address, uint8_t a_Alignment)
{
	return reinterpret_cast<void*>((reinterpret_cast<uintptr_t>(a_Address) + static_cast<uint8_t>(a_Alignment - 1)) & static_cast<uintptr_t>(~(a_Alignment - 1)));
} 

uint8_t AlignmentAdjustment(const uintptr_t a_Address, uint8_t a_Alignment)
{
	const uint8_t adjustment = a_Alignment - (static_cast<const uint8_t>(a_Address) & (a_Alignment - 1));
	if (adjustment == a_Alignment)
	{
		return 0;
	}
	return adjustment;
}

uint8_t AlignmentAdjustment(const uintptr_t a_Address, uint8_t a_Alignment, size_t a_HeaderSize)
{
	uint8_t adjustment = AlignmentAdjustment(a_Address, a_Alignment);
	uint8_t neededSpace = static_cast<uint8_t>(a_HeaderSize);

	if (adjustment < neededSpace)
	{
		neededSpace -= adjustment;
		adjustment += a_Alignment * (neededSpace / a_Alignment);
		if (neededSpace % adjustment > 0)
		{
			adjustment += a_Alignment;
		}
	}
	return adjustment; 
}

END_NAMESPACE(Memory)
