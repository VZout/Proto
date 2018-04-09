#pragma once

#include "Proto.h"
#include "BasicString.h"

BEGIN_NAMESPACE(Utility)

class FixedString : public BasicString<char>
{
public:
	FixedString();
	virtual ~FixedString();
};

END_NAMESPACE(Utility)
