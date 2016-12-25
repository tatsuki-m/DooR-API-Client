#include "door_bridge.h"

std::string LIBRARY_SOCKET_NAME = "/tmp/unix-socket-library";

DoorBridge::DoorBridge() {
    std::cout << "=====DoorBridge::DoorBridge=====" << std::endl;
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
    std::string doorShmKey = socket.getRecievedData();
}

