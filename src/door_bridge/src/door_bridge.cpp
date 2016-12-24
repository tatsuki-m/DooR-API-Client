#include "door_bridge.h"

std::string LIBRARY_SOCKET_NAME = "/tmp/library-unix-socket";

DoorBridge::DoorBridge() {
    std::cout << "=====DoorBridge::DoorBridge=====" << std::endl;
    init();
}

DoorBridge::~DoorBridge() {
}

void
DoorBridge::init() {
    SocketType type = ASK_SHM;
    UnixDomainSocketClient socket = UnixDomainSocketClient(LIBRARY_SOCKET_NAME, type);
    socket.run();
    std::string doorShmKey = socket.getRecievedData();
}

