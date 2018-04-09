#include "DegToRad.h"

#include "Math/Constants.h"

BEGIN_NAMESPACE(Math)

float DegToRad(float a_Degrees)
{
	static const float degToRad = Constants::pi<float>() / 180.0f;
    return a_Degrees * degToRad;
}

END_NAMESPACE(Math)
