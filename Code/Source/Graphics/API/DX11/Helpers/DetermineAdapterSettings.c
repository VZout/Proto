#include "DetermineAdapterSettings.h"

#include "Graphics/API/Defines.h"
#include "Graphics/API/DX11/DX11Includes.h"
#include "Graphics/API/DX11/Helpers/SafeRelease.h"

#include <assert.h>

#if defined(GFX_API_DX11)

void DetermineAdapterSettings(uint32_t a_Width, uint32_t a_Height, uint32_t *a_Numerator, uint32_t *a_Denominator, uint32_t *a_VideoCardMemory, char **a_VideoCardDescription)
{
	IDXGIFactory* factory = 0;
	HRESULT result = CreateDXGIFactory(&IID_IDXGIFactory, (void**)&factory);
	assert(S_OK == result);

	IDXGIAdapter* adapter;
	result = factory->lpVtbl->EnumAdapters(factory, 0, &adapter);
	assert(S_OK == result);

	IDXGIOutput* adapterOutput;
	result = adapter->lpVtbl->EnumOutputs(adapter, 0, &adapterOutput);
	assert(S_OK == result);

	uint32_t numModes = 0;
	result = adapterOutput->lpVtbl->GetDisplayModeList(adapterOutput, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, 0);
	assert(S_OK == result);

	DXGI_MODE_DESC* displayModeList = (DXGI_MODE_DESC*)malloc(numModes * sizeof(DXGI_MODE_DESC));
	assert(0 != displayModeList);

	result = adapterOutput->lpVtbl->GetDisplayModeList(adapterOutput, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	assert(0 != displayModeList);

	for (uint32_t currentMode = 0; currentMode < numModes; currentMode++)
	{
		if (displayModeList[currentMode].Width == a_Width)
		{
			if (displayModeList[currentMode].Height == a_Height)
			{
				*a_Numerator = displayModeList[currentMode].RefreshRate.Numerator;
				*a_Denominator = displayModeList[currentMode].RefreshRate.Denominator;
			}
		}
	}

	DXGI_ADAPTER_DESC adapterDesc;
	result = adapter->lpVtbl->GetDesc(adapter, &adapterDesc);
	assert(S_OK == result);

	*a_VideoCardMemory = (uint32_t)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	size_t stringLength = 0;
	char videoCardDescription[128];
	const int error = wcstombs_s(&stringLength, videoCardDescription, 128, adapterDesc.Description, 128);
#if !defined(NDEBUG)
	assert(0 == error);
#else
	GFX_UNUSED(error);
#endif
	*a_VideoCardDescription = malloc(stringLength);
	strcpy_s(*a_VideoCardDescription, stringLength, videoCardDescription);

	free(displayModeList);
	displayModeList = 0;

	SAFERELEASE(adapterOutput);
	SAFERELEASE(adapter);
	SAFERELEASE(factory);
}

#endif
