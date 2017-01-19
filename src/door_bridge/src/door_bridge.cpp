#include "door_bridge.h"

std::string DOCKER_SOCKET_NAME = "/tmp/docker-unix-socket";

DoorBridge::DoorBridge() {
    std::cout << "DoorBridge::DoorBridge" << std::endl;
    init();
}

DoorBridge::~DoorBridge() {
    doorSem_.close();
}

void
DoorBridge::init() {
    std::cout << "DoorBridge::init" << std::endl;
    getDoorKey();
    createSem();
}

void
DoorBridge::getDoorKey() {
    SocketType type = ASK_SHM;
    UnixDomainSocketClient socket = UnixDomainSocketClient(DOCKER_SOCKET_NAME, type);
    socket.run();
    doorKey_ = socket.getRecievedData();
}

void
DoorBridge::createSem() {
    std::cout << "DoorBridge::createSem()" << std::endl;
    doorSem_.create(doorKey_);
}

// this function is located in getInformationWithSem by all rights
// this function is separated because of experiment
bool
DoorBridge::callDoorWithSem() {
    bool is_success = client_.callDoorWithSem(doorKey_);
    return is_success;
}

//sync
void
DoorBridge::waitDoorNotification() {
    doorSem_.wait();
}


//API
void
DoorBridge::getPacketDataWithSem(Dpi*& dpi) {
    SharedMemory<Dpi, SharedPacketInformation> doorSem = SharedMemory<Dpi, SharedPacketInformation>(doorKey_);
    doorSem.read(&dpi);
}

