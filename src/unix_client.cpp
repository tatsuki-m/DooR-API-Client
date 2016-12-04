#include "unix_client.h"

const char* UnixClient::socket_name_ = "/tmp/unix-socket";

UnixClient::UnixClient() {
    ack_ = 0;
}

UnixClient::~UnixClient() {
}


void
UnixClient::run() {
    create();
    handle();
    close_socket();
}

void
UnixClient::close_socket() {
    if (close(server_) == -1) {
        perror("close");
        exit(-1);
    }
}

void
UnixClient::create() {
    struct sockaddr_un server_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, socket_name_, sizeof(server_addr.sun_path) - 1);

    server_ = socket(PF_UNIX, SOCK_STREAM, 0);
    if (!server_) {
        perror("socket");
        exit(-1);
    }

    if (connect(server_, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        exit(-1);
    }
}

void
UnixClient::handle() {
    bool sent, success;
    sent = send_ack();
    if (not sent)
        exit(-1);
    success = get_response();
    if (not success)
        exit(-1);
}


bool
UnixClient::send_ack() {
    int ss;

    if ((ss = send(server_, &ack_, sizeof(int), 0)) < 0) {
        perror("write");
        return false;
    } else {
        return true;
    }
}

bool
UnixClient::get_response() {
    int gs;

    if ((gs = recv(server_, shmKey_, sizeof(shmKey_), 0)) < 0 ) {
        perror("read");
        return false;
    } else {
        return true;
    }
}

std::string
UnixClient::getRecievedKey() {
    std::string shmKey = shmKey_;
    return shmKey;
}

