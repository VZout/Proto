#include "ApplicationLoop.h"

#include "Platform/PlatformIncludes.h"

BEGIN_NAMESPACE(Platform)

bool ApplicationLoop()
{
	bool result = true;

	MSG msg;
	::ZeroMemory(&msg, sizeof(msg));
	while (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (WM_QUIT == msg.message || WM_DESTROY == msg.message || WM_CLOSE == msg.message)
		{
			result = false;
		}
	}

	return result;
}

END_NAMESPACE(Platform)
