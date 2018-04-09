#pragma once

#include "Proto.h"
#include "Utility/NoCopy.h"

BEGIN_NAMESPACE(IO)

class Pipe;
struct PipeCreateParameters;

class PipeClient : public Utility::NoCopy
{
public:
	PipeClient();
	~PipeClient();

	void Initialize(const PipeCreateParameters &a_Parameters);
	void Start();

private:
	Pipe *m_Pipe = nullptr;
};

END_NAMESPACE(IO)
