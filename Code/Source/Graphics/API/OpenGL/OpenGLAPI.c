#include "Graphics/API/GFX.h"

#include "Graphics/API/Helpers/TransposeData.h"
#include "Graphics/API/OpenGL/OpenGLAPI.h"
#include "Graphics/API/OpenGL/OpenGLShaderReflection.h"
#include "Graphics/API/OpenGL/OpenGLStructs.h"
#include "Graphics/API/OpenGL/OpenGLTranslators.h"
#include "Graphics/API/OpenGL/Helpers/CheckGLError.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(GFX_API_OPENGL)

#define MAJOR_VERSION 3
#define MINOR_VERSION 3

#define BUFFER_OFFSET(a_Offset) ((char*)0 + (a_Offset))

GFXAPI g_API = 0;
uint32_t g_MajorVersion = 0;
uint32_t g_MinorVersion = 0;

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

void CreateContext(OpenGLAPI *a_API, OpenGLContext *a_Context)
{
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	a_Context->m_DeviceContext = GetDC(a_API->m_WindowHandle);
	const int pixelFormat = ChoosePixelFormat(a_Context->m_DeviceContext, &pfd);
	assert(0 != pixelFormat);

	bool result = TRUE == SetPixelFormat(a_Context->m_DeviceContext, pixelFormat, &pfd);
	assert(result);

	HGLRC tempRenderContext = wglCreateContext(a_Context->m_DeviceContext);
	result = TRUE == wglMakeCurrent(a_Context->m_DeviceContext, tempRenderContext);
	assert(result);

	result = GLEW_OK == glewInit();
	assert(result);

	if (1 == wglewIsSupported("WGL_ARB_create_context"))
	{
		int attributes[7];
		attributes[0] = WGL_CONTEXT_MAJOR_VERSION_ARB; attributes[1] = a_API->m_Parameters.m_MajorVersion;
		attributes[2] = WGL_CONTEXT_MINOR_VERSION_ARB, attributes[3] = a_API->m_Parameters.m_MinorVersion;
#if (_DEBUG)
		attributes[4] = WGL_CONTEXT_FLAGS_ARB; attributes[5] = WGL_CONTEXT_CORE_PROFILE_BIT_ARB | WGL_CONTEXT_DEBUG_BIT_ARB;
#else
		attributes[4] = WGL_CONTEXT_FLAGS_ARB; attributes[5] = WGL_CONTEXT_CORE_PROFILE_BIT_ARB;
#endif
		attributes[6] = 0;

		a_Context->m_RenderingContext = wglCreateContextAttribsARB(a_Context->m_DeviceContext, NULL, attributes);
		assert(0 != a_Context->m_RenderingContext);
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(tempRenderContext);
		wglMakeCurrent(a_Context->m_DeviceContext, a_Context->m_RenderingContext);
	}
	else
	{
		a_Context->m_RenderingContext = tempRenderContext;
	}
}

void GFXGetBaseAPIName(char *a_ApiName)
{
	sprintf_s(a_ApiName, 16, "OpenGL %d.%d\0", MAJOR_VERSION, MINOR_VERSION);
}

char* GFXGetBaseAPICode()
{
	return "opengl";
}

GFXAPI GetAPI()
{
	assert(0 != g_API);
	return g_API;
}

bool EqualViewports(OpenGLViewport *a_CurrentViewport, OpenGLViewport *a_RequestedViewport)
{
	return a_CurrentViewport->m_X == a_RequestedViewport->m_X &&
		a_CurrentViewport->m_Y == a_RequestedViewport->m_Y &&
		a_CurrentViewport->m_Width == a_RequestedViewport->m_Width &&
		a_CurrentViewport->m_Height == a_RequestedViewport->m_Height;
}

