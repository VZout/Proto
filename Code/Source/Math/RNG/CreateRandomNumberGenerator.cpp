#include "CreateRandomNumberGenerator.h"
#include "MersenneTwister.h"

USING_NAMESPACE(Utility)

BEGIN_NAMESPACE(Math)

AutoPointer<IRandomNumberGenerator> CreateRandomNumberGenerator()
{
	return AutoPointer<IRandomNumberGenerator>(new MersenneTwister());
}

AutoPointer<IRandomNumberGenerator> CreateRandomNumberGenerator(unsigned long a_Seed)
{
	return AutoPointer<IRandomNumberGenerator>(new MersenneTwister(a_Seed));
}

END_NAMESPACE(Math)
