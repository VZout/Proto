#include "GenerateResourceID.h"

#include "GetInvalidResourceID.h"

USING_NAMESPACE(Utility)

BEGIN_NAMESPACE(Resources)

ResourceID GenerateResourceID(const std::string &a_Name)
{
	return HashedString(a_Name);
}

END_NAMESPACE(Resources)
