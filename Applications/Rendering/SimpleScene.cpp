#include "SimpleScene.h"

#include "Graphics/Mesh.h"
#include "Graphics/Model.h"
#include "Resources/ResourceManager.h"
#include "Resources/Resources/MeshResource.h"
#include "Resources/Resources/ModelResource.h"
#include "Graphics/Scene/ModelSceneNode.h"
#include "Graphics/Scene/SceneGraph.h"
#include "Utility/HashedString.h"

USING_NAMESPACE(Graphics)
USING_NAMESPACE(Resources)
USING_NAMESPACE(Utility)

SimpleScene::SimpleScene(GFXAPI a_API)
	: Scene(a_API, HashedString("SimpleScene"))
{
}

SimpleScene::~SimpleScene()
{
}

void SimpleScene::Initialize(ResourceManager &a_ResourceManager)
{
	//a_ResourceManager.AddResource("BoxVertexColors\\glTF\\BoxVertexColors.gltf");

	ModelResource &modelResource = a_ResourceManager.GetResource<ModelResource>(HashedString("SimpleTriangle"));

	Model *model = new Model();
	Mesh *mesh = new Mesh();
	mesh->m_VertexBuffer = modelResource.m_Meshes[0]->m_VertexBuffer;
	model->m_Meshes.push_back(mesh);
	ModelSceneNode *modelSceneNode = new ModelSceneNode(*model);
	m_SceneGraph->AddNode(*modelSceneNode);

	GFXConstantBufferDescriptor constantBufferDescriptor;
	constantBufferDescriptor.m_ByteSize = sizeof(float) * 4;	
	GFXCreateConstantBuffer(m_API, &constantBufferDescriptor, &m_ConstantBuffer);

	m_BufferData.m_Offset[0] = 0.0f;
	m_BufferData.m_Offset[1] = 0.0f;
	m_BufferData.m_Offset[2] = 0.0f;
	m_BufferData.m_Offset[3] = 1.0f;
}

void SimpleScene::Update(const Utility::UpdateEvent &a_UpdateEvent)
{
	UNUSED(a_UpdateEvent);

	const float translationSpeed = 0.005f;
	const float offsetBounds = 1.25f;

	m_BufferData.m_Offset[0] += translationSpeed;
	if (m_BufferData.m_Offset[0] > offsetBounds)
	{
		m_BufferData.m_Offset[0] = -offsetBounds;
	}

	//GFXWriteConstantBufferData(m_API, m_CommandList, m_ConstantBuffer, &m_BufferData, 4 * sizeof(float));
}

void SimpleScene::Terminate()
{
	GFXDestroyConstantBuffer(m_API, m_ConstantBuffer);
}