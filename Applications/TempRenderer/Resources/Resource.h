#pragma once

#include "EResourceType.h"
#include "Utility/NoCopy.h"

BEGIN_NAMESPACE(Resources)

class Resource : public Utility::NoCopy
{
public:
	Resource(Resources::EResourceType a_ResourceType)
		: m_Type(a_ResourceType)
	{
	}

	const Resources::EResourceType m_Type;
};

END_NAMESPACE(Resources)
