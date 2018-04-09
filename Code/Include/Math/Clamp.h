#pragma once

#include "Proto.h"

#include "Platform/Debug/AssertMessage.h"

BEGIN_NAMESPACE(Math)

template <typename T>
const T Clamp(const T &a_Value, const T &a_Min, const T &a_Max)
{
	Platform::AssertMessage(a_Min <= a_Max, ("Invalid min and max values to clamp value to."));
	return (a_Value < a_Min ? a_Min : (a_Value > a_Max ? a_Max : a_Value));
}

END_NAMESPACE(Math)
