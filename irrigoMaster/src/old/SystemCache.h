#ifndef SYSTEMCACHE_H
#define SYSTEMCACHE_H

#include <Arduino.h>
#include "ProjectConfig.h"

class SystemCache
{
private:
    static char buffer[BUFFER_SIZE]; // Adjust the size based on your needs

public:
    static char *getBuffer();
    static uint8_t getBufferSize();
};

#endif // SYSTEMCACHE_H