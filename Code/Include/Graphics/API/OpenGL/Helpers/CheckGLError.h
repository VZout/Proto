#pragma once

#include "Graphics/API/OpenGL/OpenGLIncludes.h"

#if defined(GFX_API_OPENGL)

void CheckGLError(GLenum a_Source, GLenum a_Type, GLuint a_ID, GLenum a_Severity, GLsizei a_Length, const GLchar *a_Message, const void *a_Data);

#endif
