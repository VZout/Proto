#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Math)

template <typename T> 
const T Max(const T& a_Value1, const T& a_Value2)
{
    return(a_Value2 < a_Value1) ? a_Value1 : a_Value2;
}

END_NAMESPACE(Math)
