#include "Graphics/API/GFX.h"

#include "Graphics/API/Helpers/DataTypeByteSize.h"
#include "Graphics/API/Helpers/TransposeData.h"
#include "Graphics/API/OpenGLES/OpenGLESAPI.h"
#include "Graphics/API/OpenGLES/OpenGLESStructs.h"
#include "Graphics/API/OpenGLES/OpenGLESTranslators.h"
#include "Graphics/API/OpenGLES/Helpers/CheckEGLError.h"
#include "Graphics/API/OpenGLES/Helpers/CheckGLESError.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(PROTO_PLATFORM_RASPBERRY_PI)
#include "bcm_host.h"
#endif

#if defined(GFX_API_OPENGLES)

#define BUFFER_OFFSET(a_Offset) ((char*)0 + (a_Offset))

GFXAPI g_API = 0;

void CheckShaderInfoLog(GLuint a_Shader)
{
	GLint maxLength = 0;
	glGetShaderiv(a_Shader, GL_INFO_LOG_LENGTH, &maxLength);
	if (maxLength > 1)
	{
		char *infoLog = malloc(maxLength);
		glGetShaderInfoLog(a_Shader, maxLength, &maxLength, &infoLog[0]);
		fprintf(stderr, "Shader compile log: %s\n", infoLog);
		free(infoLog);
	}
}

void CheckProgramInfoLog(GLuint a_Program)
{
	GLint maxLength = 0;
	glGetProgramiv(a_Program, GL_INFO_LOG_LENGTH, &maxLength);
	char *infoLog = malloc(maxLength);
	glGetProgramInfoLog(a_Program, maxLength, NULL, infoLog);
	fprintf(stderr, "Shader program link error: %s\n", infoLog);
	free(infoLog);
}

bool EqualViewports(OpenGLESViewport *a_CurrentViewport, OpenGLESViewport *a_RequestedViewport)
{
	return a_CurrentViewport->m_X == a_RequestedViewport->m_X &&
		a_CurrentViewport->m_Y == a_RequestedViewport->m_Y &&
		a_CurrentViewport->m_Width == a_RequestedViewport->m_Width &&
		a_CurrentViewport->m_Height == a_RequestedViewport->m_Height;
}

void GFXGetBaseAPIName(char *a_ApiName)
{
	sprintf_s(a_ApiName, 16, "OpenGL ES 2.0\0");
}

char* GFXGetBaseAPICode()
{
	return "opengles";
}

void GFXInitialize(GFXAPI *a_API, Allocator *a_Allocator, GFXAPIDescriptor *a_Descriptor)
{
	(void)a_Allocator;
	OpenGLESAPI *api = ALLOCATE(OpenGLESAPI);
	assert(0 != api);

#if defined(PROTO_PLATFORM_WIN32)

	HDC hdc = GetDC(a_Descriptor->m_WindowHandle);
	api->m_Display = eglGetDisplay(hdc);
#elif defined(PROTO_PLATFORM_RASPBERRY_PI)
	bcm_host_init();
	api->m_Display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
#endif
	CheckEGLError();
	assert(EGL_NO_DISPLAY != api->m_Display);
	EGLint eglVersionMajor;
	EGLint eglVersionMinor;
	EGLBoolean success = eglInitialize(api->m_Display, &eglVersionMajor, &eglVersionMinor);
	CheckEGLError();
	assert(EGL_TRUE == success);

	EGLint configAttributes[] =
	{
		// EGL_BUFFER_SIZE, 0,
		EGL_RED_SIZE, 5,
		EGL_GREEN_SIZE, 6,
		EGL_BLUE_SIZE, 5,
		EGL_ALPHA_SIZE, EGL_DONT_CARE,
		// EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER,
		EGL_DEPTH_SIZE, EGL_DONT_CARE,
		// EGL_LEVEL, 0,
		// EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_SAMPLE_BUFFERS, EGL_DONT_CARE,
		// EGL_SAMPLES, 0,
		EGL_STENCIL_SIZE, EGL_DONT_CARE,
		//EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		// EGL_TRANSPARENT_TYPE, EGL_NONE,
		// EGL_TRANSPARENT_RED_VALUE, EGL_DONT_CARE,
		// EGL_TRANSPARENT_GREEN_VALUE, EGL_DONT_CARE,
		// EGL_TRANSPARENT_BLUE_VALUE, EGL_DONT_CARE,
		// EGL_CONFIG_CAVEAT, EGL_DONT_CARE,
		// EGL_CONFIG_ID, EGL_DONT_CARE,
		// EGL_MAX_SWAP_INTERVAL, EGL_DONT_CARE,
		// EGL_MIN_SWAP_INTERVAL, EGL_DONT_CARE,
		// EGL_NATIVE_RENDERABLE, EGL_DONT_CARE,
		// EGL_NATIVE_VISUAL_TYPE, EGL_DONT_CARE,
		EGL_NONE
	};

	EGLint numConfigs;
	EGLConfig windowConfig;
	success = eglChooseConfig(api->m_Display, configAttributes, &windowConfig, 1, &numConfigs);
	CheckEGLError();
	assert(EGL_TRUE == success);

	success = eglBindAPI(EGL_OPENGL_ES_API);
	CheckEGLError();
	assert(EGL_TRUE == success);

	EGLint contextAttributes[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };
	api->m_Context = eglCreateContext(api->m_Display, windowConfig, EGL_NO_CONTEXT, contextAttributes);
	CheckEGLError();
	assert(EGL_NO_CONTEXT != api->m_Context);

#if defined(PROTO_PLATFORM_WIN32)

#elif defined(PROTO_PLATFORM_RASPBERRY_PI)
	VC_RECT_T destRect = {
		.x = 0,
		.y = 0,
		.width = a_Descriptor->m_FrameBufferWidth,
		.height = a_Descriptor->m_FrameBufferHeight
	};

	VC_RECT_T srcRect = { 0 };

	DISPMANX_DISPLAY_HANDLE_T dispmanDisplayHandle = vc_dispmanx_display_open(0);
	DISPMANX_UPDATE_HANDLE_T dispmanUpdateHandle = vc_dispmanx_update_start(0);
	api->m_DisplayElement.element = vc_dispmanx_element_add(
		dispmanUpdateHandle,
		dispmanDisplayHandle,
		0/*layer*/,
		&destRect,
		0/*source*/,
		&srcRect,
		DISPMANX_PROTECTION_NONE, 
		0 /*alpha value*/,
		0/*clamp*/,
		(DISPMANX_TRANSFORM_T) 0/*transform*/);

	api->m_DisplayElement.width = a_Descriptor->m_FrameBufferWidth;
	api->m_DisplayElement.height = a_Descriptor->m_FrameBufferHeight;
	vc_dispmanx_update_submit_sync(dispmanUpdateHandle);
# endif
	
#if defined(PROTO_PLATFORM_WIN32)
	EGLint surfaceAttributes[] = { EGL_NONE };
	api->m_Surface = eglCreateWindowSurface(api->m_Display, windowConfig, a_Descriptor->m_WindowHandle, surfaceAttributes);
	CheckEGLError();
	assert(EGL_NO_SURFACE != api->m_Surface);
#elif defined(PROTO_PLATFORM_RASPBERRY_PI)
	api->m_Surface = eglCreateWindowSurface(api->m_Display, windowConfig, &(api->m_DisplayElement.element), NULL);
	assert(api->m_Surface != EGL_NO_SURFACE);
#endif
	success = eglMakeCurrent(api->m_Display, api->m_Surface, api->m_Surface, api->m_Context);
	CheckEGLError();
	assert(EGL_TRUE == success);

	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &api->m_Parameters.MAX_VERTEX_ATTRIBUTES); CheckGLESError();
	api->m_Parameters.m_GLESVersion = glGetString(GL_VERSION); CheckGLESError();
	api->m_Parameters.m_GLSLVersion = glGetString(GL_SHADING_LANGUAGE_VERSION); CheckGLESError();
	api->m_Parameters.m_EGLVersionMajor = eglVersionMajor;
	api->m_Parameters.m_EGLVersionMinor = eglVersionMinor;
	memset(&api->m_CurrentViewport, 0, sizeof(OpenGLESViewport));

	g_API = api;
	*a_API = api;
	
	glEnable(GL_DEPTH_TEST); CheckGLESError();
	glDepthFunc(GL_LEQUAL); CheckGLESError();
}

