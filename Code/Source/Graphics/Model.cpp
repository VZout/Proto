#include "Model.h"

#include "Mesh.h"
#include "Utility/ClearContainerContents.h"

USING_NAMESPACE(Utility)

BEGIN_NAMESPACE(Graphics)

Model::Model()
{
}

Model::~Model()
{
	ClearContainerContents(m_Meshes);
}

// void Model::Update(const Utility::UpdateEvent &a_UpdateEvent)
// {
// 	UNUSED(a_UpdateEvent);
// }
// 
bool Model::HasMeshes() const
{
	return !m_Meshes.empty();
}

MeshVector& Model::GetMeshes()
{
	return const_cast<MeshVector&>(const_cast<const Model*>(this)->GetMeshes());
}

const MeshVector& Model::GetMeshes() const
{
	return m_Meshes;
}

// bool Model::IsAnimated() const
// {
// 	return false;
// }
// 
// uint32_t Model::GetVertexFormat() const
// {
// 	return m_VertexFormat;
// }
// 
END_NAMESPACE(Graphics)
