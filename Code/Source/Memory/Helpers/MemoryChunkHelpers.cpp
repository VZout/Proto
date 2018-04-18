#include "MemoryChunkHelpers.h"

BEGIN_NAMESPACE(Memory)

#if defined(_DEBUG)

const uint32_t g_HeaderGuardValue = ('T' << 24) | ('O' << 16) | ('R' << 8) | 'P';
const uint32_t g_FooterGuardValue = ('P' << 24) | ('R' << 16) | ('O' << 8) | 'T';

#endif

END_NAMESPACE(Memory)
