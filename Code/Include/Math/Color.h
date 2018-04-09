#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Math)

class Color
{
public:
	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Black;
	static const Color White;
	static const Color CornflowerBlue;

public:
	Color();
	Color(float a_R, float a_G, float a_B, float a_A = 1.0f);
	~Color();

	void Set(float a_R, float a_G, float a_B, float a_A = 1.0f);
	float GetR() const;
	float GetG() const;
	float GetB() const;
	float GetA() const;

#pragma warning( push )
#pragma warning( disable : 4201 )
	union
	{
		float m_F[4];
		struct
		{
			float m_R;
			float m_G;
			float m_B;
			float m_A;
		};
	};
#pragma warning(pop)
};

END_NAMESPACE(Math)
