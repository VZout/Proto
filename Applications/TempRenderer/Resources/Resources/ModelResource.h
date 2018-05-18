#pragma once

#include "..\Resource.h"
#include "Graphics\API\GFX.h"

BEGIN_NAMESPACE(Resources)

class ModelResource : public Resource
{
public:
	ModelResource()
		: Resource(EResourceType_Model)
	{
	}
};

END_NAMESPACE(Resources)
