#pragma once

#include "Proto.h"

#include "NoCopy.h"
#include "Platform/Debug/AssertMessage.h"

BEGIN_NAMESPACE(Utility)

template<typename TYPE>
class Handle
{
public:
	Handle()
		: m_Pointee(NULLPTR)
	{
	}

	Handle(TYPE *a_Pointee)
		: m_Pointee(a_Pointee)
	{
	}

	virtual ~Handle()
	{
	}

	Handle(const Handle &a_Rhs)
		: m_Pointee(a_Rhs.m_Pointee)
	{
	}

	virtual const TYPE* operator->() const
	{
		return m_Pointee;
	}

	Handle& operator=(const Handle &a_Rhs)
	{
		m_Pointee = a_Rhs.m_Pointee;
		return *this;
	}

protected:
	const TYPE& GetPointee() const
	{
		Platform::AssertMessage(NULLPTR != m_Pointee, "Attempt to access an invalid pointee!");
		return *m_Pointee;
	}


	TYPE& GetPointee()
	{
		return const_cast<TYPE&>(const_cast<const Handle<TYPE>*>(this)->GetPointee());
	}

private:
	TYPE *m_Pointee;
};

END_NAMESPACE(Utility)
