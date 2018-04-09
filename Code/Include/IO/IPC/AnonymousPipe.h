#pragma once

#include "Pipe.h"

#include <windows.h>

BEGIN_NAMESPACE(IO)

struct PipeCreateParameters;

class AnonymousPipe : public Pipe
{
public:
	AnonymousPipe(HANDLE a_PipeHandle, const PipeCreateParameters &a_Parameters);

	bool Connect() override { return false; }
};

END_NAMESPACE(IO)
