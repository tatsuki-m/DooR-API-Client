#ifndef DOOR_BRIDGE_H_
#define DOOR_BRIDGE_H_

#include <iostream>
#include <string>

#include "door_shared_memory/shared_memory.h"
#include "door_shared_memory/shared_key.h"

class DoorBridge
{
public:
    DoorBridge();
    ~DoorBridge();
private:
    bool init();
    std::string appBaseShmKey_;
    char* doorShmKey_;
};

#endif

