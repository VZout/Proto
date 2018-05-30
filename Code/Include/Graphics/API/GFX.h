#pragma once

#include "Defines.h"
#include "Descriptors.h"
#include "Handles.h"

#if defined(GFX_API_DX11)
	#include "DX11/DX11API.h"
#elif defined(GFX_API_DX12)
	#include "DX12/DX12API.h"
#elif defined(GFX_API_OPENGL)
	#include "OpenGL/OpenGLAPI.h"
#elif defined(GFX_API_OPENGLES)
	#include "OpenGLES/OpenGLESAPI.h"
#elif defined(GFX_API_VULKAN)
	#include "Vulkan/VulkanAPI.h"
#elif defined(GFX_API_ORBIS)
	#include "ORBIS/ORBISAPI.h"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct Allocator Allocator;

typedef struct GFXColor
{
#if !defined(PROTO_PLATFORM_ORBIS)
#pragma warning(push)
#pragma warning(disable : 4201)
#endif
	union
	{
		float m_F[4];
		struct
		{
			float m_R;
			float m_G;
			float m_B;
			float m_A;
		};
	};
#if !defined(PROTO_PLATFORM_ORBIS)
#pragma warning(pop)
#endif
} GFXColor;

PROTO_DLL_FUNC void GFXGetBaseAPIName(char *a_ApiName);
PROTO_DLL_FUNC char* GFXGetBaseAPICode();

PROTO_DLL_FUNC void GFXInitialize(GFXAPI *a_API, Allocator *a_Allocator, GFXAPIDescriptor *a_Descriptor);
PROTO_DLL_FUNC void GFXTerminate(GFXAPI a_API);

PROTO_DLL_FUNC void GFXCreateViewport(GFXAPI a_API, GFXViewportDescriptor *a_Descriptor, GFXViewportHandle *a_Handle);
PROTO_DLL_FUNC void GFXDestroyViewport(GFXAPI a_API, GFXViewportHandle a_Handle);

PROTO_DLL_FUNC void GFXCreateScissorRect(GFXAPI a_API, GFXScissorRectDescriptor *a_Descriptor, GFXScissorRectHandle *a_Handle);
PROTO_DLL_FUNC void GFXDestroyScissorRect(GFXAPI a_API, GFXScissorRectHandle a_Handle);

PROTO_DLL_FUNC void GFXCreateSwapChain(GFXAPI a_API, GFXSwapChainDescriptor *a_Descriptor, GFXSwapChainHandle *a_Handle);
PROTO_DLL_FUNC void GFXDestroySwapChain(GFXAPI a_API, GFXSwapChainHandle a_Handle);

PROTO_DLL_FUNC void GFXCreateRenderTarget(GFXAPI a_API, GFXRenderTargetDescriptor *a_Descriptor, GFXRenderTargetHandle *a_Handle);
PROTO_DLL_FUNC void GFXDestroyRenderTarget(GFXAPI a_API, GFXRenderTargetHandle a_Handle);

PROTO_DLL_FUNC void GFXCreateDepthStencilState(GFXAPI a_API, GFXDepthStencilStateDescriptor *a_Descriptor, GFXDepthStencilStateHandle *a_Handle);
PROTO_DLL_FUNC void GFXDestroyDepthStencilState(GFXAPI a_API, GFXDepthStencilStateHandle a_Handle);

PROTO_DLL_FUNC void GFXCreateRasterizerState(GFXAPI a_API, GFXRasterizerStateDescriptor *a_Descriptor, GFXRasterizerStateHandle *a_Handle);
PROTO_DLL_FUNC void GFXDestroyRasterizerState(GFXAPI a_API, GFXRasterizerStateHandle a_Handle);

PROTO_DLL_FUNC void GFXCreateBlendState(GFXAPI a_API, GFXBlendStateDescriptor *a_Descriptor, GFXBlendStateHandle *a_Handle);
PROTO_DLL_FUNC void GFXDestroyBlendState(GFXAPI a_API, GFXBlendStateHandle a_Handle);

PROTO_DLL_FUNC void GFXPresent(GFXAPI a_API, GFXSwapChainHandle a_Handle);

PROTO_DLL_FUNC void GFXCreateVertexBuffer(GFXAPI a_API, GFXVertexBufferDescriptor *a_Descriptor, GFXVertexBufferHandle *a_Handle);
PROTO_DLL_FUNC void GFXUpdateVertexBuffer(GFXAPI a_API, GFXVertexBufferDescriptor *a_Descriptor, GFXVertexBufferHandle a_Handle);
PROTO_DLL_FUNC void GFXDestroyVertexBuffer(GFXAPI a_API, GFXVertexBufferHandle a_Handle);
PROTO_DLL_FUNC void GFXCreateIndexBuffer(GFXAPI a_API, GFXIndexBufferDescriptor *a_Descriptor, GFXIndexBufferHandle *a_Handle);
PROTO_DLL_FUNC void GFXDestroyIndexBuffer(GFXAPI a_API, GFXIndexBufferHandle a_Handle);

