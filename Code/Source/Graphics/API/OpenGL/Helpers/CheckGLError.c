#include "CheckGLError.h"

#include "Graphics/API/OpenGL/OpenGLIncludes.h"
#include "Graphics/API/Defines.h"

#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>

#if defined(GFX_API_OPENGL)

void CheckGLError(GLenum a_Source, GLenum a_Type, GLuint a_ID, GLenum a_Severity, GLsizei a_Length, const GLchar *a_Message, const void *a_Data) 
{
#if defined(_DEBUG)
	GFX_UNUSED(a_Data);
	GFX_UNUSED(a_Length);

	bool shouldBreak = true;
	char* source;
	switch (a_Source) 
	{
	case GL_DEBUG_SOURCE_API:
		{
			source = "API";
			break;
		}
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
		{
			source = "WINDOW SYSTEM";
			break;
		}
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		{
			source = "SHADER COMPILER";
			break;
		}
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		{
			source = "THIRD PARTY";
			break;
		}
	case GL_DEBUG_SOURCE_APPLICATION:
		{
			source = "APPLICATION";
			break;
		}
	case GL_DEBUG_SOURCE_OTHER:
		{
			source = "UNKNOWN";
			break;
		}
	default:
		{
			source = "UNKNOWN";
			break;
		}
	}

	char* type;
	switch (a_Type)
	{
	case GL_DEBUG_TYPE_ERROR:
	{
			type = "ERROR";
			break;
		}
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		{
			type = "DEPRECATED BEHAVIOR";
			break;
		}
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		{
			type = "UNDEFINED BEHAVIOR";
			break;
		}
	case GL_DEBUG_TYPE_PORTABILITY:
		{
			type = "PORTABILITY";
			break;
		}
	case GL_DEBUG_TYPE_PERFORMANCE:
		{
			type = "PERFORMANCE";
			break;
		}
	case GL_DEBUG_TYPE_OTHER:
		{
			type = "OTHER";
			break;
		}
	case GL_DEBUG_TYPE_MARKER:
		{
			type = "MARKER";
			break;
		}
	default:
		{
			type = "UNKNOWN";
			break;
		}
	}

	char* severity;
	switch (a_Severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:
		{
			severity = "HIGH";
			break;
		}
	case GL_DEBUG_SEVERITY_MEDIUM:
		{
			shouldBreak = false;
			severity = "MEDIUM";
			break;
		}
	case GL_DEBUG_SEVERITY_LOW:
		{
			shouldBreak = false;
			severity = "LOW";
			break;
		}
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		{
			shouldBreak = false;
			severity = "NOTIFICATION";
			break;
		}
	default:
		{
			severity = "UNKNOWN";
			break;
		}
	}

	bool shouldPrint = true;
	if (shouldPrint)
	{
		printf("%d: %s of %s severity, raised from %s: %s\n", a_ID, type, severity, source, a_Message);
	}
	if (shouldBreak)
	{
		assert(false);
	}
#else
	GFX_UNUSED(a_Source);
	GFX_UNUSED(a_Type);
	GFX_UNUSED(a_ID);
	GFX_UNUSED(a_Severity);
	GFX_UNUSED(a_Length);
	GFX_UNUSED(a_Message);
	GFX_UNUSED(a_Data);
#endif
}

#endif