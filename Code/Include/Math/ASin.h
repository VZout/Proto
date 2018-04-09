#pragma once

#include "Proto.h"

#include <math.h>

BEGIN_NAMESPACE(Math)

template <typename T>
const T Asin(const T &a_Value)
{
	asin(a_Value);
}

template<>
inline const float Asin(const float &a_Value)
{
	return asinf(a_Value);
}

template<>
inline const long double Asin(const long double &a_Value)
{
	return asinl(a_Value);
}

END_NAMESPACE(Math)
