#pragma once

#include "Proto.h"

#include <string>

BEGIN_NAMESPACE(IO)

uint64_t GetFileLastChangeTime(const std::string &a_Filename);

END_NAMESPACE(IO)
