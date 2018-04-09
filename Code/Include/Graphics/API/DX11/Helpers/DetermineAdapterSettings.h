#pragma once

#include <stdint.h>

#if defined(GFX_API_DX11)

void DetermineAdapterSettings(uint32_t a_Width, uint32_t a_Height, uint32_t *a_Numerator, uint32_t *a_Denominator, uint32_t *a_VideoCardMemory, char **a_VideoCardDescription);

#endif
