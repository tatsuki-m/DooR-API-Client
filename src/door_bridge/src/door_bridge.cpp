#include "door_bridge.h"

DoorBridge::DoorBridge() {
    appBaseShmKey_ = "shmKey0000";
    doorShmKey_ = NULL;
    // shared memory for baseShmKkey
    init();
}

DoorBridge::~DoorBridge() {
    delete doorShmKey_;
}

bool
DoorBridge::init() {
    // init baseShmKey
    SharedMemory<char, SharedKey>* appBaseShmKey = new SharedMemory<char, SharedKey>(appBaseShmKey_);
    appBaseShmKey->read(&doorShmKey_);
    std::cout << doorShmKey_ << std::endl;
    return true;
}

