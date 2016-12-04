#include <iostream>
#include <string>

#include "unix_client.h"
#include "shared_memory.h"

std::string getShmKey(int);

int
main() {
    // run socket communication
    UnixClient client = UnixClient();
    client.run();
    std::string shmKey = client.getRecievedKey();
    std::cout << shmKey << std::endl;

    // shared memory
    SharedMemory *shm = new SharedMemory(shmKey);
    std::string shmAppKey = shm->init();

    delete shm;
    return 0;
};

