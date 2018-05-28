#pragma once

#include "Proto.h"

#include "../BaseLoader.h"
#include "../Resource.h"

#include <string>
#include <vector>

FORWARD_DECLARE(Utility, class Logger)

BEGIN_NAMESPACE(Resources)

class ShaderLoader : public BaseLoader
{
public:
	ShaderLoader(const std::string &a_Extensions, GFXAPI a_API);// , Utility::Logger &a_Logger);
	virtual ~ShaderLoader();

	virtual Resource* Load(const LoadParameters &a_Parameters/*, Memory::IMemoryPool &a_MemoryPool*/) const OVERRIDE;
	virtual const std::string GetAssetDirectoryName() const OVERRIDE;

private:
	std::vector <std::string> m_RegisteredLanguages;
};

END_NAMESPACE(Resources)