#include <iostream>
#include <string>
#include <csignal>

#include "bridge_manager.h"
#include "door_unix_domain_socket_client/unix_domain_socket_client.h"
#include "door_unix_domain_socket_client/socket_ack.h"

std::string INIT_SOCKET_NAME = "/tmp/unix-socket/unix-socket";

void
signalHandler(int sigNum) {
    std::cout << "Interrupt signal (" << sigNum << ") received." << std::endl;
    std::cout << "Going to sleep.." <<std::endl;
    exit(sigNum);
}

int
main() {
    signal(SIGINT, signalHandler);

    // run socket communication
    SocketType type = ASK_SOCKET;
    UnixDomainSocketClient client = UnixDomainSocketClient(INIT_SOCKET_NAME, type);
    client.run();
    std::string workerSocketName = client.getRecievedData();
    std::cout << "main:: workerSocketName: " << workerSocketName << std::endl;

    BridgeManager* bridgeManager = new BridgeManager(workerSocketName);
    delete bridgeManager;

    return 0;
};

