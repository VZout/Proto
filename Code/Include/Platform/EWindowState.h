#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Platform)

enum EWindowState
{
	EWindowState_ForceMinimize,
	EWindowState_Hide,
	EWindowState_Maximize,
	EWindowState_Minimize,
	EWindowState_Restore,
	EWindowState_Show,
	EWindowState_Default,
	EWindowState_Maximized,
	EWindowState_Minimized,
	EWindowState_MinNoActive,
	EWindowState_NA,
	EWindowState_NoActive,
	EWindowState_Normal,

	EWindowState_Invalid
};

END_NAMESPACE(Platform)
