#include "Wrap.h"

BEGIN_NAMESPACE(Math)

uint32_t WrapInc(uint32_t a_Value, uint32_t a_MinValue, uint32_t a_MaxValue, uint32_t a_Increment /* = 1 */)
{
	return a_Value + a_Increment >= a_MaxValue ? a_MinValue : a_Value + a_Increment;
}

uint32_t WrapDec(uint32_t a_Value, uint32_t a_MinValue, uint32_t a_MaxValue, uint32_t a_Decrement /* = 1 */)
{
	return a_Value - a_Decrement <= a_MinValue ? a_MaxValue : a_Value - a_Decrement;
}

END_NAMESPACE(Math)
