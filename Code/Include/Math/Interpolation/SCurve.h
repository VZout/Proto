#pragma once

#include "Proto.h"
#include "Math/IInterpolator.h"

BEGIN_NAMESPACE(Math)

template<typename T>
class SCurve : public IInterpolator<T>
{
public:
	const T operator() (const T &a_Value1, const T &a_Value2, float a_Delta)
	{
		const float negatedDelta = 1.0f - a_Delta;
		const float negatedDeltaSquared = negatedDelta * negatedDelta;
		const float deltaSquared = a_Delta * a_Delta;

		return a_Value1 * (3.0f * negatedDeltaSquared - 2.0f * (negatedDeltaSquared * negatedDelta)) + a_Value2 * (3.0f * deltaSquared - 2.0f * (deltaSquared * a_Delta));
	}
};

END_NAMESPACE(Math)
