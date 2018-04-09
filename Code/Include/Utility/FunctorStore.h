#pragma once

#include "Proto.h"

#include "ENoInit.h"

BEGIN_NAMESPACE(Utility)

template<typename SIGNATURE>
class Functor
{

};

class FunctorStore
{
public:
	FunctorStore()
		: m_Function(0)
		, m_Object(0)
	{
	}

	FunctorStore(ENoInit)
		: m_Function()
		, m_Object()
	{
	}

	bool IsBound() const
	{
		return 0 != m_Function;
	}

	void Reset()
	{
		m_Function = 0;
	}

protected:
	typedef void (*Function)(void);
	Function m_Function;
	void *m_Object;
};


END_NAMESPACE(Utility)
