#pragma once

#include "Proto.h"
#include "EController.h"

BEGIN_NAMESPACE(IO)

class ControllerBase;

ControllerBase* CreateController(EController a_Controller);

END_NAMESPACE(IO)
