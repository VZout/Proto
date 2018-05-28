#pragma once

#include "API/GFX.h"
#include "Proto.h"

BEGIN_NAMESPACE(Graphics)

class Mesh;

void CreateSphere(GFXAPI &a_API, Graphics::Mesh &a_Mesh, float a_Radius, int a_Slices, int a_Stacks, uint32_t a_VertexFormat);
void CreateCube();
void CreateCone();
void CreateTorus();

END_NAMESPACE(Graphics)
