#pragma once

#include "Proto.h"

#include <string>

BEGIN_NAMESPACE(IO)

std::string GetExtensionFromFilename(const std::string &a_Filename, bool a_ToUpper = false);

END_NAMESPACE(IO)
