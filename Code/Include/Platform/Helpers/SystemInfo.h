#pragma once

#include "Utility/NoCopy.h"

BEGIN_NAMESPACE(Platform)

class SystemInfo : public Utility::NoCopy
{
public:
	static uint32_t GetPageSize();
};

END_NAMESPACE(Platform)
