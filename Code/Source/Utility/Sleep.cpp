#include "Utility/Sleep.h"

#include "Platform/PlatformIncludes.h"

BEGIN_NAMESPACE(Utility)

void Sleep::MilliSeconds(uint32_t a_MilliSeconds)
{
#if defined(PROTO_PLATFORM_WIN32)
	::Sleep(a_MilliSeconds);
#elif defined(PROTO_PLATFORM_RASPBERRYPI)
	usleep(a_MilliSeconds * 1000);
#endif
}

END_NAMESPACE(Utility)
