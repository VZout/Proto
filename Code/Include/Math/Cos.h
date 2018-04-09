#pragma once

#include "Proto.h"

#include <math.h>

BEGIN_NAMESPACE(Math)

template <typename T>
const T Cos(const T &a_Value)
{
	cos(a_Value);
}

template<>
inline const float Cos(const float &a_Value)
{
	return cosf(a_Value);
}

template<>
inline const long double Cos(const long double &a_Value)
{
	return cosl(a_Value);
}

END_NAMESPACE(Math)
