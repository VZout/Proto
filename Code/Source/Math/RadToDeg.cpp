#include "RadToDeg.h"

#include "Math/Constants.h"

BEGIN_NAMESPACE(Math)

float RadToDeg(float a_Radians)
{
	static const float radToDeg = static_cast<float>(180.0f) / Constants::pi<float>();
    return a_Radians * radToDeg;
}

END_NAMESPACE(Math)
