#include <iostream>
#include <string>

#include "unix_client.h"
#include "shared_memory.h"

int
main() {
    // this shmKey for application to know the shared memory name, which connected client and server
    std::string baseShmKey = "shmKey0000";

    // run socket communication
    UnixClient client = UnixClient();
    client.run();
    std::string clientShmKey = client.getRecievedKey();
    std::cout << clientShmKey << std::endl;


    // create shared memory, which are referd by application to know the clientShmKey
    SharedMemory *shm = new SharedMemory(baseShmKey);
    shm->initWrite(clientShmKey);
    return 0;
};

