#pragma once

#include "Proto.h"
#include "Graphics/API/GFX.h"

FORWARD_DECLARE(Platform, class Window)

class PathTracer
{
public:
	PathTracer();
	~PathTracer();

	void Initialize(Platform::Window &a_Window);
	void Terminate();

private:
	GFXAPI m_API;
};