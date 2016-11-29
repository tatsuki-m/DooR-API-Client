#ifndef DOOR_API_H_
#define DOOR_API_H_

#include <iostream>

#include "shared_memory.h"

class DoorApi
{

public:
    DoorApi();
    ~DoorApi();
    static std::string shmKey:
private:
    SharedMemory *shm_;
};

#endif

