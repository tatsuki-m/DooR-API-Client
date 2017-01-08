#ifndef DOOR_BRIDGE_H_
#define DOOR_BRIDGE_H_

#include <iostream>
#include <string>

#include "door_unix_domain_socket_client/unix_domain_socket_client.h"
#include "door_unix_domain_socket_client/socket_ack.h"
#include "door_api/door_api.h"
#include "door_shared_memory/shared_memory.h"
#include "door_shared_memory/shared_packet_information.h"
#include "door_shared_memory/dpi.h"

class DoorBridge
{
public:
    DoorBridge();
    ~DoorBridge();

    //api
    bool getInformationWithSem(Dpi*& dpi, std::string);

private:
    void init();
    void getDoorShmKey();
    std::string doorShmKey_;
    DoorApi client_;
};

#endif

