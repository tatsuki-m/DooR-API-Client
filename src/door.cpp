#include "door.h"

Door::Door() {
    baseShmKeyName_ = "shmKey0000";
    // shared memory for baseShmKkey
    init();
}

Door::~Door() {
}

bool
Door::init() {
    // init baseShmKey
    // SharedMemory* baseShmKey = new SharedMemory(baseShmKeyName_);
    // std::string bridgeShmKeyName = baseShmKey->initRead();
    // init bridgeShmKey
    // SharedMemory* bridgeShmKey = new SharedMemory(bridgeShmKeyName);
    // std::string appShmKeyName_ = bridgeShmKey->initRead();
    // std::cout << appShmKeyName_ << std::endl;
    return true;
}

