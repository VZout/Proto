#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum GFXHandedness
{
	Handedness_Left,
	Handedness_Right,
	Handedness_Unknown
} GFXHandedness;

typedef enum GFXFillMode
{
	FillMode_Wireframe,
	FillMode_Solid,

	FillMode_Invalid
} GFXFillMode;

typedef enum GFXUsage
{
	Usage_Default,
	Usage_Immutable,
	Usage_Dynamic,
	Usage_Staging,

	Usage_Invalid
} GFXUsage;

typedef enum GFXCPUAccess
{
	CPUAccess_Read,
	CPUAccess_Write,
	CPUAccess_ReadWrite,

	CPUAccess_Invalid
} GFXCPUAccess;

typedef enum GFXShaderType
{
	ShaderType_VertexShader,
	ShaderType_FragmentShader,
	ShaderType_ComputeShader,
	ShaderType_Geometry,
	ShaderType_Tesselation,

	ShaderType_Invalid,
} GFXShaderType;

typedef enum GFXVertexAttribute
{
	VertexAttribute_Position,
	VertexAttribute_Color,
	VertexAttribute_TexCoord0,
	VertexAttribute_Normal,
	
	VertexAttribute_Invalid
} GFXVertexAttribute;

typedef enum GFXTextureFormat
{
	TextureFormat_RGB,
	TextureFormat_RGBA,

// 	TextureFormat_RGBFloat,
// 	TextureFormat_RGBAFloat,
// 	TextureFormat_RGBUint32,
// 	TextureFormat_RGBAUint32,

	TextureFormat_R32G32B32Float,
	TextureFormat_R32G32B32A32Float,

	TextureFormat_R8G8B8A8Uint32Normalized,

	TextureFormat_DepthStencilR16Typeless,
	TextureFormat_DepthStencilR16,
	TextureFormat_DepthStencilR32Typeless,
	TextureFormat_DepthStencilR32,
	TextureFormat_DepthStencilR24G8Typeless,
	TextureFormat_DepthStencilR24G8,
	TextureFormat_DepthStencilR32G8X24Typeless,
	TextureFormat_DepthStencilR32G8X24,
	
	TextureFormat_Invalid
} GFXTextureFormat;

typedef enum GFXRenderMode
{
	RenderMode_Invalid,		// should be 0

	RenderMode_Triangles
} GFXRenderMode;

typedef enum GFXDataType
{
	DataType_Byte,
	DataType_UnsignedByte,
	DataType_Short,
	DataType_UnsignedShort,
	DataType_Int32,
	DataType_UnsignedInt32,
	DataType_Float,
	DataType_Fixed,

	DataType_Invalid
} GFXDataType;

#ifdef __cplusplus
}
#endif
