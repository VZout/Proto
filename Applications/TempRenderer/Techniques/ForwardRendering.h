#pragma once

#include "Proto.h"
#include "../RenderingTechnique.h"
#include "Graphics/API/GFX.h"

class ForwardRenderingTechnique : public RenderingTechnique
{
public:
	ForwardRenderingTechnique(GFXAPI a_API, GFXRenderTargetHandle a_RenderTarget);
	virtual ~ForwardRenderingTechnique();

	virtual void Initialize() OVERRIDE;
};