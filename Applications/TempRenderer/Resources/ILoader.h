#pragma once

#include "Proto.h"

#include "Utility/NoCopy.h"

#include <string>
#include <vector>

FORWARD_DECLARE(Memory, class IMemoryPool)

BEGIN_NAMESPACE(Resources)

struct LoadParameters;
class Resource;

class ILoader : public Utility::NoCopy
{
public:
	virtual Resource* Load(const LoadParameters &a_Parameters/*, Memory::IMemoryPool &a_MemoryPool*/) const = 0;
	virtual const std::vector<std::string>& Handles() const = 0;
	virtual bool Handles(const std::string &a_Extension) const = 0;
	virtual const std::string GetAssetDirectoryName() const = 0;
};

END_NAMESPACE(Resources)
