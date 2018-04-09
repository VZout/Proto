#pragma once

#include "Proto.h"

#include <string>

BEGIN_NAMESPACE(IO)

void WriteToNamedPipe(const std::string &a_PipeName, const std::string &a_Data);

END_NAMESPACE(IO)
