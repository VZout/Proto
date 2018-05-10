#pragma once

#include "Proto.h"
#include "Platform/Debug/AssertMessage.h"

BEGIN_NAMESPACE(Utility)

template<typename TYPE>
class Array3D
{
public:
	Array3D(uint32_t a_Width, uint32_t a_Height, uint32_t a_Depth)
		: m_Width(a_Width)
		, m_Height(a_Height)
		, m_Depth(a_Depth)
	{
		m_Data = new TYPE[a_Width * a_Height * a_Depth];
		::memset(m_Data, 0, m_Width * m_Height * a_Depth * sizeof(TYPE));
	}

	~Array3D()
	{
		delete[] m_Data;
	}

	TYPE& At(uint32_t a_Column, uint32_t a_Row, uint32_t a_Slice)
	{
		Platform::AssertMessage(a_Column < m_Width && a_Row < m_Height && a_Slice < m_Depth, "Invalid index into array!");
		return m_Data[a_Column + a_Row * m_Width];
	}

private:
	uint32_t m_Width = 0;
	uint32_t m_Height = 0;
	uint32_t m_Depth = 0;
	TYPE *m_Data = NULLPTR;
};

END_NAMESPACE(Utility)