void GFXTerminate(GFXAPI a_API)
{
	assert(0 != a_API);
	OpenGLESAPI *api = a_API;
	EGLBoolean success = eglDestroyContext(api->m_Display, api->m_Context);
#if !defined(NDEBUG)
	assert(success);
#else
	GFX_UNUSED(success);
#endif
	CheckEGLError();
	DEALLOCATE(a_API);
}

void GFXCreateViewport(GFXAPI a_API, GFXViewportDescriptor *a_Descriptor, GFXViewportHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	OpenGLESViewport *viewport = ALLOCATE(OpenGLESViewport);
	assert(0 != viewport);
	viewport->m_X = a_Descriptor->m_X;
	viewport->m_Y = a_Descriptor->m_Y;
	viewport->m_Width = a_Descriptor->m_Width;
	viewport->m_Height = a_Descriptor->m_Height;
	*a_Handle = viewport;
}

void GFXDestroyViewport(GFXAPI a_API, GFXViewportHandle a_Handle)
{
	GFX_UNUSED(a_API);
	if (NULL != a_Handle)
	{
		OpenGLESViewport *viewport = a_Handle;
		DEALLOCATE(viewport);
	}
}

void GFXCreateScissorRect(GFXAPI a_API, GFXScissorRectDescriptor *a_Descriptor, GFXScissorRectHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	OpenGLESScissorRect *scissorRect = ALLOCATE(OpenGLESScissorRect);
	assert(0 != scissorRect);
	scissorRect->m_X = a_Descriptor->m_X;
	scissorRect->m_Y = a_Descriptor->m_Y;
	scissorRect->m_Width = a_Descriptor->m_Width;
	scissorRect->m_Height = a_Descriptor->m_Height;
	*a_Handle = scissorRect;
}
void GFXDestroyScissorRect(GFXAPI a_API, GFXScissorRectHandle a_Handle)
{
	GFX_UNUSED(a_API);
	if (NULL != a_Handle)
	{
		OpenGLESScissorRect *scissorRect = a_Handle;
		DEALLOCATE(scissorRect);
	}
}

void GFXCreateSwapChain(GFXAPI a_API, GFXSwapChainDescriptor *a_Descriptor, GFXSwapChainHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	OpenGLESSwapChain *swapChain = ALLOCATE(OpenGLESSwapChain);
	*a_Handle = swapChain;
}

void GFXDestroySwapChain(GFXAPI a_API, GFXSwapChainHandle a_Handle)
{
	GFX_UNUSED(a_API);
	if (NULL != a_Handle)
	{
		OpenGLESSwapChain *swapChain = (OpenGLESSwapChain*)a_Handle;
		DEALLOCATE(swapChain);
	}
}

void GFXCreateRenderTarget(GFXAPI a_API, GFXRenderTargetDescriptor *a_Descriptor, GFXRenderTargetHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	OpenGLESRenderTarget *renderTarget = ALLOCATE(OpenGLESRenderTarget);
	renderTarget->m_ReadyForDraw = false;
	renderTarget->m_ReadyForPresent = false;
	*a_Handle = renderTarget;
}

void GFXDestroyRenderTarget(GFXAPI a_API, GFXRenderTargetHandle a_Handle)
{
	GFX_UNUSED(a_API);
	if (NULL != a_Handle)
	{
		OpenGLESRenderTarget *renderTarget = (OpenGLESRenderTarget*)a_Handle;
		DEALLOCATE(renderTarget);
	}
}

void GFXCreateDepthStencilState(GFXAPI a_API, GFXDepthStencilStateDescriptor *a_Descriptor, GFXDepthStencilStateHandle *a_Handle)
{
	assert(false);
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXDestroyDepthStencilState(GFXAPI a_API, GFXDepthStencilStateHandle a_Handle)
{
	assert(false);
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXCreateRasterizerState(GFXAPI a_API, GFXRasterizerStateDescriptor *a_Descriptor, GFXRasterizerStateHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	OpenGLESRasterizerState *rasterizerState = ALLOCATE(OpenGLESRasterizerState);
	rasterizerState->m_CullFace = GL_BACK;
	rasterizerState->m_FrontFaceCulling = GL_CW;

	// 	rasterizerState->m_BackEnd.DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
	// 	rasterizerState->m_BackEnd.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
	// 	rasterizerState->m_BackEnd.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
	// 	rasterizerState->m_BackEnd.DepthClipEnable = TRUE;
	// 	rasterizerState->m_BackEnd.MultisampleEnable = FALSE;
	// 	rasterizerState->m_BackEnd.AntialiasedLineEnable = FALSE;
	// 	rasterizerState->m_BackEnd.ForcedSampleCount = 0;
	// 	rasterizerState->m_BackEnd.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

	*a_Handle = rasterizerState;
}

void GFXDestroyRasterizerState(GFXAPI a_API, GFXRasterizerStateHandle a_Handle)
{
	GFX_UNUSED(a_API);
	if (NULL != a_Handle)
	{
		OpenGLESRasterizerState *rasterizerState = (OpenGLESRasterizerState*)a_Handle;
		DEALLOCATE(rasterizerState);
	}
}

void GFXCreateBlendState(GFXAPI a_API, GFXBlendStateDescriptor *a_Descriptor, GFXBlendStateHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	OpenGLESBlendState *blendState = ALLOCATE(OpenGLESBlendState);
	*a_Handle = blendState;
}

void GFXDestroyBlendState(GFXAPI a_API, GFXBlendStateHandle a_Handle)
{
	GFX_UNUSED(a_API);
	if (NULL != a_Handle)
	{
		OpenGLESBlendState *blendState = (OpenGLESBlendState*)a_Handle;
		DEALLOCATE(blendState);
	}
}

void GFXPresent(GFXAPI a_API, GFXSwapChainHandle a_Handle)
{
	GFX_UNUSED(a_Handle);
	assert(0 != a_API);
	OpenGLESAPI *api = a_API;
	eglSwapBuffers(api->m_Display, api->m_Surface); CheckEGLError();
}

void GFXCreateVertexBuffer(GFXAPI a_API, GFXVertexBufferDescriptor *a_Descriptor, GFXVertexBufferHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);

	OpenGLESVertexBuffer *vertexBuffer = ALLOCATE(OpenGLESVertexBuffer);
	glGenBuffers(1, &vertexBuffer->m_BufferID); CheckGLESError();
	assert(0 != vertexBuffer->m_BufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->m_BufferID); CheckGLESError();
	const GLenum vertexBufferUsage = TranslateUsage(a_Descriptor->m_Usage);
	glBufferData(GL_ARRAY_BUFFER, a_Descriptor->m_DataByteSize, a_Descriptor->m_Vertices, vertexBufferUsage); CheckGLESError();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	*a_Handle = vertexBuffer;
}

void GFXUpdateVertexBuffer(GFXAPI a_API, GFXVertexBufferDescriptor *a_Descriptor, GFXVertexBufferHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_Descriptor);
	OpenGLESVertexBuffer *vertexBuffer = a_Handle;
	assert(0 != vertexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->m_BufferID);
	glBufferSubData(GL_ARRAY_BUFFER, a_Descriptor->m_ByteOffset, a_Descriptor->m_DataByteSize, a_Descriptor->m_Vertices);
}

