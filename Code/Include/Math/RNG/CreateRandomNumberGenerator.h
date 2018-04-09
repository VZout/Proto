#pragma once

#include "IRandomNumberGenerator.h"
#include "Utility/AutoPointer.h"

BEGIN_NAMESPACE(Math)

Utility::AutoPointer<IRandomNumberGenerator> CreateRandomNumberGenerator();
Utility::AutoPointer<IRandomNumberGenerator> CreateRandomNumberGenerator(unsigned long a_Seed);

END_NAMESPACE(Math)
