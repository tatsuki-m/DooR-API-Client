#ifndef SHARED_MEMORY_H_
#define SHARED_MEMORY_H_

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

using namespace boost::interprocess;

class SharedMemory
{
    struct SharedMemoryBuffer {
        SharedMemoryBuffer(): writer(1), reader(0) {}
        interprocess_semaphore writer, reader;
        char appShmKey[16];
    };

public:
    SharedMemory(std::string);
    ~SharedMemory();
    std::string init();

private:
    SharedMemoryBuffer *m_sharedMemoryBuffer;
    const char* m_sharedMemoryName_;
};

#endif

