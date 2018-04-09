#pragma once

#include "Proto.h"
#include "Frustum.h"

BEGIN_NAMESPACE(Graphics)

class Frustum3D : public Frustum
{
public:
	Frustum3D();
	virtual ~Frustum3D();

	friend void CreateFrustum(Frustum3D&, const Camera&);
};

END_NAMESPACE(Graphics)
