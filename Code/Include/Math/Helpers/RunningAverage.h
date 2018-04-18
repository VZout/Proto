#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Math)

template<typename DATATYPE>
class RunningAverage
{
public:
	RunningAverage()
		: m_Average(0.0f)
		, m_Count(0)
	{
	}

	void Add(DATATYPE a_Value)
	{
		m_Average = (m_Average * m_Count + a_Value) / static_cast<DATATYPE>(m_Count + 1);
		m_Count++;
	}

	DATATYPE GetAverage() const
	{
		return m_Average;
	}

	uint32_t GetNumValues() const
	{
		return m_Count;
	}

private:
	DATATYPE m_Average;
	uint32_t m_Count;
};

END_NAMESPACE(Math)
