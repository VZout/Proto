#pragma once

#include "Proto.h"

#include <cstring>

BEGIN_NAMESPACE(Utility)

template<typename TYPE>
class BasicString
{
public:
	BasicString()
	{
	}

	BasicString(const TYPE *a_String)
	{
		m_Length = 0;
		while (a_String[static_cast<size_t>(m_Length)] != '\0')
		{
			m_Length++;
		}
		m_String = new TYPE[static_cast<size_t>(m_Length + 1)];
		memcpy(m_String, a_String, static_cast<size_t>(m_Length));
		m_String[static_cast<size_t>(m_Length)] = '\0';
	}

	BasicString(const BasicString &a_String)
	{
		Copy(a_String);
	}

	BasicString(BasicString &&a_String)
	{
		Move(a_String);
	}

	BasicString& operator=(const BasicString &a_String)
	{
		if (this != &a_String)
		{
			delete[] m_String;
			Copy(a_String);
		}
		return  *this;
	}

	BasicString& operator=(BasicString &&a_String)
	{
		if (this != &a_String)
		{
			Move(a_String);
		}
		return  *this;

	}

	virtual ~BasicString()
	{
		delete[] m_String;
	}

	const TYPE* GetCString() const
	{
		return &m_String[0];
	}

	uint32_t GetLength() const
	{
		return m_Length;
	}

protected:
	uint32_t m_Length = 0;
	TYPE *m_String = nullptr;

private:
	void Copy(const BasicString &a_String)
	{
		if (a_String.m_Length > 0)
		{
			m_Length = a_String.m_Length;
			m_String = new TYPE[static_cast<size_t>(m_Length + 1)];
			memcpy(m_String, a_String.m_String, static_cast<size_t>(m_Length + 1));
		}
		else
		{
			m_Length = 0;
			m_String = nullptr;
		}
	}

	void Move(BasicString &a_String)
	{
		delete[] m_String;
		if (a_String.m_Length > 0)
		{
			m_Length = a_String.m_Length;
			m_String = new TYPE[static_cast<size_t>(m_Length + 1)];
			memcpy(m_String, a_String.m_String, static_cast<size_t>(m_Length + 1));
		}
		else
		{
			m_Length = 0;
			m_String = nullptr;
		}

		a_String.m_Length = 0;
		delete[] a_String.m_String;
	}
};

END_NAMESPACE(Utility)
