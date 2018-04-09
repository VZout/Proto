#include "Utility/String.h"

BEGIN_NAMESPACE(Utility)

String::String()
{
}

String::String(const char *a_String)
	: BasicString(a_String)
{
}

String::~String()
{
}

END_NAMESPACE(Utility)
