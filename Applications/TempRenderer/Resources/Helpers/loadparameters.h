#pragma once

// #include "Memory/MemoryBuffer.h"
#include "../ResourceID.h"
// #include "Utility/Functors.h"

#include <string>

BEGIN_NAMESPACE(Resources)

class ILoader;
struct LoadParameters;

// typedef Utility::Functor<void(const ResourceID&)> LoadFinishedCallback;

struct LoadParameters
{
	LoadParameters()
	{
	}

	explicit LoadParameters(const std::string &a_Filename)
		: m_Filename(a_Filename)
	{
	}

// 	LoadParameters(const std::string &a_Filename, LoadFinishedCallback a_Callback)
// 		: m_Filename(a_Filename)
// 		, m_Callback(a_Callback)
// 	{
// 	}

	std::string m_Filename;
	ResourceID m_ResourceID;
	ILoader *m_Loader = nullptr;
// 	LoadFinishedCallback m_Callback;
// 	Memory::MemoryBuffer m_Buffer;
};

END_NAMESPACE(Resources)
