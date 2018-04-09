#pragma once

#define NOMINMAX
#undef max

#include <stddef.h>
#include <stdint.h>

#define BEGIN_NAMESPACE(x)  namespace x {
#define END_NAMESPACE(x)    }
#define FORWARD_DECLARE(x, y) namespace x { y; }

#define BEGIN_UNNAMEDNAMESPACE()    namespace {
#define END_UNNAMEDNAMESPACE()      }

#define USING_NAMESPACE(x)  using namespace x;

#define UNUSED(x) (void)x

typedef unsigned char byte;
