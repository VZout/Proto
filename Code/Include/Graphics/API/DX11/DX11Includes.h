#pragma once

#if defined(GFX_API_DX11)

#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")

#pragma warning(push)
#pragma warning(disable : 4201)
#pragma warning(disable : 4115)

#define D3D11_NO_HELPERS

#include <dxgi.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#include <d3d11.h>

#pragma warning(pop)

#endif
