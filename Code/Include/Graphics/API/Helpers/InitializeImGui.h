#pragma once

#include "Graphics/API/GFX.h"

void GFXInitializeImGui(GFXAPI a_API);
void GFXImGuiNewFrame(GFXAPI a_API, GFXCommandListHandle a_CommandList);
void GFXImGuiRenderDrawData();
void GFXTerminateImGui();
