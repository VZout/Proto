#pragma once

#include "Proto.h"

#if defined (PROTO_BOOST_ENABLED)
#include <boost/format.hpp>
#endif
#include <string>

BEGIN_NAMESPACE(Utility)

class Logger
{
public:
	virtual ~Logger()
	{
	}

#if defined (PROTO_CPP11)
	template <typename... TArgs>
	void WriteLine(const char* a_Format, TArgs&&... a_Args) const
	{
#if defined (PROTO_BOOST_ENABLED)
		using namespace boost::io;
		boost::format message(a_Format);
		WriteLine(FormatStringRecurse(message, std::forward<TArgs>(a_Args)...));
#endif
	}
#endif

private:
	virtual void WriteLine(const std::string &a_Line) const = 0;

#if defined (PROTO_BOOST_ENABLED)
	inline static std::string FormatStringRecurse(boost::format& a_Message)
	{
		return a_Message.str();
	}
#endif

#if defined (PROTO_BOOST_ENABLED)
	template <typename TValue, typename... TArgs>
	std::string FormatStringRecurse(boost::format& a_Message, TValue&& a_Arg, TArgs&&... a_Args) const
	{
		a_Message % std::forward<TValue>(a_Arg);
		return FormatStringRecurse(a_Message, std::forward<TArgs>(a_Args)...);
	}
#endif
};

END_NAMESPACE(Utility)
