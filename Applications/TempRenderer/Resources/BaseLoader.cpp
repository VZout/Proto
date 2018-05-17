#include "BaseLoader.h"

#include "Platform/Helpers/StringFunctions.h"

#include <algorithm>
#include <iterator>
#include <cctype>

USING_NAMESPACE(Platform)
USING_NAMESPACE(Utility)

BEGIN_NAMESPACE(Resources)

BaseLoader::BaseLoader(const std::string &a_Extensions, GFXAPI a_API)
	: m_API(a_API)
{
	m_Extensions = Tokenize(a_Extensions, ";");
	for (auto &extension : m_Extensions)
	{
		std::transform(extension.begin(), extension.end(), extension.begin(),
			[](unsigned char a_Char) -> unsigned char { return static_cast<unsigned char>(std::toupper(a_Char)); });
	}
}

BaseLoader::~BaseLoader()
{
}

const std::vector<std::string>& BaseLoader::Handles() const
{
	return m_Extensions;
}

bool BaseLoader::Handles(const std::string &a_Extension) const
{
	return m_Extensions.end() != std::find(m_Extensions.begin(), m_Extensions.end(), a_Extension);
}

// Logger& BaseLoader::GetLogger() const
// {
// 	return m_Logger;
// }

END_NAMESPACE(Resources)
