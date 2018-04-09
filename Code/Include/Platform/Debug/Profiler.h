#pragma once

#include "Utility/NoCopy.h"

#include <queue>
#include <string>

#define PROTO_CPU_PROFILE_PUSH_NAMED_MARKER(a_Name) \
	PushNamedProfileMarker(a_Name, EProfileMarker_CPU);

#define PROTO_CPU_PROFILE_POP_NAMED_MARKER() \
	PopNamedProfileMarker(a_Name, EProfileMarker_CPU);

BEGIN_NAMESPACE(Platform)

enum EProfileMarker
{
	EProfileMarker_CPU,
	EProfileMarker_GPU
};

struct ProfileMarker
{
	ProfileMarker(const std::string &a_Name, EProfileMarker a_Type)
		: m_Name(a_Name)
		, m_Type(a_Type)
	{
	}

	const std::string m_Name;
	const EProfileMarker m_Type;
};

class Profiler : public Utility::NoCopy
{
public:
	Profiler();
	~Profiler();

	void PushNamedMarker(const std::string &a_Name, EProfileMarker a_Type);
	void PopNamedMarker(const std::string &a_Name, EProfileMarker a_Type);

private:
	std::queue<ProfileMarker*> m_CPUMarkers;
	std::queue<ProfileMarker*> m_GPUMarkers;
};

void PushNamedProfileMarker(const char *a_Name);
void PopNamedProfileMarker(const char *a_Name);

END_NAMESPACE(Platform)
