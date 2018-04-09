#pragma once

#include "Vector3.h"

BEGIN_NAMESPACE(Math)

struct AABB
{
	Vector3 m_Min;
	Vector3 m_Max;
};

END_NAMESPACE(Math)