void GFXDestroyVertexBuffer(GFXAPI a_API, GFXVertexBufferHandle a_Handle)
{
	GFX_UNUSED(a_API);
	OpenGLESVertexBuffer *vertexBuffer = a_Handle;
	assert(0 != vertexBuffer->m_BufferID);
	glDeleteBuffers(1, &vertexBuffer->m_BufferID); CheckGLESError();
	DEALLOCATE(vertexBuffer);
}

void GFXCreateIndexBuffer(GFXAPI a_API, GFXIndexBufferDescriptor *a_Descriptor, GFXIndexBufferHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_API);
	assert(0 != a_Descriptor->m_Indices);
	OpenGLESIndexBuffer *indexBuffer = ALLOCATE(OpenGLESIndexBuffer);
	glGenBuffers(1, &indexBuffer->m_BufferID); CheckGLESError();
	assert(0 != indexBuffer->m_BufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->m_BufferID); CheckGLESError();
	const GLenum indexBufferUsage = TranslateUsage(a_Descriptor->m_Usage);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_Descriptor->m_DataByteSize, a_Descriptor->m_Indices, indexBufferUsage); CheckGLESError();
	*a_Handle = indexBuffer;
}

void GFXDestroyIndexBuffer(GFXAPI a_API, GFXIndexBufferHandle a_Handle)
{
	GFX_UNUSED(a_API);
	if (NULL != a_Handle)
	{
		OpenGLESIndexBuffer *indexBuffer = a_Handle;
		assert(0 != indexBuffer->m_BufferID);
		glDeleteBuffers(1, &indexBuffer->m_BufferID); CheckGLESError();
		DEALLOCATE(indexBuffer);
	}
}

void GFXCreateTexture(GFXAPI a_API, GFXTextureDescriptor *a_Descriptor, GFXTextureHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_API);
	OpenGLESTexture *texture = ALLOCATE(OpenGLESTexture);
	glGenTextures(1, &texture->m_TextureID); CheckGLESError();
	glBindTexture(GL_TEXTURE_2D, texture->m_TextureID); CheckGLESError();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); CheckGLESError();	// parameterize in descriptor
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); CheckGLESError();	// parameterize in descriptor
	GLenum format = TranslateTextureFormat(a_Descriptor->m_Format);
	glTexImage2D(GL_TEXTURE_2D, 0, format, a_Descriptor->m_Width, a_Descriptor->m_Height, 0, format, GL_UNSIGNED_BYTE, a_Descriptor->m_Data); CheckGLESError();
	*a_Handle = texture;
	glBindTexture(GL_TEXTURE_2D, 0); CheckGLESError();
}

void GFXDestroyTexture(GFXAPI a_API, GFXTextureHandle a_Handle)
{
	GFX_UNUSED(a_API);
	if (NULL != a_Handle)
	{
		OpenGLESTexture *texture = a_Handle;
		DEALLOCATE(texture);
	}
}

void GFXCreateSamplerState(GFXAPI a_API, GFXSamplerStateDescriptor *a_Descriptor, GFXSamplerStateHandle *a_Handle)
{
	assert(false);
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXDestroySamplerState(GFXAPI a_API, GFXSamplerStateHandle a_Handle)
{
	assert(false);
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXCreateShader(GFXAPI a_API, GFXShaderDescriptor *a_Descriptor, GFXShaderHandle *a_Handle)
{
	GFX_UNUSED(a_API);

	const GLenum shaderType = TranslateShaderType(a_Descriptor->m_Type);
	GLuint shaderID = glCreateShader(shaderType);
	assert(0 != shaderID);

	glShaderSource(shaderID, 1, &a_Descriptor->m_Source, NULL);
	glCompileShader(shaderID);
	CheckShaderInfoLog(shaderID);

	GLint compiled;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);
	if (GL_FALSE == compiled)
	{
		glDeleteShader(shaderID);
		assert(false);
	}

	OpenGLESShader *shader = ALLOCATE(OpenGLESShader);
	shader->m_BackEnd = shaderID;
	shader->m_Type = a_Descriptor->m_Type;
	*a_Handle = shader;
}

void GFXDestroyShader(GFXAPI a_API, GFXShaderHandle a_Handle)
{
	GFX_UNUSED(a_API);
	if (NULL != a_Handle)
	{
		OpenGLESShader *shader = a_Handle;
		DEALLOCATE(shader);
	}
}

void GFXCreateConstantBuffer(GFXAPI a_API, GFXConstantBufferDescriptor *a_Descriptor, GFXConstantBufferHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	OpenGLESConstantBuffer *constantBuffer = ALLOCATE(OpenGLESConstantBuffer);
	*a_Handle = constantBuffer;
}

void GFXCreateResource(GFXAPI a_API, GFXResourceDescriptor *a_Descriptor, GFXResourceHandle *a_Handle);
void GFXDestroyResource(GFXAPI a_API, GFXResourceHandle a_Handle);

void GFXDrawInstanced(GFXAPI a_API, GFXCommandListHandle a_CommandList, GFXInstancedDrawDescriptor a_Descriptor)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_CommandList);
	GFX_UNUSED(a_Descriptor);

