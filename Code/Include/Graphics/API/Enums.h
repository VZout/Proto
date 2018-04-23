#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum GFXHandedness
{
	Handedness_Left = 0,
	Handedness_Right,

	Handedness_Count,
	Handedness_Unknown
} GFXHandedness;

typedef enum GFXFillMode
{
	FillMode_Wireframe = 0,
	FillMode_Solid,

	FillMode_Count,
	FillMode_Invalid
} GFXFillMode;

typedef enum GFXUsage
{
	Usage_Default = 0,
	Usage_Immutable,
	Usage_Dynamic,
	Usage_Staging,

	Usage_Count,
	Usage_Invalid
} GFXUsage;

typedef enum GFXCPUAccess
{
	CPUAccess_Read = 0,
	CPUAccess_Write,
	CPUAccess_ReadWrite,

	CPUAccess_Count,
	CPUAccess_Invalid
} GFXCPUAccess;

typedef enum GFXShaderType
{
	ShaderType_VertexShader = 0,
	ShaderType_FragmentShader,
	ShaderType_ComputeShader,
	ShaderType_Geometry,
	ShaderType_Tesselation,

	ShaderType_Count,
	ShaderType_Invalid
} GFXShaderType;

typedef enum GFXVertexAttribute
{
	VertexAttribute_Position = 0,
	VertexAttribute_Color,
	VertexAttribute_TexCoord0,
	VertexAttribute_Normal,

	VertexAttribute_Count,
	VertexAttribute_Invalid
} GFXVertexAttribute;

typedef enum GFXTextureFormat
{
	TextureFormat_RGB = 0,
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
	
	TextureFormat_Count,
	TextureFormat_Invalid
} GFXTextureFormat;

typedef enum GFXRenderMode
{
	RenderMode_Invalid = 0,		// should be 0

	RenderMode_Triangles,

	RenderMode_Count,
	//RenderMode_Invalid
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

	DataType_Count,
	DataType_Invalid
} GFXDataType;

#ifdef __cplusplus
}
#endif
