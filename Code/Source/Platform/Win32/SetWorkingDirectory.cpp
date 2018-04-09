#include "SetWorkingDirectory.h"

#include "Platform/Debug/AssertMessage.h"
#include "Platform/Helpers/StringFunctions.h"
#include "Platform/Window.h"

#include <string>

BEGIN_NAMESPACE(Platform)

void SetWorkingDirectory(const std::string &a_Path)
{	
	BOOL result = ::SetCurrentDirectory(StringToWideString(a_Path).c_str());
	AssertMessage(TRUE == result, "Failed to set current directory!");
}

END_NAMESPACE(Platform)
