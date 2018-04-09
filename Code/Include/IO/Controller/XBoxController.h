#pragma once

#include "Proto.h"
#include "ControllerBase.h"
#include "ControllerState.h"
#include "Platform/PlatformIncludes.h"

#include "Utility/Functors.h"

#if defined(PROTO_PLATFORM_WIN32)
#include <Xinput.h>
#elif defined(PROTO_PLATFORM_RASPBERRY_PI)
#endif

BEGIN_NAMESPACE(IO)

class XBoxController : public ControllerBase
{
public:
	XBoxController(float a_DeadZoneX = 0.15f, float a_DeadZoneY = 0.15f);
	virtual ~XBoxController();

	virtual void Update(const Utility::UpdateEvent &a_UpdateEvent) override;

private:
#if defined(PROTO_PLATFORM_WIN32)
	bool m_Connected[XUSER_MAX_COUNT];
	ControllerState m_State[XUSER_MAX_COUNT];
	ControllerState m_PrevState[XUSER_MAX_COUNT];
#elif defined(PROTO_PLATFORM_RASPBERRY_PI)
#endif
	float m_DeadZoneX;
	float m_DeadZoneY;
};

END_NAMESPACE(IO)

#if defined(PROTO_PLATFORM_WIN32)
#pragma comment(lib, "Xinput9_1_0")
#elif defined(PROTO_PLATFORM_RASPBERRY_PI)
#endif
