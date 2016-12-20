#include "door_bridge.h"

DoorBridge::DoorBridge() {
    std::cout << "=====DoorBridge::DoorBridge=====" << std::endl;
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
    std::cout << "=====DoorBridge::init======" << std::endl;
    std::cout << "appBaseShmKey: " << appBaseShmKey_ << std::endl;
    std::cout << "doorShmKey: " << doorShmKey_ << std::endl;
    SharedMemory<char, SharedKey>* appBaseShm = new SharedMemory<char, SharedKey>(appBaseShmKey_);
    std::cout << "doorShmKey:" << doorShmKey_ << std::endl;
    appBaseShm->read(&doorShmKey_);
    return true;
}

