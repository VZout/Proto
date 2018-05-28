#pragma once

#include "Proto.h"
#include "../RenderingTechnique.h"
#include "Graphics/API/GFX.h"

FORWARD_DECLARE(Resources, class ResourceManager)

BEGIN_NAMESPACE(Graphics)

class ForwardRenderingTechnique : public RenderingTechnique
{
public:
	ForwardRenderingTechnique(GFXAPI a_API, GFXRenderTargetHandle a_RenderTarget);
	virtual ~ForwardRenderingTechnique();

	virtual void Initialize(Resources::ResourceManager &a_ResourceManager) OVERRIDE;
};

END_NAMESPACE(Graphics)
