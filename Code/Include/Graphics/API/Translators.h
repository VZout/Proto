#pragma once

#if defined(GFX_API_DX11)
#include "DX11/DX11Translators.h"
#elif defined(GFX_API_DX12)
#include "DX12/DX12Translators.h"
#elif defined(GFX_API_OPENGL)
#include "OpenGL/OpenGLTranslators.h"
#elif defined(GFX_API_OPENGLES)
#include "OpenGLES/OpenGLESTranslators.h"
#elif defined(GFX_API_VULKAN)
#include "Vulkan/VulkanTranslators.h"
#elif defined(GFX_API_ORBIS)
#include "ORBIS/ORBISTranslators.h"
#elif defined(GFX_API_PSP2)
#include "PSP2/PSP2Translators.h"
#else
#error Not implemented for requested platform!
#endif
