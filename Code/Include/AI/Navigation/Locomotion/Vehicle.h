#pragma once

#include "Proto.h"

#include "Math/Vector2.h"
#include "Utility/IUpdatable.h"
#include "Utility/NoCopy.h"

BEGIN_NAMESPACE(AI)

class Vehicle : public Utility::IUpdatable, public Utility::NoCopy
{
public:
	Vehicle();
	~Vehicle();

	void Update(const Utility::UpdateEvent &a_UpdateEvent) override;

	void SetMass(float a_Mass);
	float SetMass() const;
	void SetPosition(const Math::Vector2 &a_Position);
	const Math::Vector2& GetPosition() const;
	void SetVelocity(const Math::Vector2 &a_Velocity);
	const Math::Vector2& GetVelocity() const;
	void SetMaxForce(float a_MaxForce);
	float GetMaxForce() const;
	void SetMaxSpeed(float a_MaxSpeed);
	float GetMaxSpeed() const;
	void SetHeading(float a_Heading);
	float GetHeading() const;

private:
	float m_Mass;
	Math::Vector2 m_Position;
	Math::Vector2 m_Velocity;
	float m_MaxForce;
	float m_MaxSpeed;
	float m_Heading;
};

END_NAMESPACE(AI)
