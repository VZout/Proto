#pragma once

#include "Proto.h"
#include "Math/EHandedness.h"
#include "ProjectionMatrix.h"

BEGIN_NAMESPACE(Graphics)

class OrthographicProjectionMatrix : public ProjectionMatrix
{
public:
	OrthographicProjectionMatrix(Math::EHandedness a_Handedness = Math::EHandedness_Left);
	virtual ~OrthographicProjectionMatrix();

	void Initialize(uint32_t a_Left, uint32_t a_Right, uint32_t a_Bottom, uint32_t a_Top, float a_Near = -1.0f, float a_Far = 1.0f);

	uint32_t GetLeft() const;
	uint32_t GetRight() const;
	uint32_t GetBottom() const;
	uint32_t GetTop() const;

	//static void* operator new (size_t a_Size);
	//static void operator delete (void *a_Pointer);

private:
	virtual void UpdateMatrix() const;

	float m_Left;
	float m_Right;
	float m_Bottom;
	float m_Top;
};

END_NAMESPACE(Graphics)
