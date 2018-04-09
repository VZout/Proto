#pragma once

#include "Proto.h"

#include <math.h>

BEGIN_NAMESPACE(Math)

template <typename T>
const T Atan2(const T &a_X, const T &a_Y)
{
	return atan2(a_Y, a_X);
}

END_NAMESPACE(Math)
