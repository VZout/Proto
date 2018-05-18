#include "GetExtensionFromFilename.h"

#include "Platform/Debug/AssertMessage.h"

#include <algorithm>
#include <cctype>

USING_NAMESPACE(Platform)
	
BEGIN_NAMESPACE(IO)

std::string GetExtensionFromFilename(const std::string &a_Filename, bool a_ToUpper /* = false */)
{
#if defined(PROTO_PLATFORM_WIN32)
	char drive[_MAX_DRIVE];
	char directory[_MAX_DIR];
	char filename[_MAX_FNAME];
	char fileExtension[_MAX_EXT];
	_splitpath_s(a_Filename.c_str(), drive, directory, filename, fileExtension);
	std::string extension = std::string(&fileExtension[1]);
#elif defined(PROTO_PLATFORM_RASPBERRY_PI)
	std::string extension;
	const std::string::size_type pos = a_Filename.find_last_of(".");
	if (std::string::npos != pos)
	{
		extension = a_Filename.substr(pos + 1);			
	}	
#endif

	if (a_ToUpper)
	{
		std::transform(extension.begin(), extension.end(), extension.begin(),
			[](unsigned char a_Char) -> unsigned char { return static_cast<unsigned char>(std::toupper(a_Char)); });
	}
	return extension;
}

END_NAMESPACE(IO)
