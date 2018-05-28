#include "GetInvalidResourceID.h"

USING_NAMESPACE(Utility)

BEGIN_NAMESPACE(Resources)

ResourceID GetInvalidResourceID()
{
	return HashedString::Invalid;
}

END_NAMESPACE(Resources)
