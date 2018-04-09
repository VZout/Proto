#include "CheckGLESError.h"

#include "Graphics/API/OpenGLES/OpenGLESIncludes.h"

#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>

#if defined(GFX_API_OPENGLES)

void CheckGLESError()
{
#if defined(_DEBUG)
	const GLenum errorCode = glGetError();
	if (GL_NO_ERROR != errorCode)
	{
		char *message = "";

		switch (errorCode)
		{
		case GL_INVALID_ENUM:
			{
				message = "INVALID ENUM: an unacceptable value is specified for an enumerated argument.The offending command is ignored and has no other side effect than to set the error flag.";
				break;
			}
		case GL_INVALID_VALUE:
			{
				message = "INVALID VALUE: a numeric argument is out of range.The offending command is ignored and has no other side effect than to set the error flag.";
				break;
			}
		case GL_INVALID_OPERATION:
			{
				message = "INVALID OPERATION: the specified operation is not allowed in the current state.The offending command is ignored and has no other side effect than to set the error flag.";
				break;
			}
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			{
				message = "INVALID FRAMEBUFFER OPERATION: the command is trying to render to or read from the framebuffer while the currently bound framebuffer is not framebuffer complete(i.e.the return value from glCheckFramebufferStatus is not GL_FRAMEBUFFER_COMPLETE).The offending command is ignored and has no other side effect than to set the error flag.";
				break;
			}
		case GL_OUT_OF_MEMORY: 
			{
				message = "OUT OF MEMORY: there is not enough memory left to execute the command.The state of the GL is undefined, except for the state of the error flags, after this error is recorded.";
				break;
			}
		default:
			{
				message = "Unknown error occurred!";
				break;
			}
		}
		fprintf(stderr, "GLES error: %s\n", message);
		assert(false);
	}
#endif
}

#endif
