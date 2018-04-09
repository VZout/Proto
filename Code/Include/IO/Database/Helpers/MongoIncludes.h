#pragma once

#pragma comment(lib, "mongoc-static-1.0.lib")
#pragma comment(lib, "bson-static-1.0.lib")

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Secur32.lib")
#pragma comment(lib, "Crypt32.lib")
#pragma comment(lib, "BCrypt.lib")
#pragma comment(lib, "Dnsapi.lib")

#pragma warning(push)
#pragma warning(disable : 4324)

#define BSON_STATIC
#define MONGOC_STATIC

#include <mongoc.h>

#pragma warning(pop)
