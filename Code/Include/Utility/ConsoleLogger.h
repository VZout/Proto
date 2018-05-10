#pragma once

#include "Proto.h"

#include "Logger.h"

#include <string>

BEGIN_NAMESPACE(Utility)

class ConsoleLogger : public Logger
{
public:
	ConsoleLogger();
	virtual ~ConsoleLogger();

	
private:
	virtual void WriteLine(const std::string &a_Line) const OVERRIDE;
};

END_NAMESPACE(Utility)
