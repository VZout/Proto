#pragma once

#include "OpenGLESIncludes.h"

#if defined(GFX_API_OPENGLES)

typedef struct GLESParameters
{
	int MAX_VERTEX_ATTRIBUTES;
	const GLubyte *m_GLESVersion;
	const GLubyte *m_GLSLVersion;
	EGLint m_EGLVersionMajor;
	EGLint m_EGLVersionMinor;
} GLESParameters;

#endif

