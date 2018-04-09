#pragma once

#include "Proto.h"
#include "BasicString.h"

BEGIN_NAMESPACE(Utility)

class WideString : public BasicString<wchar_t>
{
public:
	WideString();
	virtual ~WideString();
};

END_NAMESPACE(Utility)
