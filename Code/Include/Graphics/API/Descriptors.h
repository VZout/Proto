#pragma once

#include "Defines.h"
#include "Enums.h"
#include "Handles.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct GFXAPIDescriptor
{
	NativeWindowHandle m_WindowHandle;
	uint32_t m_FrameBufferWidth;
	uint32_t m_FrameBufferHeight;
	uint64_t m_ThreadID;

	bool m_UseSoftwareDevice;
} GFXAPIDescriptor;

typedef struct GFXViewportDescriptor
{
	uint32_t m_X;
	uint32_t m_Y;
	uint32_t m_Width;
	uint32_t m_Height;
} GFXViewportDescriptor;

typedef struct GFXSwapChainDescriptor
{
	GFXCommandQueueHandle m_CommandQueue;
	uint32_t m_FrameBufferWidth;
	uint32_t m_FrameBufferHeight;
	uint32_t m_MSAASampleCount;
	uint32_t m_MSAAQuality;
	uint32_t m_BufferCount;
	bool m_Fullscreen;
	bool m_VSync;
	bool m_EnableMSAA;
} GFXSwapChainDescriptor;

typedef struct GFXVertexBufferDescriptor
{
	GFXUsage m_Usage;
	size_t m_DataByteSize;
	void *m_Vertices;
	size_t m_ByteOffset;
} GFXVertexBufferDescriptor;

typedef struct GFXIndexBufferDescriptor
{
	GFXUsage m_Usage;
	size_t m_DataByteSize;
	void *m_Indices;
} GFXIndexBufferDescriptor;

typedef struct GFXTextureDescriptor
{
	uint32_t m_Width;
	uint32_t m_Height;
	uint32_t m_RowPitch;
	GFXTextureFormat m_Format;
	GFXTextureFormat m_ShaderResourceViewFormat;
	void *m_Data;
#if defined(_DEBUG)
	const char *m_DebugName;
#endif
	bool m_DepthStencil;
} GFXTextureDescriptor;

typedef struct GFXSamplerStateDescriptor
{
	void *unused;
#if defined(_DEBUG)
	const char *m_DebugName;
#endif
} GFXSamplerStateDescriptor;

typedef struct GFXShaderDescriptor
{
	int m_NumShaders;
	GFXShaderType m_Type[MAX_SHADERS_PER_PROGRAM];
	const char *m_Source[MAX_SHADERS_PER_PROGRAM];
// 	int m_NumAttributes;
// 	GFXVertexAttribute m_Attributes[MAX_ATTRIBUTES_PER_PROGRAM];
	uint64_t m_ThreadID;
} GFXShaderDescriptor;

typedef struct GFXConstantBufferElementDescriptor
{
	const char *m_Name;
	uint32_t m_Size;
	GFXDataType m_Type;
	bool m_Transpose;
} GFXConstantBufferElementDescriptor;

typedef struct GFXConstantBufferDescriptor
{
	uint32_t m_ByteSize;
	GFXConstantBufferElementDescriptor *m_Elements;
	uint32_t m_NumElements;
	GFXShaderHandle m_Shader;	// not sure if this should be here; will evaluate when creating dx12 api (needed for OpenGLES now)
#if defined(_DEBUG)
	const char *m_DebugName;
#endif
} GFXConstantBufferDescriptor;

typedef struct GFXInputLayoutElementDescriptor
{
	const char *m_Name;
	uint32_t m_Index;
	int32_t m_Size;
	GFXDataType m_Type;
	bool m_Normalized;
	uint32_t m_Stride;
// 	int32_t m_BufferOffset;
} GFXInputLayoutElementDescriptor;

typedef struct GFXInputLayoutDescriptor
{
	GFXInputLayoutElementDescriptor *m_Elements;
	uint32_t m_NumElements;
	uint32_t m_VertexByteSize;
	GFXShaderHandle m_Shader;
} GFXInputLayoutDescriptor;

typedef struct GFXRenderTargetDescriptor
{
	uint32_t m_Width;
	uint32_t m_Height;
} GFXRenderTargetDescriptor;

typedef struct GFXRasterizerStateDescriptor
{
	GFXFillMode m_FillMode;
	GFXHandedness m_Handedness;
} GFXRasterizerStateDescriptor;

typedef struct GFXBlendStateDescriptor
{
	float m_Factor[4];
	uint32_t m_SampleMask;
} GFXBlendStateDescriptor;

typedef struct GFXDepthStencilStateDescriptor
{
	bool m_DepthEnabled;
#if defined(_DEBUG)
	const char *m_DebugName;
#endif
} GFXDepthStencilStateDescriptor;

typedef struct GFXCommandQueueDescriptor
{
	GFXCommandQueueFlags m_Flags;
	GFXCommandQueueType m_Type;
} GFXCommandQueueDescriptor;

typedef struct GFXCommandListDescriptor
{
	GFXVertexBufferHandle m_VertexBuffer;
	GFXIndexBufferHandle m_IndexBuffer;
	GFXViewportHandle m_Viewport;
	GFXRenderMode m_RenderMode;
	GFXPipelineStateObjectHandle m_PipelineStateObject;
	uint32_t m_NumConstantBuffers;
	GFXConstantBufferHandle *m_ConstantBuffers;
	GFXTextureHandle m_DiffuseTexture;
	GFXSamplerStateHandle m_SamplerState;
} GFXCommandListDescriptor;

typedef struct GFXPipelineStateObjectDescriptor
{
	GFXShaderHandle m_Shader;
	GFXBlendStateHandle m_BlendState;
	GFXRasterizerStateHandle m_RasterizerState;
	GFXInputLayoutHandle m_InputLayout;
	GFXRenderTargetHandle m_RenderTarget;		// should not be part of the pipeline state object
} GFXPipelineStateObjectDescriptor;

typedef struct GFXResourceDescriptor
{
	void *unused;
} GFXResourceDescriptor;

#ifdef __cplusplus
}
#endif
