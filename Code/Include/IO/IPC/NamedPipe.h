#pragma once

#include "Pipe.h"

#include <string>
#include <windows.h>

BEGIN_NAMESPACE(IO)

struct PipeCreateParameters;

class NamedPipe : public Pipe
{
public:
	~NamedPipe();

	bool Connect() override;

private:
	NamedPipe(HANDLE a_PipeHandle, const PipeCreateParameters &a_Parameters);
	
	friend NamedPipe* ConstructNamedPipe(const PipeCreateParameters&);
	friend NamedPipe* ConstructNamedPipeConnection(const PipeCreateParameters&);
};

void NamedPipeWrite(const std::string &a_PipeName, const std::string &a_Data);

END_NAMESPACE(IO)
