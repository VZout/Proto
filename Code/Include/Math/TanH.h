#pragma once

#include "Proto.h"

#include <math.h>

BEGIN_NAMESPACE(Math)

template <typename T>
const T TanH(const T &a_Value)
{
	return tanh(a_Value);
}

template<>
inline const float TanH(const float &a_Value)
{
	return tanhf(a_Value);
}

END_NAMESPACE(Math)
