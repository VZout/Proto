#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Utility)

template<typename TYPE>
class IVisitor
{
public:
	virtual void Visit(TYPE &a_Type) = 0;
};

END_NAMESPACE(Utility)
