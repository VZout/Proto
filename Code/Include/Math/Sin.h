#pragma once

#include "Proto.h"

#include <math.h>

BEGIN_NAMESPACE(Math)

template <typename T>
const T Sin(const T &a_Value)
{
	sin(a_Value);
}

template<>
inline const float Sin(const float &a_Value)
{
	return sinf(a_Value);
}

template<>
inline const long double Sin(const long double &a_Value)
{
	return sinl(a_Value);
}

END_NAMESPACE(Math)