// void GFXDrawIndexed(GFXAPI a_API, GFXCommandListHandle a_Handle, uint32_t a_NumVertices)
// {
// 	assert(0 != a_API);
// 	assert(0 != a_Handle);
// 	OpenGLAPI *api = a_API;
// 	OpenGLCommandList *commandList = a_Handle;
// 
// 	if (!EqualViewports(&api->m_CurrentViewport, commandList->m_Viewport))
// 	{
// 		glViewport(commandList->m_Viewport->m_X, commandList->m_Viewport->m_Y, commandList->m_Viewport->m_Width, commandList->m_Viewport->m_Height);
// 		api->m_CurrentViewport = *commandList->m_Viewport;
// 	}
// 
// 	OpenGLPipelineStateObject *pipelineStateObject = commandList->m_PipelineStateObject;
// 	uint32_t i;
// 	for (i = 0; i < commandList->m_NumConstantBuffers; ++i)
// 	{
// 		OpenGLConstantBuffer *constantBuffer = commandList->m_ConstantBuffers[i];
// 		uint32_t elementIndex = 0;
// 		for (elementIndex = 0; elementIndex < constantBuffer->m_NumElements; ++elementIndex)
// 		{
// 			OpenGLConstantBufferElement *element = &constantBuffer->m_Elements[elementIndex];
// 			const GLint uniformLocation = glGetUniformLocation(pipelineStateObject->m_ShaderProgram, element->m_Name);
// 			if (-1 != uniformLocation)
// 			{
// 				glUniformMatrix4fv(uniformLocation, 1, element->m_Transpose, (float*)(&constantBuffer->m_Data[element->m_Offset]));
// 			}
// 		}
// 	}
// 
// 	if (0 != commandList->m_DiffuseTexture)
// 	{
// 		glBindTexture(GL_TEXTURE_2D, commandList->m_DiffuseTexture->m_TextureID);
// 		const GLint diffuseTextureUniform = glGetUniformLocation(pipelineStateObject->m_ShaderProgram, "u_DiffuseSampler");
// 		if (-1 != diffuseTextureUniform)
// 		{
// 			glUniform1i(diffuseTextureUniform, 0);
// 		}
// 	}
// 
// 	glBindBuffer(GL_ARRAY_BUFFER, commandList->m_VertexBuffer);
// 
// 	OpenGLInputLayout *inputLayout = pipelineStateObject->m_InputLayout;
// 	for (i = 0; i < inputLayout->m_NumElements; ++i)
// 	{
// 		OpenGLInputLayoutElement *element = &inputLayout->m_Elements[i];
// 		glVertexAttribPointer(element->m_Index, element->m_Size, element->m_Type, element->m_Normalized, element->m_Stride, BUFFER_OFFSET(element->m_Offset));
// 		glEnableVertexAttribArray(element->m_Index);
// 	}
// 
// 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, commandList->m_IndexBuffer);
// 	glDrawElements(commandList->m_RenderMode, a_NumVertices, GL_UNSIGNED_INT, 0);
// }

void GFXInitialize(GFXAPI *a_API, Allocator *a_Allocator, GFXAPIDescriptor *a_Descriptor)
{
	GFX_UNUSED(a_Allocator);
	OpenGLAPI *api = ALLOCATE(OpenGLAPI);
	assert(0 != api);

	api->m_WindowHandle = a_Descriptor->m_WindowHandle;
	api->m_Parameters.m_MajorVersion = a_Descriptor->m_OpenGLMajorVerion;
	api->m_Parameters.m_MinorVersion = a_Descriptor->m_OpenGLMinorVersion;
	CreateContext(api, &api->m_Context);

#if !defined(NDEBUG)
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(CheckGLError, 0);
#endif
	glGetIntegerv(GL_MAJOR_VERSION, &api->m_Parameters.m_MajorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &api->m_Parameters.m_MinorVersion);
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &api->m_Parameters.MAX_VERTEX_ATTRIBUTES);
	api->m_Parameters.m_Version = glGetString(GL_VERSION);
	api->m_ClearMask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
	memset(&api->m_CurrentViewport, 0, sizeof(OpenGLViewport));

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	g_API = api;
	g_MajorVersion = api->m_Parameters.m_MajorVersion;
	g_MinorVersion = api->m_Parameters.m_MinorVersion;

	*a_API = api;
}

