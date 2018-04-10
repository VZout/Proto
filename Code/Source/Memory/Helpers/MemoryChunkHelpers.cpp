#include "MemoryChunkHelpers.h"

#include "MemoryChunk.h"

BEGIN_NAMESPACE(Memory)

const uint32_t g_MemoryChunkSize = sizeof(MemoryChunk);

#if defined(_DEBUG)

const uint32_t g_HeaderGuardValue = ('T' << 24) | ('O' << 16) | ('R' << 8) | 'P';
const uint32_t g_FooterGuardValue = ('P' << 24) | ('R' << 16) | ('O' << 8) | 'T';
const uint32_t g_MemoryChunkGuardSize = sizeof(MemoryChunkGuard);

// void FillChunkPointers(void *a_Ptr, MemoryChunkGuard *&a_Header, MemoryChunk *&a_Chunk, MemoryChunkGuard *&a_Footer)
// {
// 	a_Chunk = reinterpret_cast<MemoryChunk*>(reinterpret_cast<char*>(a_Ptr) + g_MemoryChunkGuardSize);
// 	a_Header = GetHeaderGuard(a_Chunk);
// 	a_Footer = GetFooterGuard(a_Chunk, a_Chunk->m_ByteSize);
// }
#endif

// uint32_t CalculateMemoryBlockSize(const uint32_t a_RequestedSize)
// {
// #if defined(_DEBUG)
// 	return g_MemoryChunkSize + a_RequestedSize + (2 * g_MemoryChunkGuardSize);
// #else
// 	return g_MemoryChunkSize + a_RequestedSize;
// #endif
// }

// MemoryChunk* CalculateNextMemoryChunkPtr(MemoryChunk *a_MemoryChunk, const uint32_t a_RequestedSize)
// {
// #if defined(_DEBUG)
// 	return reinterpret_cast<MemoryChunk*>(reinterpret_cast<char*>(a_MemoryChunk) + g_MemoryChunkSize + a_RequestedSize + (2 * g_MemoryChunkGuardSize));
// #else
// 	return reinterpret_cast<MemoryChunk*>(reinterpret_cast<char*>(a_MemoryChunk) + g_MemoryChunkSize + a_RequestedSize);
// #endif
// }

END_NAMESPACE(Memory)
