#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum GFXHandedness
{
	Handedness_Left = 0,
	Handedness_Right,

	Handedness_Invalid,
	Handedness_Count = Handedness_Invalid
} GFXHandedness;

typedef enum GFXFillMode
{
	FillMode_Wireframe = 0,
	FillMode_Solid,

	FillMode_Invalid,
	FillMode_Count = FillMode_Invalid
} GFXFillMode;

typedef enum GFXUsage
{
	Usage_Default = 0,
	Usage_Immutable,
	Usage_Dynamic,
	Usage_Staging,

	Usage_Invalid,
	Usage_Count = Usage_Invalid
} GFXUsage;

typedef enum GFXCPUAccess
{
	CPUAccess_Read = 0,
	CPUAccess_Write,
	CPUAccess_ReadWrite,

	CPUAccess_Invalid,
	CPUAccess_Count = CPUAccess_Invalid
} GFXCPUAccess;

typedef enum GFXShaderType
{
	ShaderType_VertexShader = 0,
	ShaderType_FragmentShader,
	ShaderType_ComputeShader,
	ShaderType_Geometry,
	ShaderType_Tesselation,

	ShaderType_Invalid,
	ShaderType_Count = ShaderType_Invalid
} GFXShaderType;

// typedef enum GFXVertexAttribute
// {
// 	VertexAttribute_Position = 0,
// 	VertexAttribute_Color,
// 	VertexAttribute_TexCoord0,
// 	VertexAttribute_Normal,
// 
// 	VertexAttribute_Count,
// 	VertexAttribute_Invalid
// } GFXVertexAttribute;

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
	
	TextureFormat_Invalid,
	TextureFormat_Count = TextureFormat_Invalid
} GFXTextureFormat;

typedef enum GFXRenderMode
{
	RenderMode_Invalid = 0,		// should be 0

	RenderMode_Triangles,

	RenderMode_Count
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

	DataType_Invalid,
	DataType_Count = DataType_Invalid
} GFXDataType;

typedef enum GFXCommandQueueFlags
{
	CommandQueueFlags_None,
	CommandQueueFlags_DisableGPUTimeOut,

	CommandQueueFlags_Invalid,
	CommandQueueFlags_Count = CommandQueueFlags_Invalid
} GFXCommandQueueFlags;

typedef enum GFXCommandListType
{
	CommandListType_Direct,
	CommandListType_Bundle,
	CommandListType_Compute,
	CommandListType_Copy,
	CommandListType_VideoDecode,
	CommandListType_VideoProcess,

	CommandListType_Invalid,
	CommandListType_Count = CommandListType_Invalid
} GFXCommandListType;

typedef enum GFXResourceTransitionState
{
	ResourceState_Common,
// 	D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER = 0x1,
	ResourceState_IndexBuffer,
// 	D3D12_RESOURCE_STATE_INDEX_BUFFER = 0x2,
	ResourceState_RenderTarget,
// 	D3D12_RESOURCE_STATE_UNORDERED_ACCESS = 0x8,
// 	D3D12_RESOURCE_STATE_DEPTH_WRITE = 0x10,
// 	D3D12_RESOURCE_STATE_DEPTH_READ = 0x20,
// 	D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE = 0x40,
// 	D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE = 0x80,
// 	D3D12_RESOURCE_STATE_STREAM_OUT = 0x100,
// 	D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT = 0x200,
// 	D3D12_RESOURCE_STATE_COPY_DEST = 0x400,
// 	D3D12_RESOURCE_STATE_COPY_SOURCE = 0x800,
// 	D3D12_RESOURCE_STATE_RESOLVE_DEST = 0x1000,
// 	D3D12_RESOURCE_STATE_RESOLVE_SOURCE = 0x2000,
// 	D3D12_RESOURCE_STATE_GENERIC_READ = (((((0x1 | 0x2) | 0x40) | 0x80) | 0x200) | 0x800),
	ResourceState_Present,
// 	D3D12_RESOURCE_STATE_PREDICATION = 0x200,
// 	D3D12_RESOURCE_STATE_VIDEO_DECODE_READ = 0x10000,
// 	D3D12_RESOURCE_STATE_VIDEO_DECODE_WRITE = 0x20000,
// 	D3D12_RESOURCE_STATE_VIDEO_PROCESS_READ = 0x40000,
// 	D3D12_RESOURCE_STATE_VIDEO_PROCESS_WRITE
} GFXResourceTransitionState;

#ifdef __cplusplus
}
#endif
