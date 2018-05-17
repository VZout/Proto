#pragma once

#include "Proto.h"
#include "Graphics/API/GFX.h"

FORWARD_DECLARE(Graphics, class Mesh)

void GenerateSphere(GFXAPI &a_API, Graphics::Mesh &a_Mesh, float a_Radius, int a_Slices, int a_Stacks, uint32_t a_VertexFormat);
