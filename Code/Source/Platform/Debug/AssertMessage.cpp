#include "AssertMessage.h"

#include "Platform/Helpers/StringFunctions.h"

#include <assert.h>
#include <string>

USING_NAMESPACE(Utility)

BEGIN_NAMESPACE(Platform)

void Assert(bool a_Condition)
{
#if defined(PROTO_PLATFORM_WIN32)
	if (!a_Condition)
	{
		const char *text = "Assertion triggered!\0";
		::MessageBoxA(0, text, "Error!", MB_ICONERROR | MB_OK);
		assert(false);
	}
#elif defined(PROTO_PLATFORM_RASPBERRY_PI)
#endif
}

void AssertMessage(const Utility::String &a_Text)
{
	AssertMessage(false, a_Text);
}

void AssertMessage(bool a_Condition, const Utility::String &a_Text)
{
	if (!a_Condition)
	{
#if defined(PROTO_PLATFORM_WIN32)
		::MessageBoxA(0, a_Text.GetCString(), "Error!", MB_ICONERROR | MB_OK);
#elif defined(PROTO_PLATFORM_RASPBERRY_PI)
#endif
		assert(false);
	}
}

END_NAMESPACE(Platform)
