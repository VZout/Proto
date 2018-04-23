#pragma once

#include "VulkanIncludes.h"

#include <stdint.h>

#if defined(GFX_API_VULKAN)

typedef struct VulkanParameters
{
	const char *m_EngineName;
	const char *m_ApplicationName;
	uint32_t m_NumEnabledLayers;
	const char* const* m_EnabledLayers;
	uint32_t m_NumEnabledExtensions;
	const char* const* m_EnabledExtensions;
} VulkanParameters;

#endif
