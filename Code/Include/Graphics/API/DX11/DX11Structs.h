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
#if !defined(NDEBUG)
	ID3D11Debug *m_DebugDevice;
	ID3D11InfoQueue *m_InfoQueue;
#endif
	D3D_FEATURE_LEVEL m_FeatureLevel;
	D3D11_VIEWPORT m_CurrentViewport;
} DX11API;

typedef struct DX11Viewport
{
	D3D11_VIEWPORT *m_BackEnd;
} DX11Viewport;

typedef struct DX11ScissorRect
{
	D3D11_RECT *m_BackEnd;
} DX11ScissorRect;

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

	bool m_ReadyForDraw;
	bool m_ReadyForPresent;
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
	ID3D11InputLayout *m_BackEnd;
} DX11InputLayout;

typedef struct DX11VertexBuffer
{
	ID3D11Buffer *m_BackEnd;
} DX11VertexBuffer;

typedef struct DX11IndexBuffer
{
	ID3D11Buffer *m_BackEnd;
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
	size_t m_ByteSize;
	size_t m_Offset;
	uint8_t *m_Data;
	ID3D11Buffer *m_BackEnd;
} DX11ConstantBuffer;

typedef struct DX11Shader
{
	// not really nice; maybe store the ID3DBlob (shader bytecode)?
// 	ID3D11VertexShader *m_VertexShader;
// 	ID3D11PixelShader *m_PixelShader;
// 	ID3D11DomainShader *m_DomainShader;
// 	ID3D11HullShader *m_HullShader;
// 	ID3D11GeometryShader *m_GeometryShader;
// 	ID3D11ComputeShader *m_ComputeShader;

	ID3DBlob *m_ByteCode;
} DX11Shader;

typedef struct DX11PipelineStateObject
{
	ID3D11VertexShader *m_VertexShader;
	ID3D11PixelShader *m_PixelShader;
	DX11BlendState *m_BlendState;
	DX11RasterizerState *m_RasterizerState;
	DX11Viewport *m_Viewport;
	DX11ScissorRect *m_ScissorRect;
	DX11InputLayout *m_InputLayout;
	D3D11_PRIMITIVE_TOPOLOGY m_PrimitiveTopology;

} DX11PipelineStateObject;

typedef struct DX11CommandList
{
	DX11PipelineStateObject *m_PipelineStateObject;
	bool m_Recording;
} DX11CommandList;

typedef struct DX11CommandQueue
{
	void *unused;
} DX11CommandQueue;

#endif
