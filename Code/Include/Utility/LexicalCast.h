#pragma once

#include "Proto.h"

#include <boost/lexical_cast.hpp>

BEGIN_NAMESPACE(Utility)

template<typename T>
inline T LexicalCast(const std::string &a_String)
{
    return boost::lexical_cast<T>(a_String.c_str());
}

template<typename INPUT_TYPE, typename OUTPUT_TYPE>
inline OUTPUT_TYPE LexicalCast(const INPUT_TYPE& a_Value)
{
    return boost::lexical_cast<OUTPUT_TYPE>(a_Value);
}

END_NAMESPACE(Utility)
