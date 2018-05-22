#include "SimpleScene.h"

#include "Graphics/Mesh.h"
#include "Graphics/Model.h"
#include "Resources/ResourceManager.h"
#include "Resources/Resources/MeshResource.h"
#include "Resources/Resources/ModelResource.h"
#include "Scene/ModelSceneNode.h"
#include "Scene/SceneGraph.h"
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
	a_ResourceManager.AddResource("BoxVertexColors\\glTF\\BoxVertexColors.gltf");

	ModelResource &modelResource = a_ResourceManager.GetResource<ModelResource>(HashedString("SimpleTriangle"));

	Model *model = new Model();
	Mesh *mesh = new Mesh();
	mesh->m_VertexBuffer = modelResource.m_Meshes[0]->m_VertexBuffer;
	model->m_Meshes.push_back(mesh);
	ModelSceneNode *modelSceneNode = new ModelSceneNode(*model);
	m_SceneGraph->AddNode(*modelSceneNode);

	GFXConstantBufferDescriptor constantBufferDescriptor;
	constantBufferDescriptor.m_ByteSize = sizeof(float) * 4;
	GFXConstantBufferHandle constantBufferHandle;
	GFXCreateConstantBuffer(m_API, &constantBufferDescriptor, &constantBufferHandle);
}
