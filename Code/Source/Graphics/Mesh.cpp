#include "Mesh.h"

#include "Material.h"
#include "Platform/Debug/AssertMessage.h"

USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Graphics)

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
	GFXDestroyVertexBuffer(NULLPTR, m_VertexBuffer);
	GFXDestroyIndexBuffer(NULLPTR, m_IndexBuffer);
// 	delete m_Material;
}

// GFXIndexBufferHandle Mesh::GetIndexBuffer() const
// {
// 	return m_IndexBuffer;
// }
// 
// uint32_t Mesh::GetNumIndices() const
// {
// 	return m_NumIndices;
// }
// 
// GFXVertexBufferHandle Mesh::GetVertexBuffer() const
// {
// 	return m_VertexBuffer;
// }
// 
// void Mesh::SetMaterial(Material *a_Material)
// {
// 	AssertMessage(nullptr != a_Material, "Attempt to set an invalid material!");
// 	m_Material = a_Material;
// }
// 
// bool Mesh::HasMaterial() const
// {
// 	return nullptr != m_Material;
// }
// 
// Material& Mesh::GetMaterial()
// {
// 	return const_cast<Material&>(const_cast<const Mesh*>(this)->GetMaterial());
// }
// 
// const Material& Mesh::GetMaterial() const
// {
// 	AssertMessage(nullptr != m_Material, "Attempt to retrieve an invalid material!");
// 	return *m_Material;
// }
// 
// void Mesh::SetRenderFlag(ERenderFlag a_RenderFlag)
// {
// 	m_RenderFlags |= a_RenderFlag;
// }
// 
// uint32_t Mesh::GetRenderFlags() const
// {
// 	return m_RenderFlags;
// }

END_NAMESPACE(Graphics)
