#ifndef SHARED_MEMORY_H_
#define SHARED_MEMORY_H_

#include <iostream>
#include <string>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

using namespace boost::interprocess;

class SharedMemory
{

struct SharedSt {
    int value;
    double valueFloat;
};

public:
    SharedMemory(std::string);
    ~SharedMemory();
    bool init();
    bool setStruct();

    SharedSt m_sharedSt_;

private:
    char m_sharedMemoryName_[32];
    managed_shared_memory *m_shm_;

};

#endif

