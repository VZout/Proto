#pragma once

#include "imgui/imgui.h"
#include "imgui/Helpers/ImGuiHelpers.h"
#if defined(GFX_API_DX11)
#include "imgui/Impl/imgui_impl_dx11.h"
#elif defined(GFX_API_DX12)
#elif defined(GFX_API_OPENGL)
#include "imgui/Impl/imgui_impl_gl3.h"
#elif defined(GFX_API_OPENGLES)
#elif defined(GFX_API_VULKAN)
#elif defined(GFX_API_ORBIS)
#endif
