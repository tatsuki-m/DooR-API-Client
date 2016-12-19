#include "door_bridge.h"

DoorBridge::DoorBridge() {
    baseShmKeyName_ = "shmKey0000";
    // shared memory for baseShmKkey
    init();
}

DoorBridge::~DoorBridge() {
}

bool
DoorBridge::init() {
    // init baseShmKey
    // SharedMemory* baseShmKey = new SharedMemory(baseShmKeyName_);
    // std::string bridgeShmKeyName = baseShmKey->initRead();
    // init bridgeShmKey
    // SharedMemory* bridgeShmKey = new SharedMemory(bridgeShmKeyName);
    // std::string appShmKeyName_ = bridgeShmKey->initRead();
    // std::cout << appShmKeyName_ << std::endl;
    return true;
}

