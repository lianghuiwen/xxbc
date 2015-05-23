#include <stdio.h>
#include <unistd.h>
#include "mempool.h"
using namespace xxbc;

int main(int argc, char* argv[])
{
    const int size = 1000;
    MemoryPool pool;
    Chunk* chunks[size];
    for (int i=0; i<size; ++i) {
        chunks[i] = pool.Malloc();
        printf("BlockCount=%d, FreeChunkCount=%d\n", pool.BlockCount(), pool.FreeChunkCount());
    }
    for (int i=0; i<5; ++i) {
        printf("%d\n", i+1);
        sleep(1);
    }
    for (int i=0; i<size; ++i) {
        pool.Free(chunks[i]);
        printf("BlockCount=%d, FreeChunkCount=%d\n", pool.BlockCount(), pool.FreeChunkCount());
    }
}