void GFXTerminate(GFXAPI a_API)
{
	assert(0 != a_API);
	OpenGLAPI *api = a_API;

	for (int i = 0; i < 2; ++i)
	{
		wglMakeCurrent(api->m_Context.m_DeviceContext, 0);
		wglDeleteContext(api->m_Context.m_RenderingContext);
		ReleaseDC(api->m_WindowHandle, api->m_Context.m_DeviceContext);
	}

	DEALLOCATE(a_API);
}

void GFXCreateViewport(GFXAPI a_API, GFXViewportDescriptor *a_Descriptor, GFXViewportHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	OpenGLViewport *viewport = ALLOCATE(OpenGLViewport);
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
	assert(0 != a_API);
	OpenGLViewport *viewport = a_Handle;
	DEALLOCATE(viewport);
}

void GFXCreateScissorRect(GFXAPI a_API, GFXScissorRectDescriptor *a_Descriptor, GFXScissorRectHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	OpenGLScissorRect *scissorRect = ALLOCATE(OpenGLScissorRect);
	*a_Handle = scissorRect;
}

void GFXDestroyScissorRect(GFXAPI a_API, GFXScissorRectHandle a_Handle)
{
	GFX_UNUSED(a_API);
	OpenGLScissorRect *scissorRect = (OpenGLScissorRect*)a_Handle;
	DEALLOCATE(scissorRect);
}

void GFXCreateSwapChain(GFXAPI a_API, GFXSwapChainDescriptor *a_Descriptor, GFXSwapChainHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	OpenGLSwapChain *swapChain = ALLOCATE(OpenGLSwapChain);
	*a_Handle = swapChain;
}

void GFXDestroySwapChain(GFXAPI a_API, GFXSwapChainHandle a_Handle)
{
	GFX_UNUSED(a_API);
	if (NULL != a_Handle)
	{
		OpenGLSwapChain *swapChain = (OpenGLSwapChain*)a_Handle;
		DEALLOCATE(swapChain);
	}
}

void GFXCreateRenderTarget(GFXAPI a_API, GFXRenderTargetDescriptor *a_Descriptor, GFXRenderTargetHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	OpenGLRenderTarget *renderTarget = ALLOCATE(OpenGLRenderTarget);
	*a_Handle = renderTarget;
}

void GFXDestroyRenderTarget(GFXAPI a_API, GFXRenderTargetHandle a_Handle)
{
	GFX_UNUSED(a_API);
	if (NULL != a_Handle)
	{
		OpenGLRenderTarget *renderTarget = (OpenGLRenderTarget*)a_Handle;
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
	assert(false);
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXDestroyRasterizerState(GFXAPI a_API, GFXRasterizerStateHandle a_Handle)
{
	assert(false);
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXCreateBlendState(GFXAPI a_API, GFXBlendStateDescriptor *a_Descriptor, GFXBlendStateHandle *a_Handle)
{
	assert(false);
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_Handle);
}

void GFXDestroyBlendState(GFXAPI a_API, GFXBlendStateHandle a_Handle)
{
	assert(false);
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXPresent(GFXAPI a_API, GFXSwapChainHandle a_Handle)
{
	GFX_UNUSED(a_Handle);
	assert(0 != a_API);
	OpenGLAPI *api = a_API;
	SwapBuffers(api->m_Context.m_DeviceContext);
}

void GFXCreateVertexBuffer(GFXAPI a_API, GFXVertexBufferDescriptor *a_Descriptor, GFXVertexBufferHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_Descriptor);
	OpenGLVertexBuffer *vertexBuffer = ALLOCATE(OpenGLVertexBuffer);

	glGenVertexArrays(1, &vertexBuffer->m_VAOID);
	assert(0 != vertexBuffer->m_VAOID);
	glBindVertexArray(vertexBuffer->m_VAOID);

	glGenBuffers(1, &vertexBuffer->m_VBOID);
	assert(0 != vertexBuffer->m_VBOID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->m_VBOID);

	const GLenum vertexBufferUsage = TranslateUsage(a_Descriptor->m_Usage);
	glBufferData(GL_ARRAY_BUFFER, a_Descriptor->m_DataByteSize, a_Descriptor->m_Vertices, vertexBufferUsage);
	*a_Handle = vertexBuffer;
}

void GFXUpdateVertexBuffer(GFXAPI a_API, GFXVertexBufferDescriptor *a_Descriptor, GFXVertexBufferHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_Descriptor);
	OpenGLVertexBuffer *vertexBuffer = a_Handle;
	assert(0 != vertexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->m_VBOID);
	glBufferSubData(GL_ARRAY_BUFFER, a_Descriptor->m_ByteOffset, a_Descriptor->m_DataByteSize, a_Descriptor->m_Vertices);
}

void GFXDestroyVertexBuffer(GFXAPI a_API, GFXVertexBufferHandle a_Handle)
{
	GFX_UNUSED(a_API);
	OpenGLVertexBuffer *vertexBuffer = a_Handle;
	assert(0 != vertexBuffer->m_VBOID);
	glDeleteBuffers(1, &vertexBuffer->m_VBOID);
	DEALLOCATE(vertexBuffer);
}

void GFXCreateIndexBuffer(GFXAPI a_API, GFXIndexBufferDescriptor *a_Descriptor, GFXIndexBufferHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	OpenGLIndexBuffer *indexBuffer = ALLOCATE(OpenGLIndexBuffer);
	glGenBuffers(1, &indexBuffer->m_BufferID);
	assert(0 != indexBuffer->m_BufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->m_BufferID);
	const GLenum indexBufferUsage = TranslateUsage(a_Descriptor->m_Usage);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_Descriptor->m_DataByteSize, a_Descriptor->m_Indices, indexBufferUsage);
	*a_Handle = indexBuffer;
}

