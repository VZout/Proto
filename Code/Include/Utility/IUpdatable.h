#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Utility)

struct UpdateEvent;

class IUpdatable
{
public:
	virtual void Update(const UpdateEvent &a_UpdateEvent) = 0;
};

END_NAMESPACE(Utility)
