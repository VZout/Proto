#pragma once

#include "OpenGLESIncludes.h"

#if defined(GFX_API_OPENGLES)

typedef struct OpenGLESViewport
{
	GLint m_X;
	GLint m_Y;
	GLsizei m_Width;
	GLsizei m_Height;
} OpenGLESViewport;

typedef struct OpenGLESScissorRect
{
	GLint m_X;
	GLint m_Y;
	GLsizei m_Width;
	GLsizei m_Height;
} OpenGLESScissorRect;

typedef struct OpenGLESSwapChain
{
	void *unused;
} OpenGLESSwapChain;

typedef struct OpenGLESRenderTarget
{
	bool m_ReadyForDraw;
	bool m_ReadyForPresent;
} OpenGLESRenderTarget;

typedef struct OpenGLESBlendState
{
	void *unused;
} OpenGLESBlendState;

typedef struct OpenGLESRasterizerState
{
	GLenum m_CullFace;
	GLenum m_FrontFaceCulling;
} OpenGLESRasterizerState;

typedef struct OpenGLESAPI
{
	EGLDisplay m_Display;
	EGLSurface m_Surface;
	EGLContext m_Context;
#if defined(PROTO_PLATFORM_RASPBERRY_PI)
	EGL_DISPMANX_WINDOW_T m_DisplayElement;
#endif
	GLESParameters m_Parameters;

	OpenGLESViewport m_CurrentViewport;
} OpenGLESAPI;

typedef struct OpenGLESShader
{
	GLuint m_BackEnd;
	GLenum m_Type;
} OpenGLESShader;

typedef struct OpenGLESConstantBufferElement
{
	char *m_Name;
	uint32_t m_Offset;
	uint32_t m_Size;
	GLuint m_UniformLocation;
	bool m_Transpose;
	GFXDataType m_Type;
} OpenGLESConstantBufferElement;

typedef struct OpenGLESConstantBuffer
{
	OpenGLESConstantBufferElement *m_Elements;
	uint32_t m_NumElements;
	char *m_Data;
} OpenGLESConstantBuffer;

typedef struct OpenGLESResource
{
	void *unused;
} OpenGLESResource;

typedef struct OpenGLESInputLayoutElement
{
	GLuint m_Index;
	GLint m_Size;
	GLenum m_Type;
	GLboolean m_Normalized;
	GLsizei m_Stride;
	GLint m_Offset;
} OpenGLESInputLayoutElement;

typedef struct OpenGLESInputLayout
{
	OpenGLESInputLayoutElement *m_Elements;
	uint32_t m_NumElements;
} OpenGLESInputLayout;

typedef struct OpenGLESVertexBuffer
{
	GLuint m_BufferID;
} OpenGLESVertexBuffer;

typedef struct OpenGLESIndexBuffer
{
	GLuint m_BufferID;
} OpenGLESIndexBuffer;

typedef struct OpenGLESTexture
{
	GLuint m_TextureID;
} OpenGLESTexture;

typedef struct OpenGLESPipelineStateObject
{
	GLuint m_ShaderProgram;
	GLbitfield m_ClearMask;
	OpenGLESBlendState *m_BlendState;
	OpenGLESRasterizerState *m_RasterizerState;
	OpenGLESViewport *m_Viewport;
	OpenGLESScissorRect *m_ScissorRect;
	OpenGLESInputLayout *m_InputLayout;
	GLenum m_RenderMode;
} OpenGLESPipelineStateObject;

typedef struct OpenGLESCommandList
{
	OpenGLESPipelineStateObject *m_PipelineStateObject;
	bool m_Recording;
} OpenGLESCommandList;

typedef struct OpenGLESCommandQueue
{
	void *unused;
} OpenGLESCommandQueue;

#endif
