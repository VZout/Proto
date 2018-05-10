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

#if defined(PROTO_CPP03)
#define NULLPTR 0
#define OVERRIDE
#define ENUM enum
#elif defined(PROTO_CPP11) or defined(PROTO_CPP14)
#define NULLPTR nullptr
#define OVERRIDE override
#define ENUM enum class
#endif
