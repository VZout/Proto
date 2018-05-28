#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Graphics)

class Camera;
class Frustum2D;
class Frustum3D;
void CreateFrustum(Frustum2D &a_Frustum, const Camera &a_Camera);
void CreateFrustum(Frustum3D &a_Frustum, const Camera &a_Camera);

END_NAMESPACE(Graphics)
