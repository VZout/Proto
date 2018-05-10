#pragma once

#include "Proto.h"

#include "Graphics/API/GFXIncludes.h"
#include "Resources/Helpers/ProcessModelData.h"
#include "Utility/NoCopy.h"

#include <vector>

FORWARD_DECLARE(Memory, class IMemoryPool)
FORWARD_DECLARE(Resources, struct ModelData)
FORWARD_DECLARE(Resources, class ResourceManager)

BEGIN_NAMESPACE(Graphics)

enum ERenderFlag
{
	ERenderFlag_Wireframe = 1 << 0,
	ERenderFlag_Invalid = -1
};

class Material;
class Model;

class Mesh : public Utility::NoCopy
{
public:
	Mesh();
	~Mesh();

	GFXIndexBufferHandle GetIndexBuffer() const;
	uint32_t GetNumIndices() const;
	GFXVertexBufferHandle GetVertexBuffer() const;

	void SetMaterial(Material *a_Material);
	bool HasMaterial() const;
	Material& GetMaterial();
	const Material& GetMaterial() const;

	void SetRenderFlag(ERenderFlag a_RenderFlag);
	uint32_t GetRenderFlags() const;

private:
	GFXIndexBufferHandle m_IndexBuffer;
	uint32_t m_NumIndices;
	GFXVertexBufferHandle m_VertexBuffer;
	Material *m_Material;					// material part of mesh or model?
	uint32_t m_RenderFlags = 0;

	friend class ForwardRenderer;
	friend class Model;
	friend Model* Resources::ProcessModelData(const Resources::ModelData&, GFXAPI, Memory::IMemoryPool&, Resources::ResourceManager&);
};

typedef std::vector<Mesh*> MeshVector;

END_NAMESPACE(Graphics)
