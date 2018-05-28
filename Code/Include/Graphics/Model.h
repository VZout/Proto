#pragma once

#include "Mesh.h"
#include <vector>

BEGIN_NAMESPACE(Graphics)

class Model
{
public:
	Model();
	virtual ~Model();

	bool HasMeshes() const;
	MeshVector& GetMeshes();
	const MeshVector& GetMeshes() const;

	std::vector<Mesh*> m_Meshes;
};

END_NAMESPACE(Graphics)

// #include "Graphics/API/GFXIncludes.h"
// #include "Graphics/Mesh.h"
// #include "Resources/Helpers/ProcessModelData.h"
// #include "Resources/Resource.h"
// #include "Utility/IUpdatable.h"
// 
// #include <vector>
// 
// FORWARD_DECLARE(Memory, class IMemoryPool)
// FORWARD_DECLARE(Resources, struct ModelData)
// FORWARD_DECLARE(Resources, class ResourceManager)
// 
// BEGIN_NAMESPACE(Graphics)
// 
// class Mesh;
// struct Shader;
// 
// class Model : public Resources::Resource, public Utility::IUpdatable
// {
// public:
// 	Model();
// 	virtual ~Model();
// 
// 	void Update(const Utility::UpdateEvent &a_UpdateEvent) override;
// 
// 	bool HasMeshes() const;
// 	MeshVector& GetMeshes();
// 	const MeshVector& GetMeshes() const;
// 
// 	virtual bool IsAnimated() const;
// 	uint32_t GetVertexFormat() const;
// 
// private:
// 	std::vector<Mesh*> m_Meshes;
// 	uint32_t m_VertexFormat = 0;
// 
// 	friend class ForwardRenderer;
// 	friend Model* Resources::ProcessModelData(const Resources::ModelData&, GFXAPI, Memory::IMemoryPool&, Resources::ResourceManager&);
// };
// 
// typedef std::vector<Model*> ModelVector;
// 
// END_NAMESPACE(Graphics)
