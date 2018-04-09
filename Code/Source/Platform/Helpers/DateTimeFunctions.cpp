#include "DateTimeFunctions.h"

#include <locale>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>

BEGIN_NAMESPACE(Platform)

std::string GetDateTimeString()
{
	const boost::posix_time::ptime now = boost::posix_time::second_clock::local_time();
	return to_simple_string(now);
}

END_NAMESPACE(Platform)
