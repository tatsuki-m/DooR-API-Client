#include <iostream>
#include <string>

#include "unix_client.h"
#include "shared_memory.h"

int
main() {
    int shm_key;

    // run socket communication
    UnixClient client = UnixClient();
    shm_key = client.run();

    std::cout << shm_key << std::endl;
    return 0;
}
