#pragma once

#if defined(GFX_API_DX12)

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "D3DCompiler")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")

#pragma warning( push )
#pragma warning( disable : 4201 )
#pragma warning( disable : 4115 )

#include <d3d12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>

#pragma warning( pop )

#endif
