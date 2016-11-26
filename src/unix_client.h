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

using namespace std;

class UnixClient {

public:
    UnixClient();
    ~UnixClient();

    int run();
    int mem_key_;

private:
    void create();
    void handle();
    bool send_ack();
    bool get_response();
    void close_socket();

    int server_;
    int ack_;
    static const char* socket_name_;
};