void GFXDestroyIndexBuffer(GFXAPI a_API, GFXIndexBufferHandle a_Handle)
{
	GFX_UNUSED(a_API);
	OpenGLIndexBuffer *indexBuffer = a_Handle;
	assert(0 != indexBuffer->m_BufferID);
	glDeleteBuffers(1, &indexBuffer->m_BufferID);
	DEALLOCATE(indexBuffer);
}

void GFXCreateTexture(GFXAPI a_API, GFXTextureDescriptor *a_Descriptor, GFXTextureHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_API);
	OpenGLTexture *texture = ALLOCATE(OpenGLTexture);
	glGenTextures(1, &texture->m_TextureID);
	const GLenum target = GL_TEXTURE_2D;
	glBindTexture(target, texture->m_TextureID);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// parameterize in descriptor
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	// parameterize in descriptor
	const GLint level = 0;
	const GLenum internalFormat = GL_RGBA;
	const GLenum format = TranslateTextureFormat(a_Descriptor->m_Format);
	const GLint border = 0;
	const GLenum type = TranslateTextureDataType(a_Descriptor->m_RowPitch / a_Descriptor->m_Width);
	glTexImage2D(target, level, internalFormat, a_Descriptor->m_Width, a_Descriptor->m_Height, border, format, type, a_Descriptor->m_Data);
	*a_Handle = texture;
	glBindTexture(target, 0);
}

