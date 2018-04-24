#pragma once

#include "Graphics/API/GFX.h"

#include <string>
#include <vector>

GFXTextureHandle LoadTexture(GFXAPI &a_API, const std::string &a_Filename);
GFXShaderHandle LoadShader(GFXAPI &a_API, const std::string &a_VertexShaderFilename, const std::string &a_FragmentShaderFilename);
