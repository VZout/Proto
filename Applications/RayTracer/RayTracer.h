#pragma once

#include "Proto.h"
#include "Graphics/API/GFX.h"

FORWARD_DECLARE(Platform, class Window)

class RayTracer
{
public:
	RayTracer();
	~RayTracer();

	void Initialize(Platform::Window &a_Window);

private:
	GFXAPI m_API;
};