void GFXDestroyTexture(GFXAPI a_API, GFXTextureHandle a_Handle)
{
	GFX_UNUSED(a_API);
	if (0 != a_Handle)
	{
		OpenGLTexture *texture = a_Handle;
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
	// 	assert(0 != a_Descriptor);
	// 	assert(0 != a_Descriptor->m_NumShaders);
	// 
	// 	GLuint shaderProgram = glCreateProgram();
	// 	short i;
	// 	for (i = 0; i < a_Descriptor->m_NumShaders; ++i)
	// 	{
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

// 	glAttachShader(shaderProgram, shader);
	// 	}
	// 
	// 	glLinkProgram(shaderProgram);
	// 	GLint linked;
	// 	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);
	// 	if (GL_FALSE == linked)
	// 	{
	// 		CheckProgramInfoLog(shaderProgram);
	// 
	// 		glDeleteProgram(shaderProgram);
	// 		assert(false);
	// 	}
	// 
	// 	glValidateProgram(shaderProgram);
	// 	GLint validated;
	// 	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &validated);
	// 	if (GL_FALSE == validated)
	// 	{
	// 		CheckProgramInfoLog(shaderProgram);
	// 
	// 		glDeleteProgram(shaderProgram);
	// 		assert(false);
	// 	}
	// 
	// 	GLsizei numAttachedShaders;
	// 	GLuint attachedShaders[MAX_SHADERS_PER_PROGRAM];
	// 	glGetAttachedShaders(shaderProgram, MAX_SHADERS_PER_PROGRAM, &numAttachedShaders, attachedShaders);
	// 	for (i = 0; i < numAttachedShaders; ++i)
	// 	{
	// 		glDetachShader(shaderProgram, attachedShaders[i]);
	// 		glDeleteShader(attachedShaders[i]);
	// 	}
	// 
	// 	OpenGLShader *shader = ALLOCATE(OpenGLShader);
	// 	assert(0 != shader);
	// 	shader->m_ProgramID = shaderProgram;
	// 	InspectShaderProgram(api, shader);
	// 	*a_Handle = shader;
	OpenGLShader *shader = ALLOCATE(OpenGLShader);
	shader->m_BackEnd = shaderID;
	shader->m_Type = a_Descriptor->m_Type;
	*a_Handle = shader;
}

void GFXDestroyShader(GFXAPI a_API, GFXShaderHandle a_Handle)
{
	GFX_UNUSED(a_API);
	OpenGLShader *shader = a_Handle;
// 	glDeleteProgram(shader->m_ProgramID);
// 	uint32_t i = 0;
// 	for (i = 0; i < shader->m_NumAttributes; ++i)
// 	{
// 		DEALLOCATE(shader->m_Attributes[i].m_Name);
// 	}
// 	DEALLOCATE(shader->m_Attributes);
// 	for (i = 0; i < shader->m_NumUniforms; ++i)
// 	{
// 		DEALLOCATE(shader->m_Uniforms[i].m_Name);
// 	}
// 	DEALLOCATE(shader->m_Uniforms);
	DEALLOCATE(shader);
}

void GFXCreateInputLayout(GFXAPI a_API, GFXInputLayoutDescriptor *a_Descriptor, GFXInputLayoutHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_API);
	OpenGLInputLayout *inputLayout = ALLOCATE(OpenGLInputLayout);
	inputLayout->m_NumElements = a_Descriptor->m_NumElements;
	inputLayout->m_Elements = (OpenGLInputLayoutElement*)malloc(sizeof(OpenGLInputLayoutElement) * a_Descriptor->m_NumElements);
	uint32_t offset = 0;
	uint32_t i = 0;
	for (i = 0; i < a_Descriptor->m_NumElements; ++i)
	{
		inputLayout->m_Elements[i].m_Index = a_Descriptor->m_Elements[i].m_Index;
		inputLayout->m_Elements[i].m_Size = a_Descriptor->m_Elements[i].m_Size;
		inputLayout->m_Elements[i].m_Type = TranslateDataType(a_Descriptor->m_Elements[i].m_Type);
		inputLayout->m_Elements[i].m_Normalized = a_Descriptor->m_Elements[i].m_Normalized;
		inputLayout->m_Elements[i].m_Stride = a_Descriptor->m_Elements[i].m_Stride;
		inputLayout->m_Elements[i].m_Offset = offset;
		offset += a_Descriptor->m_Elements[i].m_Size * DataTypeByteSize(a_Descriptor->m_Elements[i].m_Type);
	}
	*a_Handle = inputLayout;
}

void GFXDestroyInputLayout(GFXAPI a_API, GFXInputLayoutHandle a_Handle)
{
	GFX_UNUSED(a_API);
	OpenGLInputLayout *inputLayout = a_Handle;
	if (0 != inputLayout)
	{
		DEALLOCATE(inputLayout->m_Elements);
		DEALLOCATE(inputLayout);
	}
}

