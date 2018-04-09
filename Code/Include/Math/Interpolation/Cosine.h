#pragma once

#include "Proto.h"
#include "Math/IInterpolator.h"

BEGIN_NAMESPACE(Math)

template<typename T>
class Cosine : public IInterpolator<T>
{
public:
	const T operator() (const T &a_Value1, const T &a_Value2, float a_Delta)
	{
		float delta = (1.0f - Cos(a_Delta * PI)) / 2.0f;
		return a_Value1 * (1.0f - delta) + a_Value2 * delta;
	}
};

END_NAMESPACE(Math)
