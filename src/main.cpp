#include <iostream>
#include <string>

#include "unix_domain_socket_client.h"
#include "door_bridge/door_bridge.h"

#include "door_shared_memory/shared_memory.h"
#include "door_shared_memory/shared_key.h"


int
main() {
    // this shmKey for application to know the shared memory name, which connected client and server

    // run socket communication
    std::string socketName = "/tmp/unix-socket";
    SocketType type = SHARED_SOCKET;
    UnixDomainSocketClient client = UnixDomainSocketClient(socketName, type);
    client.run();


    // write BridgeShmKey to AppBaseShm. which will be refered from Door librry in bridge side
//    SharedMemory<char, SharedKey>* appBaseShm = new SharedMemory<char, SharedKey>(appBaseShmKey);
//    appBaseShm->write((char*)bridgeShmKey.c_str());


//    DoorBridge* bridge = new DoorBridge();
//    sleep(1);
//    delete bridge;

    return 0;
};

