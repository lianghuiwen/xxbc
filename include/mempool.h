#ifndef XXBC_MEMPOOL_H_
#define XXBC_MEMPOOL_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

namespace xxbc {

const int kChunkSize = 1024 * 8;
const int kBlockSize = kChunkSize * 256;

class MemoryPool;

struct Chunk {
    uint32_t used_size;
    uint32_t free_size;
    char* data;
    Chunk* next;
};

struct Block {
    char data[kBlockSize];
    Block* next;
};

// not thread safe
class MemoryPool {
public:
    MemoryPool(void);
    ~MemoryPool(void);

    Chunk* Malloc();
    void Free(Chunk* chunk);

    int BlockCount();
    int FreeChunkCount();

private:
    void MallocBlock();

private:
    Block* block_list_;
    Chunk* free_chunk_list_;
};

} // namespace xxbc

#endif
