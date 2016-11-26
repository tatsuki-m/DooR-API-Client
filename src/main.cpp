#include <iostream>
#include "unix_client.h"

int
main() {
    int shm_key;

    // run socket communication
    UnixClient client = UnixClient();
    shm_key = client.run();

    std::cout << shm_key << std::endl;
    return 0;
}
