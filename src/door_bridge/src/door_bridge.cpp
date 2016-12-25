#include "door_bridge.h"

std::string LIBRARY_SOCKET_NAME = "/tmp/unix-socket-library";

DoorBridge::DoorBridge() {
    std::cout << "DoorBridge::DoorBridge" << std::endl;
    init();
}

DoorBridge::~DoorBridge() {
}

void
DoorBridge::init() {
    std::cout << "DoorBridge::init" << std::endl;
    SocketType type = ASK_SHM;
    UnixDomainSocketClient socket = UnixDomainSocketClient(LIBRARY_SOCKET_NAME, type);
    socket.run();
    doorShmKey_ = socket.getRecievedData();
}

void
DoorBridge::getAllInformation(Dpi* dpi, std::string keyword) {
//    Door door = Door(keyword);
    SharedMemory<Dpi, SharedPacketInformation>* doorShm = new SharedMemory<Dpi, SharedPacketInformation>(doorShmKey_);
    doorShm->read(&dpi);
}

