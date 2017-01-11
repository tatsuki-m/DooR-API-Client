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
    getDoorShmKey();
}

void
DoorBridge::getDoorShmKey() {
    SocketType type = ASK_SHM;
    UnixDomainSocketClient socket = UnixDomainSocketClient(DOCKER_SOCKET_NAME, type);
    socket.run();
    doorShmKey_ = socket.getRecievedData();
}

//API
bool
DoorBridge::getInformationWithSem(Dpi*& dpi, std::string keyword) {
    bool is_read;
    client_.callDoorWithSem(doorShmKey_, keyword);

    SharedMemory<Dpi, SharedPacketInformation> doorShm = SharedMemory<Dpi, SharedPacketInformation>(doorShmKey_);
    is_read = doorShm.read(&dpi);

    if (is_read) {
        std::cout << "read shared memory data" << std::endl;
        return true;
    } else {
        return false;
    }
}

