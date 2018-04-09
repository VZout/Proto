#include "Color.h"

BEGIN_NAMESPACE(Math)

const Color Color::Red = Color(1.0f, 0.0f, 0.0f, 1.0f);
const Color Color::Green = Color(0.0f, 1.0f, 0.0f, 1.0f);
const Color Color::Blue = Color(0.0f, 0.0f, 1.0f, 1.0f);
const Color Color::Black = Color(0.0f, 0.0f, 0.0f, 1.0f);
const Color Color::White = Color(1.0f, 1.0f, 1.0f, 1.0f);
const Color Color::CornflowerBlue = Color(100.0f / 255.0f, 149.0f / 255.0f, 237.0f / 255.0f, 1.0f);

Color::Color()
	: m_R(0.0f)
	, m_G(0.0f)
	, m_B(0.0f)
	, m_A(0.0f)
{
}

Color::Color(float a_R, float a_G, float a_B, float a_A /* = 1.0f */)
	: m_R(a_R)
	, m_G(a_G)
	, m_B(a_B)
	, m_A(a_A)
{
}

Color::~Color()
{
}

void Color::Set(float a_R, float a_G, float a_B, float a_A /* = 1.0f */)
{
	m_R = a_R;
	m_G = a_G;
	m_B = a_B;
	m_A = a_A;
}

float Color::GetR() const
{
	return m_R;
}

float Color::GetG() const
{
	return m_G;
}

float Color::GetB() const
{
	return m_B;
}

float Color::GetA() const
{
	return m_A;
}

END_NAMESPACE(Math)
