#pragma once

#include "Proto.h"
#include "Utility/NoCopy.h"

BEGIN_NAMESPACE(Math)

template<typename T>
class IInterpolator : public Utility::NoCopy
{
	virtual
	const T operator() (const T& a_Value1, const T& a_Value2, float a_Delta) = 0;
};

END_NAMESPACE(Math)
