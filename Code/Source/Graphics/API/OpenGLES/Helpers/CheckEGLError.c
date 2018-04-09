#include "CheckEGLError.h"

#include <errno.h>
#include <stdio.h>

#if defined(GFX_API_OPENGLES)

void CheckEGLError()
{
#if defined(_DEBUG)
	const EGLint errorCode = eglGetError();
	if (EGL_SUCCESS != errorCode)
	{
		char *message = "";
		switch (errorCode)
		{
		case EGL_NOT_INITIALIZED:
			{
				message = "EGL_NOT_INITIALIZED";
				break;
			}
		case EGL_BAD_ACCESS:
			{
				message = "EGL_BAD_ACCESS";
				break;
			}
		case EGL_BAD_ALLOC:
			{
				message = "EGL_BAD_ALLOC";
				break;
			}
		case EGL_BAD_ATTRIBUTE:
			{
				message = "EGL_BAD_ATTRIBUTE";
				break;
			}
		case EGL_BAD_CONTEXT:
			{
				message = "EGL_BAD_CONTEXT";
				break;
			}
		case EGL_BAD_CONFIG:
			{
				message = "EGL_BAD_CONFIG";
				break;
			}
		case EGL_BAD_CURRENT_SURFACE:
			{
				message = "EGL_BAD_CURRENT_SURFACE";
				break;
			}
		case EGL_BAD_DISPLAY:
			{
				message = "EGL_BAD_DISPLAY";
				break;
			}
		case EGL_BAD_SURFACE:
			{
				message = "EGL_BAD_SURFACE";
				break;
			}
		case EGL_BAD_MATCH:
			{
				message = "EGL_BAD_MATCH";
				break;
			}
		case EGL_BAD_PARAMETER:
			{
				message = "EGL_BAD_PARAMETER";
				break;
			}
		case EGL_BAD_NATIVE_PIXMAP:
			{
				message = "EGL_BAD_NATIVE_PIXMAP";
				break;
			}
		case EGL_BAD_NATIVE_WINDOW:
			{
				message = "EGL_BAD_NATIVE_WINDOW";
				break;
			}
		case EGL_CONTEXT_LOST:
			{
				message = "EGL_CONTEXT_LOST";
				break;
			}
		default:
			{
				message = "Unknown error occurred!";
				break;
			}
		}
		fprintf(stderr, "GLES error: %s\n", message);
	}
#endif
}

#endif