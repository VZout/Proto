#pragma once

#include "Graphics/API/Defines.h"
#include "Graphics/API/Enums.h"
#include "Graphics/API/Handles.h"
#include "DX11API.h"
#include "DX11Includes.h"

#include <stdbool.h>
#include <stdint.h>

#if defined(GFX_API_DX11)

typedef struct DX11API
{
	uint32_t m_RefreshRateNumerator;
	uint32_t m_RefreshRateDenominator;
	uint32_t m_VideoCardMemory;
	char *m_VideoCardDescription;
	NativeWindowHandle m_WindowHandle;

	DX11Parameters m_Parameters;

	ID3D11Device *m_Device;
	ID3D11DeviceContext *m_DeviceContext;
	IDXGISwapChain *m_SwapChain; 
#if defined(_DEBUG)
	ID3D11Debug *m_DebugDevice;
	ID3D11InfoQueue *m_InfoQueue;
#endif
	D3D_FEATURE_LEVEL m_FeatureLevel;
	D3D11_VIEWPORT m_CurrentViewport;
} DX11API;

typedef struct DX11Viewport
{
	D3D11_VIEWPORT *m_Viewport;
} DX11Viewport;

typedef struct DX11SwapChain
{
	bool m_VSyncEnabled;
	IDXGISwapChain *m_SwapChain;
} DX11SwapChain;

typedef struct DX11RasterizerState
{
	ID3D11RasterizerState *m_RasterizerState;
} DX11RasterizerState;

typedef struct DX11Texture
{
	ID3D11Texture2D *m_Texture;
	ID3D11ShaderResourceView *m_ShaderResourceView;
} DX11Texture;

typedef struct DX11SamplerState
{
	ID3D11SamplerState *m_SamplerState;
} DX11SamplerState;

typedef struct DX11RenderTarget
{
	GFXTextureHandle m_DepthStencilBuffer;
	GFXDepthStencilStateHandle m_DepthStencilState;

	ID3D11DepthStencilView *m_DepthStencilView;
	ID3D11RenderTargetView *m_RenderTargetView;
} DX11RenderTarget;

typedef struct DX11DepthStencilState
{
	ID3D11DepthStencilState *m_DepthStencilState;
} DX11DepthStencilState;

typedef struct DX11BlendState
{
	ID3D11BlendState *m_BlendState;
	float m_Factor[4];
	uint32_t m_SampleMask;
} DX11BlendState;

typedef struct DX11InputLayout
{
	uint32_t m_VertexByteSize;
	ID3D11InputLayout *m_InputLayout;
} DX11InputLayout;

typedef struct DX11VertexBuffer
{
	ID3D11Buffer *m_Buffer;
} DX11VertexBuffer;

typedef struct DX11IndexBuffer
{
	ID3D11Buffer *m_Buffer;
} DX11IndexBuffer;

typedef struct DX11ConstantBufferElement
{
	char *m_Name;
	uint32_t m_Size;
	GFXDataType m_Type;
	bool m_Transpose;
	uint32_t m_Offset;
} DX11ConstantBufferElement;

typedef struct DX11ConstantBuffer
{
#if defined(_DEBUG)
	char *m_Name;
#endif
	uint32_t m_Size;
	DX11ConstantBufferElement *m_Elements;
	uint32_t m_NumElements;
	char *m_Data;
	ID3D11Buffer *m_Buffer;
} DX11ConstantBuffer;

typedef struct DX11Shader
{
	ID3D11VertexShader *m_VertexShader;
	ID3D11PixelShader *m_PixelShader;
	ID3DBlob *m_ByteCode;
	//DX11ConstantBuffer *m_ConstantBuffer;
} DX11Shader;

typedef struct DX11PipelineStateObject
{
	DX11Shader *m_Shader;
	// Shader bytecode for vertex, pixel, domain, hull, and geometry shaders(D3D12_SHADER_BYTECODE)
	// The stream output buffer(D3D12_STREAM_OUTPUT_DESC)
	DX11BlendState *m_BlendState;
	DX11RasterizerState *m_RasterizerState;
	// The depth / stencil state(D3D12_DEPTH_STENCIL_DESC)
	DX11InputLayout *m_InputLayout;
	// The primitive topology(D3D12_PRIMITIVE_TOPOLOGY_TYPE)	// hull and geometry shader setting
	// The number of render targets(this tutorial we have 2 for double buffering, but you could use 3 for tripple buffering.swap - chains have a 3 queued frames limit before DXGI will start blocking in present())
	DX11RenderTarget *m_RenderTarget;
	// Render Target View formats(DXGI_FORMAT)
	// Depth Stencil View format(DXGI_FORMAT)
	// Sample description(DXGI_SAMPLE_DESC)
} DX11PipelineStateObject;

typedef struct DX11CommandList
{
	DX11VertexBuffer *m_VertexBuffer;
	DX11IndexBuffer *m_IndexBuffer;
	// stream output targets
	DX11RenderTarget *m_RenderTarget;
	uint32_t m_NumConstantBuffers;
	DX11ConstantBuffer **m_ConstantBuffers;	// should be changed to descriptor heaps when moving to DX12 or Vulkan
	DX11Texture *m_DiffuseTexture;			// should be changed to resources when moving to DX12 or Vulkan
	DX11SamplerState *m_SamplerState;		// should be changed to root signature when moving to DX12 or Vulkan
	// graphics root arguments
	DX11Viewport *m_Viewport;
	// Scissor Rectangles
	// Blend factor
	// Depth / Stencil reference value
	D3D11_PRIMITIVE_TOPOLOGY m_RenderMode;
	// Primitive topology order and adjacency type
	DX11PipelineStateObject *m_PipelineStateObject;
} DX11CommandList;

#endif
