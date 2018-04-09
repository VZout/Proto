#include "Utility/TokenizeString.h"

BEGIN_NAMESPACE(Utility)

// std::vector<std::string> Tokenize(const std::string &a_String, const std::string &a_Delimiter)
// {
// 	size_t pos = 0;
// 	size_t previousPos = 0;
// 	std::vector<std::string> tokens;
// 
// 	while (std::string::npos != (pos = a_String.find(a_Delimiter, pos)))
// 	{
// 		tokens.push_back(a_String.substr(0, pos));
// 		previousPos = pos + 1;
// 		pos += a_Delimiter.length();
// 	}
// 	if (std::string::npos == pos)
// 	{
// 		tokens.push_back(a_String.substr(previousPos, a_String.length() - previousPos));
// 	}
// 
// 	return tokens;
// }
// 
// std::vector<std::string> Tokenize(const std::string &a_String, const char *a_Separator)
// {
// 	return Tokenize(a_String, std::string(a_Separator));
// }

END_NAMESPACE(Utility)
