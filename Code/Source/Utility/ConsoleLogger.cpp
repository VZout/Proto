#include "Utility/ConsoleLogger.h"

#include "Platform/Helpers/DateTimeFunctions.h"

#include <iostream>

USING_NAMESPACE(Platform)

BEGIN_NAMESPACE(Utility)

ConsoleLogger::ConsoleLogger()
{
}

ConsoleLogger::~ConsoleLogger()
{
}

void ConsoleLogger::WriteLine(const std::string &a_Line) const
{
	std::cout << "[" << GetDateTimeString() << "] " << a_Line << std::endl;
}

END_NAMESPACE(Utility)
