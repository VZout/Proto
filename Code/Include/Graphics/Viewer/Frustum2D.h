#pragma once

#include "Proto.h"
#include "Frustum.h"

BEGIN_NAMESPACE(Graphics)

class Frustum2D : public Frustum
{
public:
	Frustum2D();
	virtual ~Frustum2D();

private:
	uint32_t m_MinX;
	uint32_t m_MaxX;
	uint32_t m_MinY;
	uint32_t m_MaxY;

	friend void CreateFrustum(Frustum2D&, const Camera&);
};

END_NAMESPACE(Graphics)
