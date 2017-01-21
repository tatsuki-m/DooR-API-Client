#ifndef DOOR_BRIDGE_H_
#define DOOR_BRIDGE_H_

#include <iostream>
#include <string>

#include "door_unix_domain_socket_client/unix_domain_socket_client.h"
#include "door_unix_domain_socket_client/socket_ack.h"
#include "door_api/door_api.h"
#include "door_api/door_socket.h"
#include "door_ipc/shared_memory.h"
#include "door_ipc/shared_packet_information.h"
#include "door_ipc/dpi.h"
#include "door_ipc/sync_semaphore.h"
#include "door_ipc/socket_client.h"

class DoorBridge
{
public:
    DoorBridge();
    ~DoorBridge();

    // initial call for door
    void callDoorWithSem();
    void callDoorWithUds();
    void callDoorWithTcp();


    // get from door
    void getPacketDataWithSem(Dpi*& dpi);
    void getPacketDataWithUds(Dpi*& dpi);

private:
    void init();
    void createSem();
    void getDoorKey();

    std::string doorKey_;
    SyncSemaphore doorSem_;
    DoorApi client_;
};

#endif

