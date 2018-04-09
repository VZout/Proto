#include "Frustum.h"

// #include "Math/AABB.h"
// #include "Math/Plane.h"
#include "Math/Quaternion.h"
// #include "Math/Sphere.h"
#include "Math/Vector4.h"
#include "Platform/Debug/AssertMessage.h"

USING_NAMESPACE(Math)
USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Graphics)

Frustum::Frustum()
{
}

Frustum::~Frustum()
{
}

// EClassification Frustum::Classify(const Vector3 &a_Point) const
// {
// 	EClassification classification = EClassification_Inside;
// 	for (uint32 planeIndex = 0; planeIndex < 6; ++planeIndex)
// 	{
// 		const float distance = Distance(m_Planes[planeIndex], a_Point);
// 		if (distance < 0.0f)
// 		{
// 			classification = EClassification_Outside;
// 			break;
// 		}
// 	}
// 	return classification;
// }

// EClassification Frustum::Classify(const Vector4 &a_Point) const
// {
// 	return Classify(Vector3(a_Point));
// }

// EClassification Frustum::Classify(const AABB &a_AABB) const
// {
// 	EClassification classification = EClassification_Inside;
// 	for (uint32 planeIndex = 0; planeIndex < 6; ++planeIndex)
// 	{
// 		const Plane &plane = m_Planes[planeIndex];
// 		const Vector3 &planeNormal = plane.GetNormal();
// 		if (Distance(plane, GetPositiveVertex(a_AABB, planeNormal)) < 0.0f)
// 		{
// 			classification = EClassification_Outside;
// 			break;
// 		}
// 		else if (Distance(plane, GetNegativeVertex(a_AABB, planeNormal)) < 0.0f)
// 		{
// 			classification = EClassification_Intersecting;
// 		}
// 	}
// 	return classification;
// }

// EClassification Frustum::Classify(const Sphere &a_Sphere) const
// {
// 	EClassification classification = EClassification_Invalid;
// 	const Vector3 sphereCenter = a_Sphere.GetCenter();
// 	const float sphereRadius = a_Sphere.GetRadius();
// 	for (uint32 planeIndex = 0; planeIndex < 6; ++planeIndex)
// 	{
// 		const float distance = Distance(m_Planes[planeIndex], sphereCenter);
// 		if (distance < -sphereRadius)
// 		{
// 			classification = EClassification_Outside;
// 			break;
// 		}
// 		else if (distance < sphereRadius)
// 		{
// 			classification = EClassification_Intersecting;
// 		}
// 	}
// 	return classification;
// }

END_NAMESPACE(Graphics)
