#include "GenerateGeometry.h"

#include "Graphics/EVertexFormat.h"
#include "Graphics/Mesh.h"

#include <vector>

void GenerateSphere(GFXAPI &a_API, Graphics::Mesh &a_Mesh, float a_Radius, int a_Slices, int a_Stacks, uint32_t a_VertexFormat)
{
	UNUSED(a_Mesh);
	UNUSED(a_API);

	const float pi = 3.1415926535897932384626433832795f;
	const float _2pi = 2.0f * pi;

	std::vector<float> vertexData;

	for (int i = 0; i <= a_Stacks; ++i)
	{
		// V texture coordinate.
		float V = i / (float)a_Stacks;
		float phi = V * pi;

		for (int j = 0; j <= a_Slices; ++j)
		{
			// U texture coordinate.
			float U = j / (float)a_Slices;
			float theta = U * _2pi;

			float X = cos(theta) * sin(phi);
			float Y = cos(phi);
			float Z = sin(theta) * sin(phi);

			// positions
			if (EVertexFormat_Position & a_VertexFormat)
			{
				vertexData.push_back(X * a_Radius); vertexData.push_back(Y * a_Radius); vertexData.push_back(Z * a_Radius);
			}
			// normals
			if (EVertexFormat_Normal & a_VertexFormat)
			{
				vertexData.push_back(X); vertexData.push_back(Y); vertexData.push_back(Z);
			}
			// texture
			if (EVertexFormat_Texture_0 & a_VertexFormat)
			{
				vertexData.push_back(U);  vertexData.push_back(V);
			}
		}
	}

	// Now generate the index buffer
	std::vector<uint32_t> indexData;
	for (int i = 0; i < a_Slices * a_Stacks + a_Slices; ++i)
	{
		indexData.push_back(i);
		indexData.push_back(i + a_Slices + 1);
		indexData.push_back(i + a_Slices);

		indexData.push_back(i + a_Slices + 1);
		indexData.push_back(i);
		indexData.push_back(i + 1);
	}

// 	GFXVertexBufferDescriptor vertexBufferDescriptor;
// 	vertexBufferDescriptor.m_Usage = Usage_Default;
// 	vertexBufferDescriptor.m_Vertices = &vertexData[0];
// 	vertexBufferDescriptor.m_DataByteSize = static_cast<uint32_t>(vertexData.size() * sizeof(float));
// 	GFXCreateVertexBuffer(a_API, &vertexBufferDescriptor, &a_Mesh.m_VertexBuffer);
// 
// 	GFXIndexBufferDescriptor indexBufferDescriptor;
// 	indexBufferDescriptor.m_Indices = &indexData[0];
// 	indexBufferDescriptor.m_DataByteSize = indexData.size() * sizeof(uint32_t);
// 	indexBufferDescriptor.m_Usage = Usage_Default;
// 	GFXCreateIndexBuffer(a_API, &indexBufferDescriptor, &a_Mesh.m_IndexBuffer);
// 
// 	a_Mesh.m_NumIndices = static_cast<uint32_t>(indexData.size());
}