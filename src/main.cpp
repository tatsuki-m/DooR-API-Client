#include <iostream>
#include <string>

#include "unix_client.h"
#include "shared_memory.h"

std::string getShmKey(int);

int
main() {
    int i_shmKey;
    int i = 0;
    float f = 0.0;

    // run socket communication
    UnixClient client = UnixClient();
    i_shmKey = client.run();

    // shared memory
    std::string shmKey = getShmKey(i_shmKey);
    std::cout << "shmKey" << std::endl;

    SharedMemory *shm;
    shm = new SharedMemory(shmKey);
    shm->init();

    while (true) {
        shm->m_sharedSt_.valueFloat = f;
        shm->m_sharedSt_.value = i;

        if (!shm->setStruct())
            std::cout << "upload failed" << std::endl;

        cout << shm->m_sharedSt_.value << "  " << shm->m_sharedSt_.valueFloat << endl;
        i += 1;
        f += 1.1111111;
        sleep(1);
    }
    delete shm;
    return 0;
};

std::string getShmKey(int key) {
    std::string shmKey = "shm_key" + std::to_string(key);
    return shmKey;
};

