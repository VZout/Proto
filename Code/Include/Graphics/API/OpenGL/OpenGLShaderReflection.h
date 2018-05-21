#pragma once

#include "Graphics/API/GFX.h"
#include "Graphics/API/OpenGL/OpenGLIncludes.h"
#include "Graphics/API/OpenGL/OpenGLStructs.h"

#if defined(GFX_API_OPENGL)

void InspectShaderItems(GLuint a_ShaderProgram, GLenum a_ProgramInterface, uint32_t *a_NumItems, OpenGLInterfaceItem **a_Items);

#endif