#if 1
	OpenGLESAPI *api = (OpenGLESAPI*)a_API;
	OpenGLESCommandList *commandList = (OpenGLESCommandList*)a_CommandList;
	OpenGLESPipelineStateObject *pipelineStateObject = commandList->m_PipelineStateObject;
	OpenGLESViewport *viewport = pipelineStateObject->m_Viewport;
	if (!EqualViewports(&api->m_CurrentViewport, viewport))
	{
		glViewport(viewport->m_X, viewport->m_Y, viewport->m_Width, viewport->m_Height); CheckGLESError();
		api->m_CurrentViewport = *viewport;
	}

	glUseProgram(pipelineStateObject->m_ShaderProgram); CheckGLESError();

	OpenGLESVertexBuffer *vertexBuffer = (OpenGLESVertexBuffer*)a_Descriptor.m_VertexBuffer;
	glBindBuffer(GL_ARRAY_BUFFER,  vertexBuffer->m_BufferID); CheckGLESError();

// 	OpenGLESInputLayout *inputLayout = pipelineStateObject->m_InputLayout;
// 	for (i = 0; i < inputLayout->m_NumElements; ++i)
// 	{
// 		OpenGLESInputLayoutElement *element = &inputLayout->m_Elements[i];
// 		glEnableVertexAttribArray(element->m_Index); CheckGLESError();
// 		glVertexAttribPointer(element->m_Index, element->m_Size, element->m_Type, element->m_Normalized, element->m_Stride, BUFFER_OFFSET(element->m_Offset)); CheckGLESError();
// 	}
// 

	const GLsizei stride = 7 * sizeof(float);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(0)); CheckGLESError();
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, BUFFER_OFFSET(3 * sizeof(float))); CheckGLESError();
	glEnableVertexAttribArray(0); CheckGLESError();
	glEnableVertexAttribArray(1); CheckGLESError();

	OpenGLESIndexBuffer *indexBuffer = NULL;
	if (NULL != indexBuffer)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->m_BufferID); CheckGLESError();
		GLenum renderMode = pipelineStateObject->m_RenderMode;
		GLsizei count = 0;
		GLvoid *indices = NULL;
		glDrawElements(renderMode, count, GL_UNSIGNED_INT, indices); CheckGLESError();
	}
	else
	{
		GLenum renderMode = pipelineStateObject->m_RenderMode;
		GLint first = 0;
		GLsizei count = 3;
		glDrawArrays(renderMode, first, count); CheckGLESError();
	}
#else
	// 	OpenGLESCommandList *commandList = a_Handle;
	// 
	// 
	// 	OpenGLESPipelineStateObject *pipelineStateObject = commandList->m_PipelineStateObject;
	// 	uint32_t i;
	// 	for (i = 0; i < commandList->m_NumConstantBuffers; ++i)
	// 	{
	// 		OpenGLESConstantBuffer *constantBuffer = commandList->m_ConstantBuffers[i];
	// 		uint32_t elementIndex = 0;
	// 		for (elementIndex = 0; elementIndex < constantBuffer->m_NumElements; ++elementIndex)
	// 		{
	// 			OpenGLESConstantBufferElement *element = &constantBuffer->m_Elements[elementIndex];
	// 			const GLint uniformLocation = glGetUniformLocation(pipelineStateObject->m_ShaderProgram, element->m_Name); CheckGLESError();
	// 			assert(-1 != uniformLocation);
	// 			glUniformMatrix4fv(uniformLocation, 1, false, (float*)(&constantBuffer->m_Data[element->m_Offset])); CheckGLESError();
	// 		}
	// 	}
	// 
	// 	if (0 != commandList->m_DiffuseTexture)
	// 	{
	// 		glBindTexture(GL_TEXTURE_2D, commandList->m_DiffuseTexture->m_TextureID); CheckGLESError();
	// 		const GLint diffuseTextureUniform =  glGetUniformLocation(pipelineStateObject->m_ShaderProgram, "u_DiffuseSampler"); CheckGLESError();
	// 		glUniform1i(diffuseTextureUniform, 0); CheckGLESError();
	// 	}
	// 
	// 	glBindBuffer(GL_ARRAY_BUFFER, commandList->m_VertexBuffer); CheckGLESError();
	// 
	// 	OpenGLESInputLayout *inputLayout = pipelineStateObject->m_InputLayout;
	// 	for (i = 0; i < inputLayout->m_NumElements; ++i)
	// 	{
	// 		OpenGLESInputLayoutElement *element = &inputLayout->m_Elements[i];
	// 		glEnableVertexAttribArray(element->m_Index); CheckGLESError();
	// 		glVertexAttribPointer(element->m_Index, element->m_Size, element->m_Type, element->m_Normalized, element->m_Stride, BUFFER_OFFSET(element->m_Offset)); CheckGLESError();
	// 	}
	// 
	// 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, commandList->m_IndexBuffer); CheckGLESError();
	// 	glDrawElements(commandList->m_RenderMode, a_NumVertices, GL_UNSIGNED_INT, 0); CheckGLESError();
	// #endif
#endif
}

void GFXWriteConstantBufferData(GFXAPI a_API, GFXCommandListHandle a_CommandListHandle, GFXConstantBufferHandle a_ConstantBufferHandle, const void *a_Data, size_t a_ByteSize)
{
	GFX_UNUSED(a_ByteSize);
	GFX_UNUSED(a_Data);
	GFX_UNUSED(a_ConstantBufferHandle);
	GFX_UNUSED(a_CommandListHandle);
	GFX_UNUSED(a_API);
}

void GFXDestroyConstantBuffer(GFXAPI a_API, GFXConstantBufferHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXCreateCommandQueue(GFXAPI a_API, GFXCommandQueueDescriptor *a_Descriptor, GFXCommandQueueHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	OpenGLESCommandQueue *commandQueue = ALLOCATE(OpenGLESCommandQueue);
	*a_Handle = commandQueue;
}

void GFXWaitForCommandQueueCompletion(GFXAPI a_API, GFXCommandQueueHandle a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXDestroyCommandQueue(GFXAPI a_API, GFXCommandQueueHandle a_Handle)
{
	GFX_UNUSED(a_API);
	if (NULL != a_Handle)
	{
		OpenGLESCommandQueue *commandQueue = (OpenGLESCommandQueue*)a_Handle;
		DEALLOCATE(commandQueue);
	}
}

void GFXCreateCommandList(GFXAPI a_API, GFXCommandListDescriptor *a_Descriptor, GFXCommandListHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_Descriptor);
	OpenGLESCommandList *commandList = ALLOCATE(OpenGLESCommandList);
	memset(commandList, 0, sizeof(OpenGLESCommandList));
	commandList->m_PipelineStateObject = a_Descriptor->m_PipelineStateObject;
	commandList->m_Recording = false;
	*a_Handle = commandList;
}

void GFXStartRecordingCommandList(GFXAPI a_API, GFXCommandListHandle a_CommandListHandle, GFXPipelineStateObjectHandle a_PipelineStateObjectHandle)
{
	GFX_UNUSED(a_PipelineStateObjectHandle);
	GFX_UNUSED(a_API);
	OpenGLESCommandList *commandList = (OpenGLESCommandList*)a_CommandListHandle;
	commandList->m_Recording = true;
}

void GFXStopRecordingCommandList(GFXAPI a_API, GFXCommandListHandle a_Handle)
{
	GFX_UNUSED(a_API);
	OpenGLESCommandList *commandList = (OpenGLESCommandList*)a_Handle;
	commandList->m_Recording = false;
}

void GFXExecuteCommandList(GFXAPI a_API, GFXCommandListHandle a_CommandListHandle, GFXCommandQueueHandle a_CommandQueueHandle)
{
	GFX_UNUSED(a_CommandQueueHandle);
	GFX_UNUSED(a_API);
	OpenGLESCommandList *commandList = (OpenGLESCommandList*)a_CommandListHandle;
	assert(false == commandList->m_Recording);
}

void GFXDestroyCommandList(GFXAPI a_API, GFXCommandListHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_API);
	if (0 != a_Handle)
	{
		OpenGLESCommandList *commandList = a_Handle;
		DEALLOCATE(commandList);
	}
}

