#ifndef DOOR_H_
#define DOOR_H_

#include <iostream>
#include <string>

#include "door_shared_memory.h"
#include "shared_memory.h"

class Door
{
public:
    Door();
    ~Door();
private:
    bool init();

    std::string baseShmKeyName_;
    std::string appShmKeyName_;

    DoorSharedMemory* appShmKey_;
};

#endif

