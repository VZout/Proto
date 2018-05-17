#pragma once

#include "Proto.h"

#include "../BaseLoader.h"

#include <string>
#include <vector>

FORWARD_DECLARE(Utility, class Logger)

BEGIN_NAMESPACE(Resources)

class ShaderLoader : public BaseLoader
{
public:
	ShaderLoader(const std::string &a_Extensions, Utility::Logger &a_Logger);
	virtual ~ShaderLoader();

	virtual ResourceData* Load(const LoadParameters &a_Parameters, Memory::MemoryPool &a_MemoryPool) const override;
	//virtual const std::string GetAssetDirectoryName() const override;

private:
	std::vector <std::string> m_RegisteredLanguages;
};

END_NAMESPACE(Resources)
