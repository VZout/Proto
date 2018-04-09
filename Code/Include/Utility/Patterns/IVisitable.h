#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Utility)

template<typename TYPE>
class Visitor;

template<typename TYPE>
class IVisitable
{
public:
	virtual void Accept(Visitor<TYPE> &a_Visitor) = 0;
};

END_NAMESPACE(Utility)