void GFXCreateConstantBuffer(GFXAPI a_API, GFXConstantBufferDescriptor *a_Descriptor, GFXConstantBufferHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_API);
	OpenGLConstantBuffer *constantBuffer = ALLOCATE(OpenGLConstantBuffer);
	constantBuffer->m_Data = (char*)malloc(a_Descriptor->m_ByteSize * sizeof(char));
	constantBuffer->m_NumElements = a_Descriptor->m_NumElements;
	constantBuffer->m_Elements = (OpenGLConstantBufferElement*)malloc(constantBuffer->m_NumElements * sizeof(OpenGLConstantBufferElement));

	uint32_t offset = 0;
	uint32_t i = 0;
	for (i = 0; i < a_Descriptor->m_NumElements; ++i)
	{
		GFXConstantBufferElementDescriptor *element = &a_Descriptor->m_Elements[i];
		const size_t length = strlen(a_Descriptor->m_Elements[i].m_Name) + 1;
		constantBuffer->m_Elements[i].m_Name = (char*)malloc(length * sizeof(char));
		strcpy_s(constantBuffer->m_Elements[i].m_Name, length, element->m_Name);

		constantBuffer->m_Elements[i].m_Size = element->m_Size;
		constantBuffer->m_Elements[i].m_Offset = offset;
		constantBuffer->m_Elements[i].m_Transpose = element->m_Transpose;
		constantBuffer->m_Elements[i].m_Type = element->m_Type;

		offset += element->m_Size;
	}
	assert(0 != constantBuffer->m_Data);
	*a_Handle = constantBuffer;
}

void GFXCopyConstantBufferData(GFXAPI a_API, GFXConstantBufferHandle a_Handle, const char *a_VariableName, const void *a_Data)
{
	GFX_UNUSED(a_API);
	assert(0 != a_API);
	assert(0 != a_Data);
	bool copied = false;
	OpenGLConstantBuffer *constantBuffer = a_Handle;
	uint32_t i = 0;
	for (i; i < constantBuffer->m_NumElements && !copied; ++i)
	{
		OpenGLConstantBufferElement *element = &constantBuffer->m_Elements[i];
		if (0 == strcmp(element->m_Name, a_VariableName))
		{
			memcpy(&constantBuffer->m_Data[element->m_Offset], a_Data, element->m_Size);
			copied = true;
		}
	}
	assert(copied);
}

void GFXDestroyConstantBuffer(GFXAPI a_API, GFXConstantBufferHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_API);
	OpenGLConstantBuffer *constantBuffer = a_Handle;
	if (0 != constantBuffer)
	{
		uint32_t i = 0;
		for (i = 0; i < constantBuffer->m_NumElements; ++i)
		{
			DEALLOCATE(constantBuffer->m_Elements[i].m_Name);
		}
		DEALLOCATE(constantBuffer->m_Elements);
		DEALLOCATE(constantBuffer->m_Data);
		DEALLOCATE(constantBuffer);
	}
}

void GFXCreateResource(GFXAPI a_API, GFXResourceDescriptor *a_Descriptor, GFXResourceHandle *a_Handle)
{
#if !defined(NDEBUG)
	assert(0 != a_API);
	assert(0 != a_Descriptor);
#else
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
#endif
	OpenGLResource *resource = ALLOCATE(OpenGLResource);
	*a_Handle = resource;
}

void GFXDestroyResource(GFXAPI a_API, GFXResourceHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_API);
	OpenGLResource *resource = a_Handle;
	DEALLOCATE(resource);
}

//void GFXDrawIndexed(GFXAPI a_API, uint32_t a_NumIndices);
void GFXDrawInstanced(GFXAPI a_API, GFXCommandListHandle a_CommandList, GFXVertexBufferHandle a_VertexBuffer)
{
	assert(false);
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_VertexBuffer);
	GFX_UNUSED(a_CommandList);
}
//void GFXDrawIndexed(GFXAPI a_API, GFXCommandListHandle a_Handle, uint32_t a_NumVertices);

void GFXCreateCommandQueue(GFXAPI a_API, GFXCommandQueueDescriptor *a_Descriptor, GFXCommandQueueHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Descriptor);
	OpenGLCommandQueue *commandQueue = ALLOCATE(OpenGLCommandQueue);
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
		OpenGLCommandQueue *commandQueue = (OpenGLCommandQueue*)a_Handle;
		DEALLOCATE(commandQueue);
	}
}

