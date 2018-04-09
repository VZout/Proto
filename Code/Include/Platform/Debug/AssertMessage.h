#pragma once

#include "Proto.h"
#include "Platform/PlatformIncludes.h"
#include "Utility/String.h"

BEGIN_NAMESPACE(Platform)

void Assert(bool a_Condition);
void AssertMessage(const Utility::String &a_Text);
void AssertMessage(bool a_Condition, const Utility::String &a_Text);

END_NAMESPACE(Platform)
