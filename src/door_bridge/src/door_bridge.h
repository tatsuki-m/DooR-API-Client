#ifndef DOOR_BRIDGE_H_
#define DOOR_BRIDGE_H_

#include <iostream>
#include <string>

#include "unix_domain_socket_client.h"
#include "socket_ack.h"
#include "door_shared_memory/shared_memory.h"
#include "door_shared_memory/shared_packet_information.h"
#include "door_shared_memory/dpi.h"


class DoorBridge
{
public:
    DoorBridge();
    ~DoorBridge();

    //api
    void getAllInformation(Dpi* dpi, std::string);

private:
    void init();
    std::string doorShmKey_;

};

#endif

