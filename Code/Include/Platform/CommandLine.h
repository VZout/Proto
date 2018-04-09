#pragma once

#include "Proto.h"
#include "Platform/Debug/AssertMessage.h"
#include "Utility/HashedString.h"
#include "Utility/LexicalCast.h"
#include "Utility/NoCopy.h"

#include <map>
#include <string>
#include <vector>

BEGIN_NAMESPACE(Platform)

class CommandLineParser;

class CommandLine : public Utility::NoCopy
{
public:
	~CommandLine();

	bool IsValid() const;
	bool HasOptionSet(const Utility::HashedString &a_Option) const;
	bool HasParameter(const Utility::HashedString &a_Parameter) const;

	template<typename TYPE>
	const TYPE GetParameter(const Utility::HashedString &a_Parameter) const
	{
		std::map<Utility::HashedString, std::string>::const_iterator pos = m_Parameters.find(a_Parameter);
		Platform::AssertMessage(pos != m_Parameters.end(), ("Parameter was not set!"));
		return Utility::LexicalCast<TYPE>(pos->second);
	}
	const std::string GetParameter(const Utility::HashedString &a_Parameter) const;


private:
	CommandLine();

	void SetOption(const Utility::HashedString &a_Option);
	void SetParameter(const Utility::HashedString &a_Option, const std::string &a_Value);

	std::vector<Utility::HashedString> m_Options;
	std::map<Utility::HashedString, std::string> m_Parameters;

	bool m_IsValid;

	friend class CommandLineParser;
};

END_NAMESPACE(Platform)
