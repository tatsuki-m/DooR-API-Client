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
    bool is_sucess = client_.callDoor(doorKey_, SHM);
    if (is_sucess)
        waitDoorNotification();
    else
        std::cerr << "error";
}

void
DoorBridge::callDoorWithUds() {
    bool is_sucess = client_.callDoor(doorKey_, UD_SOCK);
    if (is_sucess)
        waitDoorNotification();
    else
        std::cerr << "error";
}

void
DoorBridge::callDoorWithTcp() {
    bool is_sucess = client_.callDoor(doorKey_, TCP_SOCK);
    if (is_sucess)
        waitDoorNotification();
    else
        std::cerr << "error";
}

//sync
void
DoorBridge::waitDoorNotification() {
    doorSem_.wait();
}


//=======================
// API
// ======================
void
DoorBridge::getPacketDataWithSem(Dpi*& dpi) {
    SharedMemory<Dpi, SharedPacketInformation> doorSem = SharedMemory<Dpi, SharedPacketInformation>(doorKey_);
    doorSem.read(&dpi);
}


