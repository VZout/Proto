#include "CreateController.h"

#include "IController.h"
#include "Platform/Debug/AssertMessage.h"
#include "XBoxController.h"

USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(IO)

ControllerBase* CreateController(EController a_Controller)
{
	ControllerBase *controller = nullptr;

	switch (a_Controller)
	{
	case IO::EController_XBox:
		{
			controller = new XBoxController();
			break;
		}
	case IO::EController_Invalid:
	default:
		{
			AssertMessage("Invalid controller type encountered!");
			break;
		}
	}
	AssertMessage(nullptr != controller, "Failed to create controller!");
	return controller;
}

END_NAMESPACE(IO)
