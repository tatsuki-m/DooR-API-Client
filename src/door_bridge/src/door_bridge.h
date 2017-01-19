#ifndef DOOR_BRIDGE_H_
#define DOOR_BRIDGE_H_

#include <iostream>
#include <string>

#include "door_unix_domain_socket_client/unix_domain_socket_client.h"
#include "door_unix_domain_socket_client/socket_ack.h"
#include "door_api/door_api.h"
#include "door_ipc/shared_memory.h"
#include "door_ipc/shared_packet_information.h"
#include "door_ipc/dpi.h"
#include "door_ipc/sync_semaphore.h"

class DoorBridge
{
public:
    DoorBridge();
    ~DoorBridge();

    bool callDoorWithSem();
    void getPacketDataWithSem(Dpi*& dpi);
    void getDoorKey();
    void createSem();
    void waitDoorNotification();
private:
    void init();

    std::string doorKey_;
    SyncSemaphore doorSem_;
    DoorApi client_;
};

#endif

