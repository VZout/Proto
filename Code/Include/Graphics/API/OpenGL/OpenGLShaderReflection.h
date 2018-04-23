#pragma once

#include "Graphics/API/GFX.h"
#include "Graphics/API/OpenGL/OpenGLIncludes.h"
#include "Graphics/API/OpenGL/OpenGLStructs.h"

#if defined(GFX_API_OPENGL)

void InspectShaderProgram(OpenGLAPI *a_API, GLuint a_ShaderProgram);

#endif
