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

typedef struct OpenGLShader
{
	GLuint m_ProgramID;
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

 typedef struct OpenGLPipelineStateObject
 {
 	GLuint m_ShaderProgram;
 	// Shader bytecode for vertex, pixel, domain, hull, and geometry shaders(D3D12_SHADER_BYTECODE)
 	// The stream output buffer(D3D12_STREAM_OUTPUT_DESC)
 	// The blend state(D3D12_BLEND_DESC)
 	// The rasterizer state(D3D12_RASTERIZER_DESC)
 	// The depth / stencil state(D3D12_DEPTH_STENCIL_DESC)
 	OpenGLInputLayout *m_InputLayout;
 	// The primitive topology(D3D12_PRIMITIVE_TOPOLOGY_TYPE)	// hull and geometry shader setting
 	// The number of render targets(this tutorial we have 2 for double buffering, but you could use 3 for tripple buffering.swap - chains have a 3 queued frames limit before DXGI will start blocking in present())
 	// Render Target View formats(DXGI_FORMAT)
 	// Depth Stencil View format(DXGI_FORMAT)
 	// Sample description(DXGI_SAMPLE_DESC)
 } OpenGLPipelineStateObject;
 
 typedef struct OpenGLCommandList
 {
 	GLuint m_VertexBuffer;
 	GLuint m_IndexBuffer;
 	// stream output targets
 	// render targets
	uint32_t m_NumConstantBuffers;
	OpenGLConstantBuffer **m_ConstantBuffers;	// should be changed to descriptor heaps when moving to DX12 or Vulkan
	OpenGLTexture *m_DiffuseTexture;			// should be changed to resources when moving to DX12 or Vulkan
 	// graphics root arguments
 	OpenGLViewport *m_Viewport;
 	// Scissor RectanGL
 	// Blend factor
 	// Depth / Stencil reference value
 	GLenum m_RenderMode;
 	// Primitive topology order and adjacency type
 	OpenGLPipelineStateObject *m_PipelineStateObject;
 } OpenGLCommandList;

#endif
