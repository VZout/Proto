#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Memory)

bool IsAligned(void *a_Address, uint8_t a_Alignment);
void* AlignAddress(void* a_Address, uint8_t a_Alignment);
uint8_t AlignmentAdjustment(const uintptr_t a_Address, uint8_t a_Alignment);
uint8_t AlignmentAdjustment(const uintptr_t a_Address, uint8_t a_Alignment, size_t a_HeaderSize);

END_NAMESPACE(Memory)