void GFXCreatePipelineStateObject(GFXAPI a_API, GFXPipelineStateObjectDescriptor *a_Descriptor, GFXPipelineStateObjectHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GLuint shaderProgram = glCreateProgram();
	assert(0 != shaderProgram);

	OpenGLESShader *vertexShader = a_Descriptor->m_VertexShader;
	glAttachShader(shaderProgram, vertexShader->m_BackEnd);
	OpenGLESShader *fragmentShader = a_Descriptor->m_PixelShader;
	glAttachShader(shaderProgram, fragmentShader->m_BackEnd);

	glBindAttribLocation(shaderProgram, 0, "vPosition"); CheckGLESError();

	glLinkProgram(shaderProgram);
	GLint linked;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);
	if (GL_FALSE == linked)
	{
		CheckProgramInfoLog(shaderProgram);
		assert(false);

		glDeleteProgram(shaderProgram);
		assert(false);
	}

	glValidateProgram(shaderProgram);
	GLint validated;
	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &validated);
	if (GL_FALSE == validated)
	{
		CheckProgramInfoLog(shaderProgram);
		assert(false);

		glDeleteProgram(shaderProgram);
		assert(false);
	}

	GLsizei numAttachedShaders;
	GLuint attachedShaders[MAX_SHADERS_PER_PROGRAM];
	glGetAttachedShaders(shaderProgram, MAX_SHADERS_PER_PROGRAM, &numAttachedShaders, attachedShaders);
	int i = 0;
	for (i = 0; i < numAttachedShaders; ++i)
	{
		glDetachShader(shaderProgram, attachedShaders[i]);
		glDeleteShader(attachedShaders[i]);
	}

	OpenGLESInputLayout *inputLayout = ALLOCATE(OpenGLESInputLayout);
	// TODO: shader inspection

	OpenGLESPipelineStateObject *pipelineStateObject = ALLOCATE(OpenGLESPipelineStateObject);
	pipelineStateObject->m_ShaderProgram = shaderProgram;

	pipelineStateObject->m_ClearMask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
	pipelineStateObject->m_BlendState = a_Descriptor->m_BlendState;
	pipelineStateObject->m_RasterizerState = (OpenGLESRasterizerState*)a_Descriptor->m_RasterizerState;
	pipelineStateObject->m_Viewport = a_Descriptor->m_Viewport;
	pipelineStateObject->m_ScissorRect = a_Descriptor->m_ScissorRect;
	pipelineStateObject->m_InputLayout = inputLayout;
	pipelineStateObject->m_RenderMode = TranslateRenderMode(a_Descriptor->m_RenderMode);

	*a_Handle = pipelineStateObject;
}

void GFXSetPipelineStateObject(GFXAPI a_API, GFXPipelineStateObjectHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_Handle);
	OpenGLESPipelineStateObject *pipelineStateObject = a_Handle;
	assert(0 != pipelineStateObject->m_ShaderProgram);
	glUseProgram(pipelineStateObject->m_ShaderProgram);

#if !defined(NDEBUG)
	GLint programID = 0;
	glGetIntegerv(GL_CURRENT_PROGRAM, &programID);
	assert(0 != programID);
#endif
}

void GFXDestroyPipelineStateObject(GFXAPI a_API, GFXPipelineStateObjectHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_API);
	OpenGLESPipelineStateObject *pipelineStateObject = a_Handle;
	DEALLOCATE(pipelineStateObject);
}
void GFXPrepareRenderTargetForDraw(GFXAPI a_API, GFXCommandListHandle a_CommandListHandle, GFXRenderTargetHandle a_RenderTargetHandle)
{
	GFX_UNUSED(a_CommandListHandle);
	GFX_UNUSED(a_API);
	OpenGLESRenderTarget *renderTarget = (OpenGLESRenderTarget*)a_RenderTargetHandle;
	renderTarget->m_ReadyForDraw = true;
	renderTarget->m_ReadyForPresent = false;
}

void GFXClearRenderTarget(GFXAPI a_API, GFXCommandListHandle a_CommandListHandle, GFXRenderTargetHandle a_RenderTargetHandle, const GFXColor a_ClearColor)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_RenderTargetHandle);
	OpenGLESCommandList *commandList = (OpenGLESCommandList*)a_CommandListHandle;
	glClearColor(a_ClearColor.m_R, a_ClearColor.m_G, a_ClearColor.m_B, a_ClearColor.m_A);
	glClear(commandList->m_PipelineStateObject->m_ClearMask);
}

void GFXPrepareRenderTargetForPresent(GFXAPI a_API, GFXCommandListHandle a_CommandListHandle, GFXRenderTargetHandle a_RenderTargetHandle)
{
	GFX_UNUSED(a_CommandListHandle);
	GFX_UNUSED(a_API);
	OpenGLESRenderTarget *renderTarget = (OpenGLESRenderTarget*)a_RenderTargetHandle;
	renderTarget->m_ReadyForDraw = false;
	renderTarget->m_ReadyForPresent = true;
}


