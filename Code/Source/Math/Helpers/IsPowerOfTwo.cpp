#include "IsPowerOfTwo.h"

BEGIN_NAMESPACE(Math)

bool IsPowerOfTwo(uint32_t a_Value)
{
  return ((a_Value != 0) && ((a_Value & (~a_Value + 1)) == a_Value));
}

END_NAMESPACE(Math)
