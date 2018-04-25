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
	float m_R;
	float m_G;
	float m_B;
	float m_A;
} GFXColor;

void GFXGetBaseAPIName(char *a_ApiName);
char* GFXGetBaseAPICode();

GFXAPI GetAPI();

#if defined(GFX_API_DX11)
void GetDevice(GFXAPI a_API, ID3D11Device **a_Device);
void GetDeviceContext(GFXAPI a_API, ID3D11DeviceContext **a_DeviceContext);
#endif

void GFXInitialize(GFXAPI *a_API, Allocator *a_Allocator, GFXAPIDescriptor *a_Descriptor);
void GFXTerminate(GFXAPI a_API);

void GFXCreateViewport(GFXAPI a_API, GFXViewportDescriptor *a_Descriptor, GFXViewportHandle *a_Handle);
void GFXDestroyViewport(GFXAPI a_API, GFXViewportHandle a_Handle);

void GFXCreateSwapChain(GFXAPI a_API, GFXSwapChainDescriptor *a_Descriptor, GFXSwapChainHandle *a_Handle);
void GFXDestroySwapChain(GFXAPI a_API, GFXSwapChainHandle a_Handle);

void GFXCreateRenderTarget(GFXAPI a_API, GFXRenderTargetDescriptor *a_Descriptor, GFXRenderTargetHandle *a_Handle);
void GFXDestroyRenderTarget(GFXAPI a_API, GFXRenderTargetHandle a_Handle);

void GFXCreateDepthStencilState(GFXAPI a_API, GFXDepthStencilStateDescriptor *a_Descriptor, GFXDepthStencilStateHandle *a_Handle);
void GFXDestroyDepthStencilState(GFXAPI a_API, GFXDepthStencilStateHandle a_Handle);

void GFXCreateRasterizerState(GFXAPI a_API, GFXRasterizerStateDescriptor *a_Descriptor, GFXRasterizerStateHandle *a_Handle);
void GFXDestroyRasterizerState(GFXAPI a_API, GFXRasterizerStateHandle a_Handle);

void GFXCreateBlendState(GFXAPI a_API, GFXBlendStateDescriptor *a_Descriptor, GFXBlendStateHandle *a_Handle);
void GFXDestroyBlendState(GFXAPI a_API, GFXBlendStateHandle a_Handle);

void GFXClearRenderTarget(GFXAPI a_API, GFXRenderTargetHandle m_RenderTarget, GFXColor m_ClearColor);

void GFXPresent(GFXAPI a_API, GFXSwapChainHandle a_Handle);

void GFXCreateVertexBuffer(GFXAPI a_API, GFXVertexBufferDescriptor *a_Descriptor, GFXVertexBufferHandle *a_Handle);
void GFXUpdateVertexBuffer(GFXAPI a_API, GFXVertexBufferDescriptor *a_Descriptor, GFXVertexBufferHandle a_Handle);
void GFXDestroyVertexBuffer(GFXAPI a_API, GFXVertexBufferHandle a_Handle);
void GFXCreateIndexBuffer(GFXAPI a_API, GFXIndexBufferDescriptor *a_Descriptor, GFXIndexBufferHandle *a_Handle);
void GFXDestroyIndexBuffer(GFXAPI a_API, GFXIndexBufferHandle a_Handle);

void GFXCreateTexture(GFXAPI a_API, GFXTextureDescriptor *a_Descriptor, GFXTextureHandle *a_Handle);
void GFXDestroyTexture(GFXAPI a_API, GFXTextureHandle a_Handle);

void GFXCreateSamplerState(GFXAPI a_API, GFXSamplerStateDescriptor *a_Descriptor, GFXSamplerStateHandle *a_Handle);
void GFXDestroySamplerState(GFXAPI a_API, GFXSamplerStateHandle a_Handle);

void GFXCreateShader(GFXAPI a_API, GFXShaderDescriptor *a_Descriptor, GFXShaderHandle *a_Handle);
void GFXDestroyShader(GFXAPI a_API, GFXShaderHandle a_Handle);
void GFXCreateInputLayout(GFXAPI a_API, GFXInputLayoutDescriptor *a_Descriptor, GFXInputLayoutHandle *a_Handle);
void GFXDestroyInputLayout(GFXAPI a_API, GFXInputLayoutHandle a_Handle);

void GFXCreateConstantBuffer(GFXAPI a_API, GFXConstantBufferDescriptor *a_Descriptor, GFXConstantBufferHandle *a_Handle);
void GFXCopyConstantBufferData(GFXAPI a_API, GFXConstantBufferHandle a_Handle, const char *a_VariableName, const void *a_Data);
void GFXDestroyConstantBuffer(GFXAPI a_API, GFXConstantBufferHandle a_Handle);

void GFXCreateResource(GFXAPI a_API, GFXResourceDescriptor *a_Descriptor, GFXResourceHandle *a_Handle);
void GFXDestroyResource(GFXAPI a_API, GFXResourceHandle a_Handle);

//void GFXDrawIndexed(GFXAPI a_API, uint32_t a_NumIndices);
void GFXDrawIndexed(GFXAPI a_API, GFXCommandListHandle a_Handle, uint32_t a_NumVertices);

void GFXCreateCommandQueue(GFXAPI a_API, GFXCommandQueueDescriptor *a_Descriptor, GFXCommandQueueHandle *a_Handle);
void GFXDestroyCommandQueue(GFXAPI a_API, GFXCommandQueueHandle a_Handle);
void GFXCreateCommandList(GFXAPI a_API, GFXCommandListDescriptor *a_Descriptor, GFXCommandListHandle *a_Handle);
void GFXUpdateCommandList(GFXAPI a_API, GFXCommandListDescriptor *a_Descriptor, GFXCommandListHandle a_Handle);
void GFXDestroyCommandList(GFXAPI a_API, GFXCommandListHandle a_Handle);
void GFXCreatePipelineStateObject(GFXAPI a_API, GFXPipelineStateObjectDescriptor *a_Descriptor, GFXPipelineStateObjectHandle *a_Handle);
void GFXSetPipelineStateObject(GFXAPI a_API, GFXPipelineStateObjectHandle a_Handle);
void GFXDestroyPipelineStateObject(GFXAPI a_API, GFXPipelineStateObjectHandle a_Handle);

// move to pipelinestate object eventually

// move to constant buffers eventually

// part of command lists

#ifdef __cplusplus
}
#endif
