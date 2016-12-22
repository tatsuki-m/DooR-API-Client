#ifndef UNIX_DOMAIN_SOCKET_STEP_SERVER_H_
#define UNIX_DOMAIN_SOCKET_STEP_SERVER_H_

#pragma once

#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "door_bridge/socket_ack.h"
#include "door_bridge/unix_domain_socket_client.h"

class UnixDomainSocketStepServer {

public:
    UnixDomainSocketStepServer(std::string);
    ~UnixDomainSocketStepServer();

    void run();
    std::string getRecievedKey();

private:
    void serve();
    void create();
    void handle(int);
    bool sendAck();
    bool getRequest(int, SocketAck&);
    void closeSocket();
    void askShmKey(SocketAck&);
    void sendDoorShmKey(int, SocketAck&);
    std::string getSocketName();
    std::string getShmKey();

    int server_;
    //TODO: move to bridge manager, in this class, just have pointer of it
    std::vector<std::string> doorShmKeys_;
    std::string librarySocketName_;
    std::string workerSocketName_;
};

#endif

