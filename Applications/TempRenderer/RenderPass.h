#pragma once

#include "Graphics/API/GFX.h"

class RenderPass
{
public:
	RenderPass();
	~RenderPass();

	void Update();

private:
	GFXCommandListHandle m_CommandList;
};