#pragma once

#pragma comment(lib, "bson-static-1.0.lib")
#pragma comment(lib, "Ws2_32.lib")

#pragma warning(push)
#pragma warning(disable : 4324)

#define BSON_STATIC
#define MONGOC_STATIC

#include <bson.h>

#pragma warning(pop)
