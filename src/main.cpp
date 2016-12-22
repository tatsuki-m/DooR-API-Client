#include <iostream>
#include <string>

#include "bridge_manager.h"
#include "unix_domain_socket_client.h"
#include "socket_ack.h"

int
main() {
    // this shmKey for application to know the shared memory name, which connected client and server

    // run socket communication
    std::string initSocketName = "/tmp/unix-socket";
    SocketType type = ASK_SOCKET;
    UnixDomainSocketClient client = UnixDomainSocketClient(initSocketName, type);
    client.run();
    std::string workerSocketName = client.getRecievedData();

    BridgeManager* bridgeManager = new BridgeManager(workerSocketName);
    delete bridgeManager;

    return 0;
};

