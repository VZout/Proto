#pragma once

// TODO: duplication string formatting from logger..!

#include "Proto.h"

#if defined(PROTO_BOOST_ENABLED)
#include <boost/format.hpp>
#endif
#include <sstream>
#include <vector>

BEGIN_NAMESPACE(Platform)

size_t ConvertString(const char *a_Input, wchar_t *a_Output);
size_t ConvertString(const wchar_t *a_Input, char *&a_Output);
std::wstring StringToWideString(const std::string &a_String);
std::string WideStringToString(const std::wstring &a_String);
std::vector<std::string> Tokenize(const std::string &a_String, const std::string &a_Delimiters);

void LTrim(std::string &a_String);
void RTrim(std::string &a_String);
void Trim(std::string &a_String);

template<typename TYPE>
std::string Append(const std::string &a_Text, TYPE a_Value)
{
	std::ostringstream s;
	s << a_Text << a_Value;
	return s.str();
}
class StringFormatter
{
public:
#if defined(PROTO_CPP11)
	template <typename... TArgs>
	static std::string Format(const char* a_Format, TArgs&&... a_Args)
	{
#if defined(PROTO_BOOST_ENABLED)
		using namespace boost::io;
		boost::format message(a_Format);
		return FormatStringRecurse(message, std::forward<TArgs>(a_Args)...);
#endif
	}
#endif

#if defined(PROTO_CPP11)
	template <typename... TArgs>
	static const char* FormatCString(const char* a_Format, TArgs&&... a_Args)
	{
#if defined(PROTO_BOOST_ENABLED)
		using namespace boost::io;
		boost::format message(a_Format);
		return FormatStringRecurse(message, std::forward<TArgs>(a_Args)...).c_str();
#endif
	}
#endif

private:
#if defined(PROTO_BOOST_ENABLED)
	inline static std::string FormatStringRecurse(boost::format& a_Message)
	{
		return a_Message.str();
	}
#endif

#if defined(PROTO_CPP11)
	template <typename TValue, typename... TArgs>
	static std::string FormatStringRecurse(boost::format& a_Message, TValue&& a_Arg, TArgs&&... a_Args)
	{
#if defined(PROTO_BOOST_ENABLED)
		a_Message % std::forward<TValue>(a_Arg);
		return FormatStringRecurse(a_Message, std::forward<TArgs>(a_Args)...);
#endif
	}
#endif
};

END_NAMESPACE(Platform)
