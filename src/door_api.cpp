#include "door_api.h"

DoorApi::DoorApi() {
    shm_ = new SharedMemory(shmKey);
    shm_-> init();
}

DoorApi::~DoorApi() {
    delete shm;
}

DoorApi::getShmKey() {
}

