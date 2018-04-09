#pragma once

#include "Graphics/API/Enums.h"

#include <stdint.h>

void TransposeData(const void *a_Source, void *a_Destination, uint32_t a_Size, GFXDataType a_Type);