void GFXCreateCommandList(GFXAPI a_API, GFXCommandListDescriptor *a_Descriptor, GFXCommandListHandle *a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_API);
	assert(0 != a_Descriptor);
	OpenGLCommandList *commandList = ALLOCATE(OpenGLCommandList);
	memset(commandList, 0, sizeof(OpenGLCommandList));
	commandList->m_PipelineStateObject = a_Descriptor->m_PipelineStateObject;
	commandList->m_Viewport = a_Descriptor->m_Viewport;
	commandList->m_ScissorRect = a_Descriptor->m_ScissorRect;
	commandList->m_Recording = false;
	*a_Handle = commandList;

}

void GFXStartRecordingCommandList(GFXAPI a_API, GFXCommandListHandle a_CommandListHandle, GFXPipelineStateObjectHandle a_PipelineStateObjectHandle)
{
	assert(false);
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_PipelineStateObjectHandle);
	GFX_UNUSED(a_CommandListHandle);
}

void GFXStopRecordingCommandList(GFXAPI a_API, GFXCommandListHandle a_Handle)
{
	assert(false);
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Handle);
}

void GFXExecuteCommandList(GFXAPI a_API, GFXCommandListHandle a_CommandListHandle, GFXCommandQueueHandle a_CommandQueueHandle)
{
	assert(false);
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_CommandListHandle);
	GFX_UNUSED(a_CommandQueueHandle);
}

void GFXDestroyCommandList(GFXAPI a_API, GFXCommandListHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_API);
	if (0 != a_Handle)
	{
		OpenGLCommandList *commandList = a_Handle;
		//DEALLOCATE(commandList->m_ConstantBuffers);
		DEALLOCATE(commandList);
	}
}

void GFXCreatePipelineStateObject(GFXAPI a_API, GFXPipelineStateObjectDescriptor *a_Descriptor, GFXPipelineStateObjectHandle *a_Handle)
{
	assert(false);
	GFX_UNUSED(a_Handle);
	GFX_UNUSED(a_Descriptor);
	GFX_UNUSED(a_API);
	// 	GFX_UNUSED(a_API);
	// 	assert(0 != a_API);
	// 	assert(0 != a_Descriptor);
	// 	OpenGLPipelineStateObject *pipelineStateObject = ALLOCATE(OpenGLPipelineStateObject);
	// 	pipelineStateObject->m_ShaderProgram = ((OpenGLShader*)(a_Descriptor->m_Shader))->m_ProgramID;
	// 	pipelineStateObject->m_InputLayout = ((OpenGLInputLayout*)a_Descriptor->m_InputLayout);
	// 	*a_Handle = pipelineStateObject;
}

void GFXSetPipelineStateObject(GFXAPI a_API, GFXPipelineStateObjectHandle a_Handle)
{
	GFX_UNUSED(a_API);
	assert(0 != a_Handle);
	OpenGLPipelineStateObject *pipelineStateObject = a_Handle;
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
	OpenGLPipelineStateObject *pipelineStateObject = a_Handle;
	DEALLOCATE(pipelineStateObject);
}

void GFXPrepareRenderTargetForDraw(GFXAPI a_API, GFXCommandListHandle a_CommandListHandle, GFXRenderTargetHandle a_RenderTargetHandle)
{
	assert(false);
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_CommandListHandle);
	GFX_UNUSED(a_RenderTargetHandle);
}

void GFXClearRenderTarget(GFXAPI a_API, GFXCommandListHandle a_CommandListHandle, GFXRenderTargetHandle a_RenderTargetHandle, const GFXColor a_ClearColor)
{
	assert(0 != a_API);
	OpenGLAPI *api = a_API;
	GFX_UNUSED(a_CommandListHandle);
	GFX_UNUSED(a_RenderTargetHandle);
	glClearColor(a_ClearColor.m_R, a_ClearColor.m_G, a_ClearColor.m_B, a_ClearColor.m_A);
	glClear(api->m_ClearMask);
}

void GFXPrepareRenderTargetForPresent(GFXAPI a_API, GFXCommandListHandle a_CommandListHandle, GFXRenderTargetHandle a_RenderTargetHandle)
{
	assert(false);
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_CommandListHandle);
	GFX_UNUSED(a_RenderTargetHandle);
}
#endif
