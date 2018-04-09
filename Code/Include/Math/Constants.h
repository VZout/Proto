#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Math)

class Constants
{
public:
	template<typename TYPE>
	static const TYPE pi();
};

template<> inline const float Constants::pi() { return 3.141592653589793238462643383279502884f; }

END_NAMESPACE(Math)
