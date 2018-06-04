#pragma once

#include "Proto.h"

#include "Graphics/API/GFXIncludes.h"
#include "Platform/PlatformIncludes.h"
#include "Utility/NoCopy.h"

#include <functional>
#include <vector>

BEGIN_NAMESPACE(Platform)

typedef std::function<void(void)> InspectFunctionType;

class Inspector : public Utility::NoCopy
{
public:
	Inspector();
	virtual ~Inspector();

	void Initialize(GFXAPI a_Api);
	void BeginFrame(GFXAPI a_API, GFXCommandListHandle a_CommandList);
	void EndFrame();
	void Terminate();

	void Add(InspectFunctionType a_Function);

#if defined(PROTO_PLATFORM_WIN32)
	static bool AbsorbInput(NativeWindowHandle a_WindowHandle, UINT a_Msg, WPARAM a_WParam, LPARAM a_LParam);
#endif
private:
	std::vector<InspectFunctionType> m_Inspectables;
	static bool m_Initialized;
};

END_NAMESPACE(Platform)
