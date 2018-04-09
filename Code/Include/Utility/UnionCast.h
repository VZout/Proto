#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Utility)

template<typename TO, typename FROM>
union UnionCastOp 
{
	FROM m_From;
	TO m_To;

	UnionCastOp(FROM a_From)
		: m_From(a_From) 
	{
	}

	TO GetTo() const 
	{
		return m_To; 
	}
};

template <class TO, class FROM> 
TO UnionCast(FROM a_From)
{
	UnionCastOp<TO, FROM> castingOperator(a_From);
	return castingOperator.GetTo();
}

END_NAMESPACE(Utility)
