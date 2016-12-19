#ifndef DOOR_BRIDGE_H_
#define DOOR_BRIDGE_H_

#include <iostream>
#include <string>

#include "door_shared_memory/shared_memory.h"

class DoorBridge
{
public:
    DoorBridge();
    ~DoorBridge();
private:
    bool init();

    std::string baseShmKeyName_;
    std::string appShmKeyName_;

};

#endif

