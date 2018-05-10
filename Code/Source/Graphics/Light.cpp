#include "Light.h"

#include "Platform/Debug/AssertMessage.h"

// USING_NAMESPACE(Math);
// USING_NAMESPACE(Platform);
// USING_NAMESPACE(Utility);
// 
// BEGIN_NAMESPACE(Graphics)
// 
// Light::Light(const LightParameters &a_Parameters)
// 	: m_Type(a_Parameters.m_Type)
// 	, m_Direction(a_Parameters.m_Direction)
// 	, m_Position(a_Parameters.m_Position)
// 	, m_Color(a_Parameters.m_Color)
// 	, m_SpotAngle(a_Parameters.m_SpotAngle)
// 	, m_Attenuation(a_Parameters.m_Attenuation)
// {
// }
// 
// Light::~Light()
// {
// }
// 
// ELightType Light::GetLightType() const 
// {
// 	return m_Type;
// }
// 
// const Vector3& Light::GetDirection() const
// {
// 	AssertMessage(ELightType_Spot == m_Type || ELightType_Directional == m_Type, "Current light type does not have a direction!");
// 	return m_Direction;
// }
// 
// const Vector3& Light::GetPosition()const
// {
// 	AssertMessage(ELightType_Spot == m_Type || ELightType_Point == m_Type, "Current light type does not have a position!");
// 	return m_Position;
// }
// 
// const Color& Light::GetColor()const
// {
// 	return m_Color;
// }
// 
// float Light::GetSpotAngle() const
// {
// 	AssertMessage(ELightType_Spot == m_Type, "Only spotlights have spot angles!");
// 	return m_SpotAngle;
// }
// 
// float Light::GetAttenuation() const
// {
// 	AssertMessage(ELightType_Spot == m_Type || ELightType_Point == m_Type, "Current light type does not have an attenuation!");
// 	return m_Attenuation;
// }
// 
// END_NAMESPACE(Graphics)
