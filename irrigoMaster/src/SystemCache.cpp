#include "SystemCache.h"

// Definition and initialization of the static member
char SystemCache::buffer[BUFFER_SIZE] = {0};

char *SystemCache::getBuffer()
{
    return buffer;
}

uint8_t SystemCache::getBufferSize()
{
    return BUFFER_SIZE;
}