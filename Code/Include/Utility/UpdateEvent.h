#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Utility)

struct UpdateEvent
{
	UpdateEvent(float a_DeltaTime)
		: m_DeltaTime(a_DeltaTime)
	{
	}

	const float m_DeltaTime;
};

END_NAMESPACE(Utility)
