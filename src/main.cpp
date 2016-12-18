#include <iostream>
#include <string>

#include "unix_client.h"
#include "door_shared_memory/shared_memory.h"
#include "door_shared_memory/shared_key.h"

int
main() {
    // this shmKey for application to know the shared memory name, which connected client and server
    std::string appBaseShmKey = "shmKey0000";

    // run socket communication
    UnixClient client = UnixClient();
    client.run();
    std::string bridgeShmKey = client.getRecievedKey();

    // write BridgeShmKey to AppBaseShm. which will be refered from Door librry in bridge side
    SharedMemory<char, SharedKey>* appBaseShm = new SharedMemory<char, SharedKey>(appBaseShmKey);
    appBaseShm->write((char*)bridgeShmKey.c_str()); /* loop */

    // delete[] appBaseShmKey;

    // delete appBaseShm;
    return 0;
};

