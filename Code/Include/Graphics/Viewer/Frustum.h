#pragma once

#include "Proto.h"
// #include "Math/Helpers/EClassification.h"
// #include "Math/Plane.h"
#include "Utility/NoCopy.h"

FORWARD_DECLARE(Math, class AABB)
FORWARD_DECLARE(Math, class Matrix4)
FORWARD_DECLARE(Math, class Sphere)
FORWARD_DECLARE(Math, class Vector4)

BEGIN_NAMESPACE(Graphics)

class Camera;
class Frustum2D;
class Frustum3D;

class Frustum : public Utility::NoCopy
{
public:
	enum EPlane
	{
		EPlane_Right = 0,
		EPlane_Left,
		EPlane_Top,
		EPlane_Bottom,
		EPlane_Near,
		EPlane_Far
	};

public:
	Frustum();
	virtual ~Frustum();

// 	Math::EClassification Classify(const Math::Vector3 &a_Point) const;
// 	Math::EClassification Classify(const Math::Vector4 &a_Point) const;
// 	Math::EClassification Classify(const Math::AABB &a_AABB) const;
// 	Math::EClassification Classify(const Math::Sphere &a_Sphere) const;

public:
// 	Math::Plane m_Planes[6];

	friend void CalculateFrustum(Frustum3D&, const Camera&);
};

END_NAMESPACE(Graphics)
