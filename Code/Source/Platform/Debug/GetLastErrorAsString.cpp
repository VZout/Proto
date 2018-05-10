#include "GetLastErrorAsString.h"

#include "Platform/PlatformIncludes.h"

BEGIN_NAMESPACE(Platform)

std::string GetLastErrorAsString()
{
	std::string errorMessage;
#if defined(PROTO_PLATFORM_WIN32)
	const DWORD errorMessageID = ::GetLastError();
	if (0 != errorMessageID)
	{
		LPSTR messageBuffer = NULLPTR;
		const size_t size = ::FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)(&messageBuffer), 0, NULL);
		errorMessage = std::string(messageBuffer, size);
		::LocalFree(messageBuffer);
	}
#elif defined(PROTO_PLATFORM_RASPBERRY_PI)
#endif
	return errorMessage;
}

END_NAMESPACE(Platform)
