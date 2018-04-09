#pragma once

#include "Proto.h"

#include "EDisplayResolution.h"

FORWARD_DECLARE(Math, struct Dimension)
FORWARD_DECLARE(Utility, class HashedString)

BEGIN_NAMESPACE(Platform)

EDisplayResolution TranslateDisplayResolution(const Utility::HashedString &a_Resolution);
void GetDisplaySize(EDisplayResolution a_Resolution, Math::Dimension &a_Dimension);
void GetDisplaySize(EDisplayResolution a_Resolution, uint32_t &a_Width, uint32_t &a_Height);

END_NAMESPACE(Platform)
