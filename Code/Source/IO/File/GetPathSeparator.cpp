#include "GetPathSeparator.h"

BEGIN_NAMESPACE(IO)

const char GetPathSeparator()
{
#if defined(PROTO_PLATFORM_WIN32)
	return '\\';
#elif defined(PROTO_PLATFORM_ORBIS)
	assert(false);
#elif defined(PROTO_PLATFORM_PSP2)
	assert(false);
#elif defined(PROTO_PLATFORM_RASPBERRY_PI)
	assert(false);
#endif
}

END_NAMESPACE(IO)
