#include "CreateFrustum.h"

#include "Math/Matrix4.h"
// #include "Math/Plane.h"
#include "Platform/Debug/AssertMessage.h"
#include "Camera.h"
#include "Frustum2D.h"
#include "Frustum3D.h"
#include "EProjectionMatrix.h"
#include "ProjectionMatrix.h"
#include "OrthographicProjectionMatrix.h"
#include "PerspectiveProjectionMatrix.h"

USING_NAMESPACE(Math)
USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Graphics)

void CreateFrustum(Frustum2D &a_Frustum, const Camera &a_Camera)
{
	UNUSED(a_Frustum);
	UNUSED(a_Camera);
// 	const OrthographicProjectionMatrix &projectionMatrix = static_cast<const OrthographicProjectionMatrix&>(a_Camera.GetProjectionMatrix(EProjectionMatrix_Orthographic));
// 
// 	a_Frustum.m_MinX = projectionMatrix.GetLeft();
// 	a_Frustum.m_MaxX = projectionMatrix.GetRight();
// 	a_Frustum.m_MinY = projectionMatrix.GetTop();
// 	a_Frustum.m_MaxY = projectionMatrix.GetBottom();
}

void CreateFrustum(Frustum3D &a_Frustum, const Camera &a_Camera)
{
	UNUSED(a_Frustum);
	UNUSED(a_Camera);
// 	const Matrix4 &viewMatrix = a_Camera.GetViewMatrix();
// 
// 	const Vector3 &xAxis = Vector3::X_AXIS;
// 	const Vector3 &yAxis = Vector3::Y_AXIS;
// 
// 	const Vector3 &cameraPosition = a_Camera.GetPosition();
// 
// 	AssertMessage(EProjectionMatrix_Perspective == a_Camera.GetProjectionMatrix().GetType(), ("No valid perspective projection matrix available!"));
// 	const PerspectiveProjectionMatrix &projectionMatrix = static_cast<const PerspectiveProjectionMatrix&>(a_Camera.GetProjectionMatrix());
// 
// 	const Vector3 &farPlaneCenter = Vector3::Z_AXIS * projectionMatrix.GetFar();
// 	const Vector3 &nearPlaneCenter = Vector3::Z_AXIS * projectionMatrix.GetNear();
// 	a_Frustum.m_Planes[Frustum::EPlane_Near].SetNormalAndPoint(Vector3::Z_AXIS, nearPlaneCenter);
// 	a_Frustum.m_Planes[Frustum::EPlane_Far].SetNormalAndPoint(Vector3::NEG_Z_AXIS, farPlaneCenter);
// 
// 	const float nearplaneHeight = tan(projectionMatrix.GetFOV(EUnit_Radians) * 0.5f) * projectionMatrix.GetNear();
// 	const float nearplaneWidth = nearplaneHeight * projectionMatrix.GetAspectRatio();
// 
// 	Vector3 auxiliary, planeNormal;
// 	auxiliary = (nearPlaneCenter + yAxis * nearplaneHeight);
// 	Normalize(auxiliary);
// 	planeNormal = Cross(auxiliary, xAxis);
// 	a_Frustum.m_Planes[Frustum::EPlane_Top].SetNormalAndPoint(-planeNormal, nearPlaneCenter + yAxis * nearplaneHeight);
// 
// 	auxiliary = (nearPlaneCenter - yAxis * nearplaneHeight);
// 	Normalize(auxiliary);
// 	planeNormal = Cross(xAxis, auxiliary);
// 	a_Frustum.m_Planes[Frustum::EPlane_Bottom].SetNormalAndPoint(-planeNormal, nearPlaneCenter - yAxis * nearplaneHeight);
// 
// 	auxiliary = (nearPlaneCenter - xAxis * nearplaneWidth);
// 	Normalize(auxiliary);
// 	planeNormal = Cross(auxiliary, yAxis);
// 	a_Frustum.m_Planes[Frustum::EPlane_Left].SetNormalAndPoint(-planeNormal, nearPlaneCenter - xAxis * nearplaneWidth);
// 
// 	auxiliary = (nearPlaneCenter + xAxis * nearplaneWidth);
// 	Normalize(auxiliary);
// 	planeNormal = Cross(yAxis, auxiliary);
// 	a_Frustum.m_Planes[Frustum::EPlane_Right].SetNormalAndPoint(-planeNormal, nearPlaneCenter + xAxis * nearplaneWidth);
}

END_NAMESPACE(Graphics)