// 
// 
// void GFXCreateRasterizerState(GFXAPI a_API, GFXRasterizerStateDescriptor *a_Descriptor, GFXRasterizerStateHandle *a_Handle)
// {
// 	GFX_UNUSED(a_API);
// 	GFX_UNUSED(a_Descriptor);
// 	GFX_UNUSED(a_Handle);
// }
// void GFXDestroyRasterizerState(GFXAPI a_API, GFXRasterizerStateHandle a_Handle)
// {
// 	GFX_UNUSED(a_API);
// 	GFX_UNUSED(a_Handle);
// }
// 
// void GFXCreateBlendState(GFXAPI a_API, GFXBlendStateDescriptor *a_Descriptor, GFXBlendStateHandle *a_Handle)
// {
// 	GFX_UNUSED(a_API);
// 	GFX_UNUSED(a_Descriptor);
// 	GFX_UNUSED(a_Handle);
// }
// 
// void GFXDestroyBlendState(GFXAPI a_API, GFXBlendStateHandle a_Handle)
// {
// 	GFX_UNUSED(a_API);
// 	GFX_UNUSED(a_Handle);
// }
// 
// void GFXClearRenderTarget(GFXAPI a_API, GFXRenderTargetHandle a_RenderTarget, GFXColor a_ClearColor)
// {
// 	assert(0 != a_API);
// 	OpenGLESAPI *api = a_API;
// 	GFX_UNUSED(a_RenderTarget);
// 	glClearColor(a_ClearColor.m_R, a_ClearColor.m_G, a_ClearColor.m_B, a_ClearColor.m_A); CheckGLESError();
// 	glClear(api->m_ClearMask); CheckGLESError();
// }
// 
// void GFXCreateShader(GFXAPI a_API, GFXShaderDescriptor* a_Descriptor, GFXShaderHandle* a_Handle)
// {
// 	GFX_UNUSED(a_API);
// 	assert(0 != a_API);
// 	assert(0 != a_Descriptor);
// 
// 	GLuint shaderProgram = glCreateProgram(); CheckGLESError();
// 	short i;
// 	for (i = 0; i < a_Descriptor->m_NumShaders; ++i)
// 	{
// 		const GLenum shaderType = TranslateShaderType(a_Descriptor->m_Type[i]);
// 		GLuint shader = glCreateShader(shaderType); CheckGLESError();
// 		assert(0 != shader);
// 		
// 		glShaderSource(shader, 1, &a_Descriptor->m_Source[i], NULL); CheckGLESError();
// 		glCompileShader(shader); CheckGLESError();
// 		GLint maxLength = 0;
// 		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength); CheckGLESError();
// 		if (0 != maxLength)
// 		{
// 			char *infoLog = malloc(maxLength);
// 			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]); CheckGLESError();
// 			fprintf(stderr, "Shader compile info: %s\n", infoLog);
// 			free(infoLog);
// 		}
// 
// 		GLint compiled;
// 		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled); CheckGLESError();
// 		if (GL_FALSE == compiled)
// 		{
// 			glDeleteShader(shader); CheckGLESError();
// 			assert(false);
// 		}
// 
// 		glAttachShader(shaderProgram, shader); CheckGLESError();
// 	}
// 
// 	for (i = 0; i < a_Descriptor->m_NumAttributes; ++i)
// 	{
// 		const GFXVertexAttribute attribute = a_Descriptor->m_Attributes[i];
// 		const char *attributeName = TranslateVertexAttribute(attribute);
// 		const GLuint attributeLocation = GetVertexAttributeLocation(attribute);
// 		glBindAttribLocation(shaderProgram, attributeLocation, attributeName); CheckGLESError();
// 	}
// 
// 	glLinkProgram(shaderProgram); CheckGLESError();
// 	GLint linked;
// 	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked); CheckGLESError();
// 	if (GL_FALSE == linked)
// 	{
// 		GLint maxLength = 0;
// 		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength); CheckGLESError();
// 		char *infoLog = malloc(maxLength);
// 		glGetProgramInfoLog(shaderProgram, maxLength, NULL, infoLog); CheckGLESError();
// 		fprintf(stderr, "Shader program link error: %s\n", infoLog);
// 		free(infoLog);
// 
// 		glDeleteProgram(shaderProgram); CheckGLESError();
// 		assert(false);
// 	}
// 
// 	GLsizei numAttachedShaders;
// 	GLuint attachedShaders[MAX_SHADERS_PER_PROGRAM];
// 	glGetAttachedShaders(shaderProgram, MAX_SHADERS_PER_PROGRAM, &numAttachedShaders, attachedShaders); CheckGLESError();
// 	for (i = 0; i < numAttachedShaders; ++i)
// 	{
// 		glDetachShader(shaderProgram, attachedShaders[i]); CheckGLESError();
// 		glDeleteShader(attachedShaders[i]); CheckGLESError();
// 	}
// 
// 	OpenGLESShader *shader = ALLOCATE(OpenGLESShader);
// 	assert(0 != shader);
// 	shader->m_ProgramID = shaderProgram;
// 	*a_Handle = shader;
// }
// 
// void GFXDestroyShader(GFXAPI a_API, GFXShaderHandle a_Handle)
// {
// 	GFX_UNUSED(a_API);
// 	assert(0 != a_API);
// 	OpenGLESShader *shader = a_Handle;
// 	glDeleteProgram(shader->m_ProgramID); CheckGLESError();
// 	DEALLOCATE(shader);
// }
// 
// void GFXCreateInputLayout(GFXAPI a_API, GFXInputLayoutDescriptor *a_Descriptor, GFXInputLayoutHandle *a_Handle)
// {
// 	GFX_UNUSED(a_API);
// 	assert(0 != a_API);
// 	OpenGLESInputLayout *inputLayout = ALLOCATE(OpenGLESInputLayout);
// 	inputLayout->m_NumElements = a_Descriptor->m_NumElements;
// 	inputLayout->m_Elements = (OpenGLESInputLayoutElement*)malloc(sizeof(OpenGLESInputLayoutElement) * a_Descriptor->m_NumElements);
// 	uint32_t offset = 0;
// 	uint32_t i = 0;
// 	for (i = 0; i < a_Descriptor->m_NumElements; ++i)
// 	{
// 		inputLayout->m_Elements[i].m_Index = a_Descriptor->m_Elements[i].m_Index;
// 		inputLayout->m_Elements[i].m_Size = a_Descriptor->m_Elements[i].m_Size;
// 		inputLayout->m_Elements[i].m_Type = TranslateDataType(a_Descriptor->m_Elements[i].m_Type);
// 		inputLayout->m_Elements[i].m_Normalized = a_Descriptor->m_Elements[i].m_Normalized;
// 		inputLayout->m_Elements[i].m_Stride = a_Descriptor->m_Elements[i].m_Stride;
// 		inputLayout->m_Elements[i].m_Offset = offset;
// 		offset += a_Descriptor->m_Elements[i].m_Size * DataTypeByteSize(a_Descriptor->m_Elements[i].m_Type);
// 	}
// 	*a_Handle = inputLayout;
// }
// 
// void GFXDestroyInputLayout(GFXAPI a_API, GFXInputLayoutHandle a_Handle)
// {
// 	GFX_UNUSED(a_API);
// 	OpenGLESInputLayout *inputLayout = a_Handle;
// 	if (0 != inputLayout)
// 	{
// 		DEALLOCATE(inputLayout->m_Elements);
// 		DEALLOCATE(inputLayout);
// 	}
// }
// 
// void GFXCreateConstantBuffer(GFXAPI a_API, GFXConstantBufferDescriptor *a_Descriptor, GFXConstantBufferHandle *a_Handle)
// {
// 	GFX_UNUSED(a_API);
// 	assert(0 != a_API);
// 	OpenGLESConstantBuffer *constantBuffer = ALLOCATE(OpenGLESConstantBuffer);
// 	constantBuffer->m_Data = (char*)malloc(a_Descriptor->m_ByteSize * sizeof(char));
// 	constantBuffer->m_NumElements = a_Descriptor->m_NumElements;
// 	constantBuffer->m_Elements = (OpenGLESConstantBufferElement*)malloc(constantBuffer->m_NumElements * sizeof(OpenGLESConstantBufferElement));
// 
// 	//OpenGLESShader *shader = a_Descriptor->m_Shader;
// 	uint32_t offset = 0;
// 	uint32_t i = 0;
// 	for (i = 0; i < a_Descriptor->m_NumElements; ++i)
// 	{
// 		GFXConstantBufferElementDescriptor *element = &a_Descriptor->m_Elements[i];
// 		const size_t length = strlen(a_Descriptor->m_Elements[i].m_Name) + 1;
// 		constantBuffer->m_Elements[i].m_Name = (char*)malloc(length * sizeof(char));
// 		strcpy_s(constantBuffer->m_Elements[i].m_Name, length, element->m_Name);
// 
// 		const GLint uniformLocation = i;// glGetUniformLocation(shader->m_ProgramID, element->m_Name);
// 		assert(-1 != uniformLocation);
// 		constantBuffer->m_Elements[i].m_UniformLocation = uniformLocation;
// 		constantBuffer->m_Elements[i].m_Size = element->m_Size;
// 		constantBuffer->m_Elements[i].m_Offset = offset;
// 		constantBuffer->m_Elements[i].m_Transpose = element->m_Transpose;
// 		constantBuffer->m_Elements[i].m_Type = element->m_Type;
// 
// 		offset += element->m_Size;
// 	}
// 	assert(0 != constantBuffer->m_Data);
// 	*a_Handle = constantBuffer;
// }
// 
// void GFXCopyConstantBufferData(GFXAPI a_API, GFXConstantBufferHandle a_Handle, const char *a_VariableName, const void *a_Data)
// {
// 	GFX_UNUSED(a_API);
// 	assert(0 != a_API);
// 	assert(0 != a_Data);
// 	bool copied = false;
// 	OpenGLESConstantBuffer *constantBuffer = a_Handle;
// 	uint32_t i = 0;
// 	for (i; i < constantBuffer->m_NumElements; ++i)
// 	{
// 		OpenGLESConstantBufferElement *element = &constantBuffer->m_Elements[i];
// 		if (0 == strcmp(element->m_Name, a_VariableName))
// 		{
// 			if (element->m_Transpose)
// 			{
// 				void *data = malloc(element->m_Size);
// 				TransposeData(a_Data, data, element->m_Size, element->m_Type);
// 				memcpy(&constantBuffer->m_Data[element->m_Offset], data, element->m_Size);
// 				free((void*)data);
// 			}
// 			else
// 			{
// 				memcpy(&constantBuffer->m_Data[element->m_Offset], a_Data, element->m_Size);
// 			}
// 			copied = true;
// 		}
// 	}
// 	assert(copied);
// }
// 
// void GFXDestroyConstantBuffer(GFXAPI a_API, GFXConstantBufferHandle a_Handle)
// {
// 	GFX_UNUSED(a_API);
// 	assert(0 != a_API);
// 	OpenGLESConstantBuffer *constantBuffer = a_Handle;
// 	if (0 != constantBuffer)
// 	{
// 		uint32_t i = 0;
// 		for (i = 0; i < constantBuffer->m_NumElements; ++i)
// 		{
// 			free(constantBuffer->m_Elements[i].m_Name);
// 		}
// 		free(constantBuffer->m_Elements);
// 		free(constantBuffer->m_Data);
// 		DEALLOCATE(constantBuffer);
// 	}
// }
// 
// void GFXCreateResource(GFXAPI a_API, GFXResourceDescriptor *a_Descriptor, GFXResourceHandle *a_Handle)
// {
// 	GFX_UNUSED(a_API);
// 	GFX_UNUSED(a_Descriptor);
// 	OpenGLESResource *resource = ALLOCATE(OpenGLESResource);
// 	*a_Handle = resource;
// }
// 
// void GFXDestroyResource(GFXAPI a_API, GFXResourceHandle a_Handle)
// {
// 	GFX_UNUSED(a_API);
// 	assert(0 != a_API);
// 	OpenGLESResource *resource = a_Handle;
// 	DEALLOCATE(resource);
// }
// 

