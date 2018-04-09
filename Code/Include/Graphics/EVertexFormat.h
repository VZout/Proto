#pragma once

enum EVertexFormat
{
	EVertexFormat_Position = (1u << 1),
	EVertexFormat_Texture_0 = (1u << 2),
	EVertexFormat_Normal = (1u << 3),
	EVertexFormat_Tangent = (1u << 4),
	EVertexFormat_Bitangent = (1u << 5),

	EVertexFormat_Count = 5,
	EVertexFormat_Invalid = -1
};
