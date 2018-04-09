#pragma once

#include "Proto.h"
#include "Math/IInterpolator.h"

BEGIN_NAMESPACE(Math)

template <typename T>
const T Lerp(const T& a_Value1, const T& a_Value2, float a_Delta)
{
	return a_Value1 + a_Delta * (a_Value2 - a_Value1);
}

END_NAMESPACE(Math)
