#pragma once

#include "OpenGLIncludes.h"

#if defined(GFX_API_OPENGL)

typedef struct OpenGLViewport
{
	GLint m_X;
	GLint m_Y;
	GLsizei m_Width;
	GLsizei m_Height;
} OpenGLViewport;

typedef struct OpenGLScissorRect
{
	GLint m_X;
	GLint m_Y;
	GLsizei m_Width;
	GLsizei m_Height;
} OpenGLScissorRect;

typedef struct OpenGLContext
{
	HDC m_DeviceContext;
	HGLRC m_RenderingContext;
} OpenGLContext;

typedef struct OpenGLAPI
{
	GLParameters m_Parameters;
	GLbitfield m_ClearMask;
	HWND m_WindowHandle;
	OpenGLContext m_Context;
	char m_CurrentContext;
	OpenGLViewport m_CurrentViewport;
} OpenGLAPI;

typedef struct OpenGLInterfaceItem
{
	char *m_Name;
	GLenum m_Type;
	GLint m_Location;
} OpenGLInterfaceItem;

typedef struct OpenGLShader
{
	GLuint m_BackEnd;
	GLenum m_Type;
// 	GLuint m_ProgramID;
// 	uint32_t m_NumUniforms;
// 	OpenGLInterfaceItem *m_Attributes;
// 	uint32_t m_NumAttributes;
// 	OpenGLInterfaceItem *m_Uniforms;
} OpenGLShader;

 typedef struct OpenGLConstantBufferElement
 {
 	char *m_Name;
 	uint32_t m_Offset;
 	uint32_t m_Size;
 	bool m_Transpose;
	GFXDataType m_Type;
 } OpenGLConstantBufferElement;
 
 typedef struct OpenGLConstantBuffer
 {
 	OpenGLConstantBufferElement *m_Elements;
 	uint32_t m_NumElements;
 	char *m_Data;
 } OpenGLConstantBuffer;
 
 typedef struct OpenGLResource
 {
 	void *unused;
 } OpenGLResource;
 
 typedef struct OpenGLInputLayoutElement
 {
 	GLuint m_Index;
 	GLint m_Size;
 	GLenum m_Type;
 	GLboolean m_Normalized;
 	GLsizei m_Stride;
 	GLint m_Offset;
 } OpenGLInputLayoutElement;
 
 typedef struct OpenGLInputLayout
 {
 	OpenGLInputLayoutElement *m_Elements;
 	uint32_t m_NumElements;
 } OpenGLInputLayout;
 
typedef struct OpenGLVertexBuffer
{
	GLuint m_VAOID;
	GLuint m_VBOID;
} OpenGLVertexBuffer;

typedef struct OpenGLIndexBuffer
{
	GLuint m_BufferID;
} OpenGLIndexBuffer;

typedef struct OpenGLTexture
{
	GLuint m_TextureID;
} OpenGLTexture;

typedef struct OpenGLBlendState
{
	void *unused;
} OpenGLBlendState;

typedef struct OpenGLRasterizerState
{
	void *unused;
} OpenGLRasterizerState;

typedef struct OpenGLPipelineStateObject
{
	GLuint m_ShaderProgram;
	OpenGLBlendState *m_BlendState;
	OpenGLRasterizerState *m_RasterizerState;
	OpenGLViewport *m_Viewport;
	OpenGLScissorRect *m_ScissorRect;
	OpenGLInputLayout *m_InputLayout;
	GLenum m_PrimitiveTopology;
} OpenGLPipelineStateObject;

typedef struct OpenGLCommandList
{
// 	OpenGLViewport *m_Viewport;
// 	OpenGLScissorRect *m_ScissorRect;
	OpenGLPipelineStateObject *m_PipelineStateObject;
	bool m_Recording;
} OpenGLCommandList;

typedef struct OpenGLCommandQueue
{
	void *unused;
} OpenGLCommandQueue;

typedef struct OpenGLSwapChain
{
	void *unused;
} OpenGLSwapChain;

typedef struct OpenGLRenderTarget
{
	bool m_ReadyForDraw;
	bool m_ReadyForPresent;
} OpenGLRenderTarget;

#endif
