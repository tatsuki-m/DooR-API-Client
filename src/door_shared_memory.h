#ifndef DOOR_SHARED_MEMORY_H_
#define DOOR_SHARED_MEMORY_H_

#include <iostream>
#include <string>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

using namespace boost::interprocess;

class DoorSharedMemory
{
    struct SharedMemoryBuffer {
        SharedMemoryBuffer(): writer(1), reader(0) {}
        interprocess_semaphore writer, reader;
        char doorData[100];
    };

public:
    DoorSharedMemory(std::string);
    ~DoorSharedMemory();
    std::string init();

private:
    SharedMemoryBuffer *m_sharedMemoryBuffer;
    const char* m_sharedMemoryName_;
};


#endif

