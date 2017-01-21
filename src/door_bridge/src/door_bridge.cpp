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

// get DoorKey
void
DoorBridge::getDoorKey() {
    SocketType type = ASK_SHM;
    UnixDomainSocketClient socket = UnixDomainSocketClient(DOCKER_SOCKET_NAME, type);
    socket.run();
    doorKey_ = socket.getRecievedData();
}

// sync
void
DoorBridge::createSem() {
    std::cout << "DoorBridge::createSem()" << std::endl;
    doorSem_.create(doorKey_);
}

// =====================
// call for door
// =====================
void
DoorBridge::callDoorWithSem() {
    client_.callDoor(doorKey_, SHM);
    doorSem_.wait();
}

void
DoorBridge::callDoorWithUds() {
    client_.callDoor(doorKey_, UD_SOCK);
    std::cout << doorSem_.getValue() << std::endl;
    doorSem_.wait();
}

void
DoorBridge::callDoorWithTcp() {
    client_.callDoor(doorKey_, TCP_SOCK);
    syncDpi();
}

void
DoorBridge::syncDpi() {
    std::cout << doorSem_.getValue() << std::endl;
    sleep(5);
    std::cout << "DoorBridge::syncDpi()" << std::endl;
    doorSem_.wait();
    std::cout << "DoorBridge::syncDpi()" << std::endl;
    std::cout << "num: " << doorSem_.getValue() << std::endl;
}

//=======================
// API
// ======================
void
DoorBridge::getPacketDataWithSem(Dpi*& dpi) {
    SharedMemory<Dpi, SharedPacketInformation> doorSem = SharedMemory<Dpi, SharedPacketInformation>(doorKey_);
    doorSem.read(&dpi);
}

void
DoorBridge::getPacketDataWithUds(Dpi*& dpi) {
    SocketClient socket = SocketClient(doorKey_);
    socket.run();
    socket.getDpi(dpi);
}

