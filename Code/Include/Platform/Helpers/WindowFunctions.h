#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Platform)

class IWindowApplication;

void SetWindowApplication(Platform::IWindowApplication &a_Application);
bool HasWindowApplication();
Platform::IWindowApplication& GetWindowApplication();
void ReleaseWindowApplication();

END_NAMESPACE(Platform)
