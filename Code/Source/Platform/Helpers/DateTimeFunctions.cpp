#include "DateTimeFunctions.h"

#if defined(PROTO_BOOST_ENABLED)
#include <locale>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#endif

BEGIN_NAMESPACE(Platform)

std::string GetDateTimeString()
{
#if defined(PROTO_BOOST_ENABLED)
	const boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
	return to_simple_string(now);
#else
	return std::string();
#endif
}

END_NAMESPACE(Platform)
