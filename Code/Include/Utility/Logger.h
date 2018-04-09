#pragma once

#include "Proto.h"

#include <boost/format.hpp>
#include <string>

BEGIN_NAMESPACE(Utility)

class Logger
{
public:
	template <typename... TArgs>
	void WriteLine(const char* a_Format, TArgs&&... a_Args) const
	{
		using namespace boost::io;
		boost::format message(a_Format);
		WriteLine(FormatStringRecurse(message, std::forward<TArgs>(a_Args)...));
	}

private:
	virtual void WriteLine(const std::string &a_Line) const = 0;

	inline static std::string FormatStringRecurse(boost::format& a_Message)
	{
		return a_Message.str();
	}

	template <typename TValue, typename... TArgs>
	std::string FormatStringRecurse(boost::format& a_Message, TValue&& a_Arg, TArgs&&... a_Args) const
	{
		a_Message % std::forward<TValue>(a_Arg);
		return FormatStringRecurse(a_Message, std::forward<TArgs>(a_Args)...);
	}
};

END_NAMESPACE(Utility)
