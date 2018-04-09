#include "TranslateDisplayResolution.h"

#include "Math/Dimension.h"
#include "Platform/Debug/AssertMessage.h"
#include "Utility/HashedString.h"

USING_NAMESPACE(Math)
USING_NAMESPACE(Utility)

BEGIN_UNNAMEDNAMESPACE()

const HashedString g_HVGA("HVGA");
const HashedString g_VGA("VGA");
const HashedString g_SVGA("SVGA");
const HashedString g_DVGA("DVGA");
const HashedString g_XGA("XGA");
const HashedString g_WXGA16x9("WXGA16x9");
const HashedString g_WXGA5x3("WXGA5x3");
const HashedString g_WSXGAPlus("WSXGAPlus");
const HashedString g_FullHD("FullHD");
const HashedString g_QXGA("QXGVA");

END_UNNAMEDNAMESPACE()

BEGIN_NAMESPACE(Platform)

EDisplayResolution TranslateDisplayResolution(const HashedString &a_Resolution)
{
	EDisplayResolution displayResolution = EDisplayResolution_Invalid;
	if (g_HVGA == a_Resolution)
	{
		displayResolution = EDisplayResolution_HVGA;
	}
	else if (g_VGA == a_Resolution)
	{
		displayResolution = EDisplayResolution_VGA;
	}
	else if (g_SVGA == a_Resolution)
	{
		displayResolution = EDisplayResolution_SVGA;
	}
	else if (g_DVGA == a_Resolution)
	{
		displayResolution = EDisplayResolution_DVGA;
	}
	else if (g_XGA == a_Resolution)
	{
		displayResolution = EDisplayResolution_XGA;
	}
	else if (g_WXGA16x9 == a_Resolution)
	{
		displayResolution = EDisplayResolution_WXGA16x9;
	}
	else if (g_WXGA5x3 == a_Resolution)
	{
		displayResolution = EDisplayResolution_WXGA5x3;
	}
	else if (g_WSXGAPlus == a_Resolution)
	{
		displayResolution = EDisplayResolution_WSXGAPlus;
	}
	else if (g_FullHD == a_Resolution)
	{
		displayResolution = EDisplayResolution_FullHD;
	}
	else if (g_QXGA == a_Resolution)
	{
		displayResolution = EDisplayResolution_QXGA;
	}
	else
	{
		AssertMessage("Invalid display resolution requested!");
	}
	return displayResolution;
}

void GetDisplaySize(EDisplayResolution a_Resolution, Math::Dimension &a_Dimension)
{
	GetDisplaySize(a_Resolution, a_Dimension.m_Width, a_Dimension.m_Height);
}

void GetDisplaySize(EDisplayResolution a_Resolution, uint32_t &a_Width, uint32_t &a_Height)
{
	switch (a_Resolution)
	{
	case EDisplayResolution_HVGA:
		{
			a_Width = 480;
			a_Height = 320;
			break;
		}
	case EDisplayResolution_VGA:
		{
			a_Width = 640;
			a_Height = 480;
			break;
		}
	case EDisplayResolution_SVGA:
		{
			a_Width = 800;
			a_Height = 600;
			break;
		}
	case EDisplayResolution_DVGA:
		{
			a_Width = 960;
			a_Height = 640;
			break;
		}
	case EDisplayResolution_XGA:
		{
			a_Width = 1024;
			a_Height = 768;
			break;
		}
	case EDisplayResolution_WXGA16x9:
		{
			a_Width = 1280;
			a_Height = 720;
			break;
		}
	case EDisplayResolution_WXGA5x3:
		{
			a_Width = 1280;
			a_Height = 768;
			break;
		}
	case EDisplayResolution_WSXGAPlus:
		{
			a_Width = 1680;
			a_Height = 1050;
			break;
		}
	case EDisplayResolution_FullHD:
		{
			a_Width = 1920;
			a_Height = 1080;
			break;
		}
	case EDisplayResolution_QXGA:
		{
			a_Width = 2048;
			a_Height = 1536;
			break;
		}
	case EDisplayResolution_Invalid:
	default:
		{
			AssertMessage("Unknown screen resolution requested!");
			break;
		}
	}
}

END_NAMESPACE(Platform)
