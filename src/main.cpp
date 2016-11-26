#include <iostream>
#include <string>

#include "unix_client.h"
#include "shared_memory.h"

std::string getShmKey(int);

int
main() {
    int i_shmKey;

    // run socket communication
    UnixClient client = UnixClient();
    i_shmKey = client.run();

    std::string shmKey = getShmKey(i_shmKey);
    std::cout << shmKey << std::endl;

    SharedMemory *shm = new SharedMemory(shmKey);
    std::cout << "generate worker" << std::endl;
    delete shm;

    return 0;
};

std::string getShmKey(int key) {
    std::string shmKey = "shm_key" + std::to_string(key);
    return shmKey;
};


