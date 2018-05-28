#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Resources)

enum EResourceType
{
	EResourceType_DataBlob,
	EResourceType_Material,
	EResourceType_Mesh,
	EResourceType_Model,
	EResourceType_Package,
	EResourceType_Script,
	EResourceType_Shader,
	EResourceType_Sound,
	EResourceType_Texture,
	EResourceType_Tilemap,

	EResourceType_Invalid
};

END_NAMESPACE(Resources)
