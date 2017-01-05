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
    getDoorShmKey();
}

void
DoorBridge::getDoorShmKey() {
    SocketType type = ASK_SHM;
    UnixDomainSocketClient socket = UnixDomainSocketClient(LIBRARY_SOCKET_NAME, type);
    socket.run();
    doorShmKey_ = socket.getRecievedData();
}

bool
DoorBridge::readShm(Dpi* dpi) {
    SharedMemory<Dpi, SharedPacketInformation>* doorShm = new SharedMemory<Dpi, SharedPacketInformation>(doorShmKey_);
    bool is_read = doorShm->read(&dpi);
    std::cout << "DoorBridge::readShm: " << dpi->id_<< std::endl;
    return is_read;
}

//API
bool
DoorBridge::getAllInformation(Dpi*& dpi, std::string keyword) {
    bool is_read;
    client_.getAllInformation(doorShmKey_, keyword);

    SharedMemory<Dpi, SharedPacketInformation>* doorShm = new SharedMemory<Dpi, SharedPacketInformation>(doorShmKey_);
    is_read = doorShm->read(&dpi);
    std::cout << "DoorBridge::readShm: " << dpi->id_<< std::endl;
    std::cout << "dpi address:" << &dpi << std::endl;

    if (is_read) {
        std::cout << "read shared memory data" << std::endl;
        return true;
    } else {
        return false;
    }
}

