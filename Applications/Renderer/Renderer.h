#pragma once

#include "Proto.h"

#include "Graphics/API/GFX.h"
#include "Graphics/Mesh.h"

FORWARD_DECLARE(Graphics, class Camera)
FORWARD_DECLARE(Platform, class Window)

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Initialize(Platform::Window &a_Window);
	void Update();
	void Render();
	void Terminate();

private:
	Graphics::Camera *m_Camera = nullptr;

	GFXAPI m_API;
	GFXColor m_ClearColor;
	GFXViewportHandle m_Viewport;
	GFXSwapChainHandle m_SwapChain;
	GFXRenderTargetHandle m_RenderTarget;
	GFXRasterizerStateHandle m_RasterizerState;
	GFXPipelineStateObjectHandle m_PipelineStateObject;
	GFXSamplerStateHandle m_SamplerState;
	GFXCommandListHandle m_CommandList;
	GFXTextureHandle m_EarthTexture;
	GFXTextureHandle m_MoonTexture;
	GFXInputLayoutHandle m_SimpleShaderInputLayout;
	GFXShaderHandle m_SimpleShader;
	GFXInputLayoutHandle m_DiffuseShaderInputLayout;
	GFXShaderHandle m_DiffuseShader;
	GFXConstantBufferHandle m_MatrixConstantBuffer;
	GFXConstantBufferHandle m_MaterialConstantBuffer;
	GFXConstantBufferHandle m_LightConstantBuffer;

	Graphics::Mesh m_SphereTexLit;
	Graphics::Mesh m_Sphere;
};
