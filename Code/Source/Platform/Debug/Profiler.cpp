#include "Profiler.h"

#include "AssertMessage.h"

BEGIN_NAMESPACE(Platform)

BEGIN_UNNAMEDNAMESPACE()

Profiler *g_Profiler = nullptr;

void PushNamedProfileMarker(const char *a_Name)
{
	AssertMessage(nullptr != g_Profiler, "Attempt to use an invalid profiler!");
	g_Profiler->PushNamedMarker(a_Name, EProfileMarker_CPU);
}

void PopNamedProfileMarker(const char *a_Name)
{
	AssertMessage(nullptr != g_Profiler, "Attempt to use an invalid profiler!");
	g_Profiler->PopNamedMarker(a_Name, EProfileMarker_CPU);
}

END_UNNAMEDNAMESPACE()

Profiler::Profiler()
{
}

Profiler::~Profiler()
{
}

void Profiler::PushNamedMarker(const std::string &a_Name, EProfileMarker a_Type)
{
	ProfileMarker *marker = new ProfileMarker(a_Name, a_Type);
	switch (a_Type)
	{
	case EProfileMarker_CPU:
		{
			m_CPUMarkers.push(marker);
			break;
		}
	case EProfileMarker_GPU:
		{
			m_GPUMarkers.push(marker);
			break;
		}
	default:
		{
			AssertMessage("Invalid profile marker type encountered!");
			break;
		}
	}
}

void Profiler::PopNamedMarker(const std::string &a_Name, EProfileMarker a_Type)
{
	std::queue<ProfileMarker*> *queue = nullptr;
	switch (a_Type)
	{
	case EProfileMarker_CPU:
		{
			queue = &m_CPUMarkers;
			break;
		}
	case EProfileMarker_GPU:
		{
			queue = &m_GPUMarkers;
			break;
		}
	default:
		{
			AssertMessage("Invalid profile marker type encountered!");
			break;
		}
	}
	ProfileMarker *marker = queue->front();
	AssertMessage(a_Name == marker->m_Name, "Top profile marker does not match marker to pop!");
	queue->pop();
}

END_NAMESPACE(Platform)
