#pragma once

#include "Proto.h"

#include "../BaseLoader.h"
#include "../Resource.h"

#include <string>
#include <vector>

BEGIN_NAMESPACE(Resources)

class ModelLoader : public BaseLoader
{
public:
	ModelLoader(const std::string &a_Extensions, GFXAPI a_API);
	virtual ~ModelLoader();

	virtual Resource* Load(const LoadParameters &a_Parameters) const OVERRIDE;
	virtual const std::string GetAssetDirectoryName() const OVERRIDE;
};

END_NAMESPACE(Resources)
