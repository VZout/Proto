#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Math)

struct Dimension
{
	Dimension(uint32_t a_Width = static_cast<uint32_t>(-1), uint32_t a_Height = static_cast<uint32_t>(-1))
	: m_Width(a_Width)
	, m_Height(a_Height)
	{
	}

	uint32_t m_Width;
	uint32_t m_Height;
};

END_NAMESPACE(Math)
