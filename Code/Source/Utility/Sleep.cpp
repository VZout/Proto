#include "Utility/Sleep.h"

BEGIN_NAMESPACE(Utility)

void Sleep::MilliSeconds(uint32_t a_MilliSeconds)
{
#if defined(PROTO_PLATFORM_WIN32)
	::Sleep(a_MilliSeconds);
#else
	usleep(a_MilliSeconds * 1000);
#endif
}

END_NAMESPACE(Utility)
