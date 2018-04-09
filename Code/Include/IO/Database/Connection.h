#pragma once

#include "Utility/NoCopy.h"

BEGIN_NAMESPACE(IO)

class Connection : public Utility::NoCopy
{
public:
	Connection();
	virtual ~Connection();
};

END_NAMESPACE(IO)
