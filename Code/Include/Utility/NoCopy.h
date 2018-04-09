#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Utility)

class NoCopy
{
public:
    NoCopy() {}
    virtual ~NoCopy() {}

private:
    NoCopy(const NoCopy&);
    const NoCopy& operator=(const NoCopy&);
};

END_NAMESPACE(Utility)
