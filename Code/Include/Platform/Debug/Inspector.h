#pragma once

#include "Proto.h"

#include "Graphics/API/GFXIncludes.h"
#include "Platform/PlatformIncludes.h"
#include "Utility/NoCopy.h"

BEGIN_NAMESPACE(Platform)

class Inspector : public Utility::NoCopy
{
public:
	Inspector();
	virtual ~Inspector();

	void Initialize(GFXAPI a_Api, NativeWindowHandle a_WindowHandle);
	void BeginFrame();
	void EndFrame();
	void Terminate();

#if defined(PROTO_PLATFORM_WIN32)
	static bool AbsorbInput(NativeWindowHandle a_WindowHandle, UINT a_Msg, WPARAM a_WParam, LPARAM a_LParam);
#endif
};

END_NAMESPACE(Platform)
