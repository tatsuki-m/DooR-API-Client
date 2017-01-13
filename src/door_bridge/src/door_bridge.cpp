#include "door_bridge.h"

std::string DOCKER_SOCKET_NAME = "/tmp/docker-unix-socket";

DoorBridge::DoorBridge() {
    std::cout << "DoorBridge::DoorBridge" << std::endl;
    init();
}

DoorBridge::~DoorBridge() {
}

void
DoorBridge::init() {
    std::cout << "DoorBridge::init" << std::endl;
    getDoorKey();
}

void
DoorBridge::getDoorKey() {
    SocketType type = ASK_SHM;
    UnixDomainSocketClient socket = UnixDomainSocketClient(DOCKER_SOCKET_NAME, type);
    socket.run();
    doorKey_ = socket.getRecievedData();
}

// this function is located in getInformationWithSem by all rights
// this function is separated because of experiment
bool
DoorBridge::callDoorWithSem() {
    bool is_success = client_.callDoorWithSem(doorKey_);
    return is_success;
}

//API
void
DoorBridge::getPacketDataWithSem(Dpi*& dpi) {
    SharedMemory<Dpi, SharedPacketInformation> doorShm = SharedMemory<Dpi, SharedPacketInformation>(doorKey_);
    doorShm.read(&dpi);
}

