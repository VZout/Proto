#include "LightSceneNode.h"

#include "Graphics/Light.h"

USING_NAMESPACE(Graphics)

LightSceneNode::LightSceneNode(Light &a_Light)
	: m_Light(a_Light)
{
}

LightSceneNode::~LightSceneNode()
{
}

Light& LightSceneNode::GetLight()
{
	return const_cast<Light&>(const_cast<const LightSceneNode*>(this)->GetLight());

}
const Light& LightSceneNode::GetLight() const
{
	return m_Light;
}
