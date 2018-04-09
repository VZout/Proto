#pragma once

#include "Proto.h"
#include "Utility/IUpdatable.h"
#include "Utility/NoCopy.h"

BEGIN_NAMESPACE(IO)

class IInputHandler : public Utility::NoCopy, public Utility::IUpdatable
{
public:
	virtual void Update(const Utility::UpdateEvent &a_UpdateEvent) = 0;
};

END_NAMESPACE(IO)
