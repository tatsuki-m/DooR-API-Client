#ifndef BRIDGE_MANAGER_H_
#define BRIDGE_MANAGER_H_

#include <iostream>
#include <string>

#include "socket_ack.h"
#include "unix_domain_socket_step_server.h"

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

