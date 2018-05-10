#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Utility)

template<typename TYPE>
class Vector
{
public:
	Vector()
	{
	}

	~Vector()
	{
	}

	TYPE* GetBegin()
	{
		return const_cast<TYPE*>(const_cast<const Vector<TYPE>*>(this)->GetBegin());
	}

	const TYPE* GetBegin() const
	{
		return m_Begin;
	}

	TYPE* GetEnd()
	{
		return const_cast<TYPE*>(const_cast<const Vector<TYPE>*>(this)->GetEnd());
	}

	const TYPE* GetEnd() const
	{
		return m_End;
	}

	void PushBack(TYPE *a_Value)
	{
	}

private:
	TYPE *m_Begin = NULLPTR;
	TYPE *m_End = NULLPTR;
};

END_NAMESPACE(Utility)
