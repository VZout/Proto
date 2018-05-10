#pragma once

#include "Proto.h"

#include "Platform/PlatformIncludes.h"

BEGIN_NAMESPACE(Utility)

class Stopwatch
{
public:
    Stopwatch();
    ~Stopwatch();
    
    void Start();
    uint64_t GetElapsedTime();
    uint64_t GetTimeSinceStart() const;
    void End();
    void Reset();
    bool IsRunning() const;
    
    void WaitForTimePassed(double a_MilliSeconds);
private:
#if defined(PROTO_PLATFORM_WIN32)
	LARGE_INTEGER m_StartTime;
	LARGE_INTEGER m_LastQueryTime;
	LARGE_INTEGER m_Frequency;
#elif defined(PROTO_PLATFORM_RASPBERRY_PI)
	timeval m_StartTime;
	timeval m_LastQueryTime;
#elif defined(PROTO_PLATFORM_PSVITA) or defined(PROTO_PLATFORM_ORBIS)
	uint64_t m_StartTime;
	uint64_t m_LastQueryTime;
#endif

	bool m_FirstQuery;
    bool m_Running;
};

END_NAMESPACE(Utility)
