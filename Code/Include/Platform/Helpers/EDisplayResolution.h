#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Platform)

enum EDisplayResolution
{
	EDisplayResolution_HVGA,		//  480 x  320
	EDisplayResolution_VGA,			//  640 x  480
	EDisplayResolution_SVGA,		//  800 x  600
	EDisplayResolution_DVGA,		//  960 x  640
	EDisplayResolution_XGA,			// 1024 x  768
	//EDisplayResolution_1136x640,
	EDisplayResolution_WXGA16x9,	// 1280 x  720
	EDisplayResolution_WXGA5x3,		// 1280 x  768
	EDisplayResolution_WSXGAPlus,	// 1680 x 1050
	EDisplayResolution_FullHD,		// 1920 x 1080
	EDisplayResolution_QXGA,		// 2048 x 1536
	EDisplayResolution_Invalid
};

END_NAMESPACE(Platform)
