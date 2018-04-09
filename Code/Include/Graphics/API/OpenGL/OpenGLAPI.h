#pragma once

#include "OpenGLIncludes.h"

#if defined(GFX_API_OPENGL)

typedef struct GLParameters
{
	int m_MajorVersion;
	int m_MinorVersion;

	int MAX_VERTEX_ATTRIBUTES;
	const GLubyte *m_Version;
} GLParameters;

#endif