// 

// 
// 
// bool EqualViewports(OpenGLESViewport *a_CurrentViewport, OpenGLESViewport *a_RequestedViewport)
// {
// 	return a_CurrentViewport->m_X == a_RequestedViewport->m_X &&
// 		a_CurrentViewport->m_Y == a_RequestedViewport->m_Y &&
// 		a_CurrentViewport->m_Width == a_RequestedViewport->m_Width &&
// 		a_CurrentViewport->m_Height == a_RequestedViewport->m_Height;
// }
// 
// void GFXDrawIndexed(GFXAPI a_API, GFXCommandListHandle a_Handle, uint32_t a_NumVertices)
// {
// 	assert(0 != a_API);
// 	assert(0 != a_Handle);
// 	OpenGLESAPI *api = a_API;
// #if 0
// 	GLfloat vVertices[] = { 0.0f,  0.5f, 0.0f,
// 		-0.5f, -0.5f, 0.0f,
// 		0.5f, -0.5f, 0.0f };
// 
// 	// Set the viewport
// 	OpenGLESCommandList *commandList = a_Handle;
// 	glViewport(commandList->m_Viewport->m_X, commandList->m_Viewport->m_Y, commandList->m_Viewport->m_Width, commandList->m_Viewport->m_Height); CheckGLESError();
// 
// 	// Load the vertex data
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
// 	glEnableVertexAttribArray(0);
// 
// 	glDrawArrays(GL_TRIANGLES, 0, 3);
// #else
// 	OpenGLESCommandList *commandList = a_Handle;
// 
// 	if (!EqualViewports(&api->m_CurrentViewport, commandList->m_Viewport))
// 	{
// 		glViewport(commandList->m_Viewport->m_X, commandList->m_Viewport->m_Y, commandList->m_Viewport->m_Width, commandList->m_Viewport->m_Height); CheckGLESError();
// 		api->m_CurrentViewport = *commandList->m_Viewport;
// 	}
// 
// 	OpenGLESPipelineStateObject *pipelineStateObject = commandList->m_PipelineStateObject;
// 	uint32_t i;
// 	for (i = 0; i < commandList->m_NumConstantBuffers; ++i)
// 	{
// 		OpenGLESConstantBuffer *constantBuffer = commandList->m_ConstantBuffers[i];
// 		uint32_t elementIndex = 0;
// 		for (elementIndex = 0; elementIndex < constantBuffer->m_NumElements; ++elementIndex)
// 		{
// 			OpenGLESConstantBufferElement *element = &constantBuffer->m_Elements[elementIndex];
// 			const GLint uniformLocation = glGetUniformLocation(pipelineStateObject->m_ShaderProgram, element->m_Name); CheckGLESError();
// 			assert(-1 != uniformLocation);
// 			glUniformMatrix4fv(uniformLocation, 1, false, (float*)(&constantBuffer->m_Data[element->m_Offset])); CheckGLESError();
// 		}
// 	}
// 
// 	if (0 != commandList->m_DiffuseTexture)
// 	{
// 		glBindTexture(GL_TEXTURE_2D, commandList->m_DiffuseTexture->m_TextureID); CheckGLESError();
// 		const GLint diffuseTextureUniform =  glGetUniformLocation(pipelineStateObject->m_ShaderProgram, "u_DiffuseSampler"); CheckGLESError();
// 		glUniform1i(diffuseTextureUniform, 0); CheckGLESError();
// 	}
// 
// 	glBindBuffer(GL_ARRAY_BUFFER, commandList->m_VertexBuffer); CheckGLESError();
// 
// 	OpenGLESInputLayout *inputLayout = pipelineStateObject->m_InputLayout;
// 	for (i = 0; i < inputLayout->m_NumElements; ++i)
// 	{
// 		OpenGLESInputLayoutElement *element = &inputLayout->m_Elements[i];
// 		glEnableVertexAttribArray(element->m_Index); CheckGLESError();
// 		glVertexAttribPointer(element->m_Index, element->m_Size, element->m_Type, element->m_Normalized, element->m_Stride, BUFFER_OFFSET(element->m_Offset)); CheckGLESError();
// 	}
// 
// 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, commandList->m_IndexBuffer); CheckGLESError();
// 	glDrawElements(commandList->m_RenderMode, a_NumVertices, GL_UNSIGNED_INT, 0); CheckGLESError();
// #endif
// }
// 
// void GFXCreateCommandList(GFXAPI a_API, GFXCommandListDescriptor *a_Descriptor, GFXCommandListHandle *a_Handle)
// {
// 	GFX_UNUSED(a_API);
// 	assert(0 != a_API);
// 	assert(0 != a_Descriptor);
// 	OpenGLESCommandList *commandList = ALLOCATE(OpenGLESCommandList);
// 	memset(commandList, 0, sizeof(OpenGLESCommandList));
// 	if (0 != a_Descriptor->m_VertexBuffer)
// 	{
// 		commandList->m_VertexBuffer = ((OpenGLESVertexBuffer*)(a_Descriptor->m_VertexBuffer))->m_BufferID;
// 	}
// 	if (0 != a_Descriptor->m_IndexBuffer)
// 	{
// 		commandList->m_IndexBuffer = ((OpenGLESIndexBuffer*)(a_Descriptor->m_IndexBuffer))->m_BufferID;
// 	}
// 	commandList->m_Viewport = ((OpenGLESViewport*)(a_Descriptor->m_Viewport));
// 	commandList->m_RenderMode = TranslateRenderMode(a_Descriptor->m_RenderMode);
// 	commandList->m_PipelineStateObject = (OpenGLESPipelineStateObject*)a_Descriptor->m_PipelineStateObject;
// 	commandList->m_NumConstantBuffers = a_Descriptor->m_NumConstantBuffers;
// 	commandList->m_ConstantBuffers = (OpenGLESConstantBuffer**)malloc(sizeof(OpenGLESConstantBuffer*) * a_Descriptor->m_NumConstantBuffers);
// 	if (0 != a_Descriptor->m_NumConstantBuffers)	// be careful with how these are copied; always all of 'em or not...?!?!?
// 	{
// 		uint32_t i;
// 		for (i = 0; i < a_Descriptor->m_NumConstantBuffers; ++i)
// 		{
// 			commandList->m_ConstantBuffers[i] = (OpenGLESConstantBuffer*)a_Descriptor->m_ConstantBuffers[i];
// 		}
// 	}
// 	*a_Handle = commandList;
// }
// 
// void GFXUpdateCommandList(GFXAPI a_API, GFXCommandListDescriptor *a_Descriptor, GFXCommandListHandle a_Handle)
// {
// 	GFX_UNUSED(a_API);
// 	assert(0 != a_API);
// 	assert(0 != a_Descriptor);
// 	assert(0 != a_Handle);
// 	OpenGLESCommandList *commandList = a_Handle;
// 	if (0 != a_Descriptor->m_VertexBuffer) { commandList->m_VertexBuffer = ((OpenGLESVertexBuffer*)(a_Descriptor->m_VertexBuffer))->m_BufferID; }
// 	if (0 != a_Descriptor->m_IndexBuffer) { commandList->m_IndexBuffer = ((OpenGLESIndexBuffer*)(a_Descriptor->m_IndexBuffer))->m_BufferID; }
// 	if (0 != a_Descriptor->m_Viewport) { commandList->m_Viewport = ((OpenGLESViewport*)(a_Descriptor->m_Viewport)); }
// 	if (RenderMode_Invalid != a_Descriptor->m_RenderMode) { commandList->m_RenderMode = TranslateRenderMode(a_Descriptor->m_RenderMode); }
// 	if (0 != a_Descriptor->m_PipelineStateObject) { commandList->m_PipelineStateObject = (OpenGLESPipelineStateObject*)a_Descriptor->m_PipelineStateObject; }
// 	// copy constant buffers? probably not, they're already associated and we won't add/remove buffer on the fly, right?
// 	if (0 != a_Descriptor->m_DiffuseTexture) { commandList->m_DiffuseTexture = (OpenGLESTexture*)a_Descriptor->m_DiffuseTexture; }	
// }
// 
// void GFXDestroyCommandList(GFXAPI a_API, GFXCommandListHandle a_Handle)
// {
// 	GFX_UNUSED(a_API);
// 	assert(0 != a_API);
// 	if (0 != a_Handle) 
// 	{
// 		OpenGLESCommandList *commandList = a_Handle;
// 		free(commandList->m_ConstantBuffers);
// 		DEALLOCATE(commandList);
// 	}
// }
// 
// void GFXCreatePipelineStateObject(GFXAPI a_API, GFXPipelineStateObjectDescriptor *a_Descriptor, GFXPipelineStateObjectHandle *a_Handle)
// {
// 	GFX_UNUSED(a_API);
// 	assert(0 != a_API);
// 	assert(0 != a_Descriptor);
// 	OpenGLESPipelineStateObject *pipelineStateObject = ALLOCATE(OpenGLESPipelineStateObject);
// 	pipelineStateObject->m_ShaderProgram = ((OpenGLESShader*)(a_Descriptor->m_Shader))->m_ProgramID;
// 	pipelineStateObject->m_InputLayout = ((OpenGLESInputLayout*)a_Descriptor->m_InputLayout);
// 	*a_Handle = pipelineStateObject;
// }
// 
// void GFXSetPipelineStateObject(GFXAPI a_API, GFXPipelineStateObjectHandle a_Handle)
// {
// 	GFX_UNUSED(a_API);
// 	assert(0 != a_API);
// 	assert(0 != a_Handle);
// 	OpenGLESPipelineStateObject *pipelineStateObject = a_Handle;
// 	assert(0 != pipelineStateObject->m_ShaderProgram);
// 	glUseProgram(pipelineStateObject->m_ShaderProgram); CheckGLESError();
// }
// 
// void GFXDestroyPipelineStateObject(GFXAPI a_API, GFXPipelineStateObjectHandle a_Handle)
// {
// 	GFX_UNUSED(a_API);
// 	assert(0 != a_API);
// 	if (0 != a_Handle)
// 	{
// 		OpenGLESPipelineStateObject *pipelineStateObject = a_Handle;
// 		DEALLOCATE(pipelineStateObject);
// 	}
// }

#endif
