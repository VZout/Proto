#pragma once

#include "Proto.h"

#include "ILoader.h"

#include <string>
#include <vector>

FORWARD_DECLARE(Utility, class Logger)

BEGIN_NAMESPACE(Resources)

class BaseLoader : public ILoader
{
public:
	BaseLoader(const std::string &a_Extensions, Utility::Logger &a_Logger);
	virtual ~BaseLoader();

	virtual const std::vector<std::string>& Handles() const override;
	virtual bool Handles(const std::string &a_Extension) const override;

protected:
	Utility::Logger& GetLogger() const;

private:
	std::vector<std::string> m_Extensions;
	Utility::Logger &m_Logger;
};

END_NAMESPACE(Resources)
