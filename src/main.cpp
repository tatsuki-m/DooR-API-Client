#include <iostream>
#include <string>

#include "unix_client.h"
#include "shared_memory.h"
#include "shared_key.h"

int
main() {
    // this shmKey for application to know the shared memory name, which connected client and server
    const std::string appBaseShmKey = "shmKey0000";

    // run socket communication
    UnixClient client = UnixClient();
    client.run();
    std::string doorShmKey = client.getRecievedKey();
    std::cout << doorShmKey << std::endl;

    // SharedMemory<char, SharedKey>* appBaseShmKey = new SharedMemory<char, SharedKey>(appBaseShmKey.c_str());
    // appBaseShmKey.write(doorShmKey

    // create shared memory, which are referd by application to know the clientShmKey
    // SharedMemory<char, SharedKey>*app_  = new SharedMemory<char, SharedKey>(appBaseShm.c_str());
    return 0;
};

