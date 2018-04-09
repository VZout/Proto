#pragma once

#include "Proto.h"
#include "Math/EHandedness.h"
#include "Math/EUnit.h"
#include "ProjectionMatrix.h"

BEGIN_NAMESPACE(Graphics)

class PerspectiveProjectionMatrix : public ProjectionMatrix
{
public:
	PerspectiveProjectionMatrix(Math::EHandedness a_Handedness = Math::EHandedness_Left);
	virtual ~PerspectiveProjectionMatrix();

	void Initialize(float a_FOVDegrees, float a_AspectRatio, float a_Near, float a_Far);

	float GetFOV(Math::EUnit a_Unit) const;
	float GetAspectRatio() const;

	//static void* operator new (size_t a_Size);
	//static void operator delete (void *a_Pointer);

private:
	virtual void UpdateMatrix() const;

	float m_FOVDegrees;
	float m_FOVRadians;
	float m_AspectRatio;
};

END_NAMESPACE(Graphics)
