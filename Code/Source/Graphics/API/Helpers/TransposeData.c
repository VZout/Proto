#include "TransposeData.h"

#include "Graphics/API/Defines.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void TransposeData(const void *a_Source, void *a_Destination, uint32_t a_Size, GFXDataType a_Type)
{
#if !defined(NDEBUG)
	assert(DataType_Float == a_Type);
	assert(64 == a_Size);
#else
	GFX_UNUSED(a_Type);
	GFX_UNUSED(a_Size);
#endif
	float *sourceBuffer = (float*)a_Source;
	float *destinationBuffer = (float*)a_Destination;
	uint32_t i;
	for (i = 0; i < 4; i++)
	{
		destinationBuffer[i + 0] = sourceBuffer[(i * 4) + 0];
		destinationBuffer[i + 4] = sourceBuffer[(i * 4) + 1];
		destinationBuffer[i + 8] = sourceBuffer[(i * 4) + 2];
		destinationBuffer[i + 12] = sourceBuffer[(i * 4) + 3];
	}
}
