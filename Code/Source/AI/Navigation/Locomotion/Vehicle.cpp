#include "Vehicle.h"

USING_NAMESPACE(Math)
USING_NAMESPACE(Utility)

BEGIN_NAMESPACE(AI)

Vehicle::Vehicle()
	: m_Mass(1.0f)
	, m_Position(Vector2::ORIGIN)
	, m_Velocity(Vector2::ORIGIN)
	, m_MaxForce(1.0f)
	, m_MaxSpeed(1.0f)
	, m_Heading(0.0f)
{
}

Vehicle::~Vehicle()
{
}

void Vehicle::Update(const UpdateEvent &a_UpdateEvent)
{
	UNUSED(a_UpdateEvent);
}

void Vehicle::SetMass(float a_Mass)
{
	m_Mass = a_Mass;
}

float Vehicle::SetMass() const
{
	return m_Mass;
}

void Vehicle::SetPosition(const Math::Vector2 &a_Position)
{
	m_Position = a_Position;
}

const Math::Vector2& Vehicle::GetPosition() const
{
	return m_Position;
}

void Vehicle::SetVelocity(const Math::Vector2 &a_Velocity)
{
	m_Velocity = a_Velocity;
}

const Math::Vector2& Vehicle::GetVelocity() const
{
	return m_Velocity;
}

void Vehicle::SetMaxForce(float a_MaxForce)
{
	m_MaxForce = a_MaxForce;
}

float Vehicle::GetMaxForce() const
{
	return m_MaxForce;
}

void Vehicle::SetMaxSpeed(float a_MaxSpeed)
{
	m_MaxSpeed = a_MaxSpeed;
}

float Vehicle::GetMaxSpeed() const
{
	return m_MaxSpeed;
}

void Vehicle::SetHeading(float a_Heading)
{
	m_Heading = a_Heading;
}

float Vehicle::GetHeading() const
{
	return m_Heading;
}

END_NAMESPACE(AI)
