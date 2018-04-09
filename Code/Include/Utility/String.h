#pragma once

#include "Proto.h"
#include "BasicString.h"

BEGIN_NAMESPACE(Utility)

class String : public BasicString<char>
{
public:
	String();
	String(const char *a_String);
	virtual ~String();

	String& operator+=(const String &a_Rhs)
	{
		uint32_t newLength = m_Length + a_Rhs.m_Length;
		char *temp = m_String;
		m_String = new char[static_cast<size_t>(newLength + 1)];

		memcpy(m_String, temp, static_cast<size_t>(newLength + 1));
		memcpy(m_String + m_Length, a_Rhs.m_String, static_cast<size_t>(a_Rhs.m_Length));
		m_String[static_cast<size_t>(newLength)] = '\0';
		m_Length = newLength;

		delete[] temp;
		return  *this;
	}

	String& operator-=(const String &a_Rhs)
	{
		UNUSED(a_Rhs);
		return *this;
	}

	friend String operator+(String a_Lhs, const String& a_Rhs)
	{
		a_Lhs += a_Rhs;
		return a_Lhs;
	}

	friend String operator-(String a_Lhs, const String& a_Rhs)
	{
		a_Lhs -= a_Rhs;
		return a_Lhs;
	}
};

END_NAMESPACE(Utility)