PROTO_DLL_FUNC void GFXCreateTexture(GFXAPI a_API, GFXTextureDescriptor *a_Descriptor, GFXTextureHandle *a_Handle);
PROTO_DLL_FUNC void GFXDestroyTexture(GFXAPI a_API, GFXTextureHandle a_Handle);

PROTO_DLL_FUNC void GFXCreateSamplerState(GFXAPI a_API, GFXSamplerStateDescriptor *a_Descriptor, GFXSamplerStateHandle *a_Handle);
PROTO_DLL_FUNC void GFXDestroySamplerState(GFXAPI a_API, GFXSamplerStateHandle a_Handle);

PROTO_DLL_FUNC void GFXCreateShader(GFXAPI a_API, GFXShaderDescriptor *a_Descriptor, GFXShaderHandle *a_Handle);
PROTO_DLL_FUNC void GFXDestroyShader(GFXAPI a_API, GFXShaderHandle a_Handle);

// PROTO_DLL_FUNC void GFXCreateInputLayout(GFXAPI a_API, GFXInputLayoutDescriptor *a_Descriptor, GFXInputLayoutHandle *a_Handle);
// PROTO_DLL_FUNC void GFXDestroyInputLayout(GFXAPI a_API, GFXInputLayoutHandle a_Handle);

PROTO_DLL_FUNC void GFXCreateConstantBuffer(GFXAPI a_API, GFXConstantBufferDescriptor *a_Descriptor, GFXConstantBufferHandle *a_Handle);
PROTO_DLL_FUNC void GFXWriteConstantBufferData(GFXAPI a_API, GFXCommandListHandle a_CommandListHandle, GFXConstantBufferHandle a_ConstantBufferHandle, const void *a_Data, size_t a_ByteSize);
PROTO_DLL_FUNC void GFXDestroyConstantBuffer(GFXAPI a_API, GFXConstantBufferHandle a_Handle);

PROTO_DLL_FUNC void GFXCreateResource(GFXAPI a_API, GFXResourceDescriptor *a_Descriptor, GFXResourceHandle *a_Handle);
PROTO_DLL_FUNC void GFXDestroyResource(GFXAPI a_API, GFXResourceHandle a_Handle);

//void GFXDrawIndexed(GFXAPI a_API, uint32_t a_NumIndices);
PROTO_DLL_FUNC void GFXDrawInstanced(GFXAPI a_API, GFXCommandListHandle a_CommandList, GFXInstancedDrawDescriptor a_Descriptor);
//PROTO_DLL_FUNC void GFXDrawIndexed(GFXAPI a_API, GFXCommandListHandle a_Handle, uint32_t a_NumVertices);

PROTO_DLL_FUNC void GFXCreateCommandQueue(GFXAPI a_API, GFXCommandQueueDescriptor *a_Descriptor, GFXCommandQueueHandle *a_Handle);
PROTO_DLL_FUNC void GFXWaitForCommandQueueCompletion(GFXAPI a_API, GFXCommandQueueHandle a_Handle);
PROTO_DLL_FUNC void GFXDestroyCommandQueue(GFXAPI a_API, GFXCommandQueueHandle a_Handle);

PROTO_DLL_FUNC void GFXCreateCommandList(GFXAPI a_API, GFXCommandListDescriptor *a_Descriptor, GFXCommandListHandle *a_Handle);
PROTO_DLL_FUNC void GFXStartRecordingCommandList(GFXAPI a_API, GFXCommandListHandle a_CommandListHandle, GFXPipelineStateObjectHandle a_PipelineStateObjectHandle);
PROTO_DLL_FUNC void GFXStopRecordingCommandList(GFXAPI a_API, GFXCommandListHandle a_Handle);
PROTO_DLL_FUNC void GFXExecuteCommandList(GFXAPI a_API, GFXCommandListHandle a_CommandListHandle, GFXCommandQueueHandle a_CommandQueueHandle);
PROTO_DLL_FUNC void GFXDestroyCommandList(GFXAPI a_API, GFXCommandListHandle a_Handle);

PROTO_DLL_FUNC void GFXCreatePipelineStateObject(GFXAPI a_API, GFXPipelineStateObjectDescriptor *a_Descriptor, GFXPipelineStateObjectHandle *a_Handle);
PROTO_DLL_FUNC void GFXSetPipelineStateObject(GFXAPI a_API, GFXPipelineStateObjectHandle a_Handle);
PROTO_DLL_FUNC void GFXDestroyPipelineStateObject(GFXAPI a_API, GFXPipelineStateObjectHandle a_Handle);

// commandlist commands
PROTO_DLL_FUNC void GFXPrepareRenderTargetForDraw(GFXAPI a_API, GFXCommandListHandle a_CommandListHandle, GFXRenderTargetHandle a_RenderTargetHandle);
PROTO_DLL_FUNC void GFXClearRenderTarget(GFXAPI a_API, GFXCommandListHandle a_CommandListHandle, GFXRenderTargetHandle a_RenderTargetHandle, const GFXColor a_ClearColor);
PROTO_DLL_FUNC void GFXPrepareRenderTargetForPresent(GFXAPI a_API, GFXCommandListHandle a_CommandListHandle, GFXRenderTargetHandle a_RenderTargetHandle);

#ifdef __cplusplus
}
#endif
