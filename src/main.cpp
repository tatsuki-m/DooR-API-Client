#include <iostream>
#include <string>

#include "unix_client.h"
#include "shared_memory.h"

std::string getShmKey(int);

int
main() {
    unsigned int i = 0;

    // run socket communication
    UnixClient client = UnixClient();
    client.run();
    std::string shmKey = client.getRecievedKey();

    // shared memory
    SharedMemory *shm;
    shm = new SharedMemory(shmKey);
    shm->init();

    while (true) {
        shm->shmKey_= i;

        if (!shm->getStruct())
            std::cout << "upload failed" << std::endl;

        cout << shm->shmKey_ << "  " << endl;
        sleep(1);
    }
    delete shm;
    return 0;
};

std::string getShmKey(int key) {
    std::string shmKey = "shm_key" + std::to_string(key);
    return shmKey;
};

