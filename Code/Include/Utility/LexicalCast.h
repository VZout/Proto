#pragma once

#include "Proto.h"

#if defined(PROTO_BOOST_ENABLED)
#include <boost/lexical_cast.hpp>
#endif

BEGIN_NAMESPACE(Utility)

template<typename T>
inline T LexicalCast(const std::string &a_String)
{
#if defined(PROTO_BOOST_ENABLED)
	return boost::lexical_cast<T>(a_String.c_str());
#else
	return T();
#endif
}

template<typename INPUT_TYPE, typename OUTPUT_TYPE>
inline OUTPUT_TYPE LexicalCast(const INPUT_TYPE& a_Value)
{
#if defined(PROTO_BOOST_ENABLED)
	return boost::lexical_cast<OUTPUT_TYPE>(a_Value);
#else
	return OUTPUT_TYPE();
#endif
}

END_NAMESPACE(Utility)
