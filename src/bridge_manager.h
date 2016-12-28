#ifndef BRIDGE_MANAGER_H_
#define BRIDGE_MANAGER_H_

#include <iostream>
#include <string>

#include "unix_domain_socket_step_server.h"
#include "door_bridge/socket_ack.h"

class BridgeManager
{
public:
    BridgeManager(std::string);
    ~BridgeManager();
    void init();
private:
    std::string workerSocketName_;
};

#endif

