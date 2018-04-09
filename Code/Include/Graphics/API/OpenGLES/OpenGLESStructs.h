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

typedef struct OpenGLESAPI
{
	EGLDisplay m_Display;
	EGLSurface m_Surface;
	EGLContext m_Context;
#if defined(PROTO_PLATFORM_RASPBERRY_PI)
	EGL_DISPMANX_WINDOW_T m_DisplayElement;
#endif
	GLESParameters m_Parameters;

	GLbitfield m_ClearMask;
	OpenGLESViewport m_CurrentViewport;
} OpenGLESAPI;

typedef struct OpenGLESShader
{
	GLuint m_ProgramID;
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
	// Shader bytecode for vertex, pixel, domain, hull, and geometry shaders(D3D12_SHADER_BYTECODE)
	// The stream output buffer(D3D12_STREAM_OUTPUT_DESC)
	// The blend state(D3D12_BLEND_DESC)
	// The rasterizer state(D3D12_RASTERIZER_DESC)
	// The depth / stencil state(D3D12_DEPTH_STENCIL_DESC)
	OpenGLESInputLayout *m_InputLayout;
	// The primitive topology(D3D12_PRIMITIVE_TOPOLOGY_TYPE)	// hull and geometry shader setting
	// The number of render targets(this tutorial we have 2 for double buffering, but you could use 3 for tripple buffering.swap - chains have a 3 queued frames limit before DXGI will start blocking in present())
	// Render Target View formats(DXGI_FORMAT)
	// Depth Stencil View format(DXGI_FORMAT)
	// Sample description(DXGI_SAMPLE_DESC)
} OpenGLESPipelineStateObject;

typedef struct OpenGLESCommandList
{
	GLuint m_VertexBuffer;
	GLuint m_IndexBuffer;
	// stream output targets
	// render targets
	uint32_t m_NumConstantBuffers;
	OpenGLESConstantBuffer **m_ConstantBuffers;	// should be changed to descriptor heaps when moving to DX12 or Vulkan
	OpenGLESTexture *m_DiffuseTexture;			// should be changed to resources when moving to DX12 or Vulkan
	// graphics root arguments
	OpenGLESViewport *m_Viewport;
	// Scissor Rectangles
	// Blend factor
	// Depth / Stencil reference value
	GLenum m_RenderMode;
	// Primitive topology order and adjacency type
	OpenGLESPipelineStateObject *m_PipelineStateObject;
} OpenGLESCommandList;

#endif
