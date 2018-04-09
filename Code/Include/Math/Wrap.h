#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Math)

uint32_t WrapInc(uint32_t a_Value, uint32_t a_MinValue, uint32_t a_MaxValue, uint32_t a_Increment = 1);
uint32_t WrapDec(uint32_t a_Value, uint32_t a_MinValue, uint32_t a_MaxValue, uint32_t a_Decrement = 1);

END_NAMESPACE(Math)
