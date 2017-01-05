#include "unix_domain_socket_step_server.h"

std::string LIBRARY_SOCKET_NAME = "/tmp/unix-socket-library";

UnixDomainSocketStepServer::UnixDomainSocketStepServer(std::string workerSocketName) {
    std::cout << "UnixDomainSocketStepServer::UnixDomainSocketStepServer" << std::endl;
    unlink(librarySocketName_.c_str());
    librarySocketName_ = LIBRARY_SOCKET_NAME;
    workerSocketName_ = workerSocketName;
}

UnixDomainSocketStepServer::~UnixDomainSocketStepServer() {
    closeSocket();
}

void
UnixDomainSocketStepServer::run() {
    create();
    serve();
}

void
UnixDomainSocketStepServer::create() {
    try {
        struct sockaddr_un server_addr;
        int soval = 1;

        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sun_family = AF_UNIX;
        strncpy(server_addr.sun_path, librarySocketName_.c_str(), sizeof(server_addr.sun_path) - 1);

        server_ = socket(AF_UNIX, SOCK_STREAM, 0);
        if(!server_) {
            std::cerr << "UnixDomainSocketStepServer::socket: ";
            throw;
        }

        if(setsockopt(server_, SOL_SOCKET, SO_REUSEADDR, &soval, sizeof(soval)) == -1) {
            std::cerr << "UnixDomainSOcketStepServer::Create setsockopt: ";
            throw;
        }

        if (bind(server_, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            std::cerr << "UnixDomainSocketStepServer::Create bind: ";
            throw;
        }

        if (listen(server_, 10) < 0) {
            std::cerr << "UnixDomainSocketStepServer::Create listn: ";
            throw;
        }
    } catch(...) {
        closeSocket();
    }
}

void
UnixDomainSocketStepServer::serve() {
    int client;
    struct sockaddr_in client_addr;
    socklen_t clientlen = sizeof(client_addr);

    while (1) {
        std::cout << "socket running" << std::endl;
        try {
            if ((client = accept(server_, (struct sockaddr *)&client_addr, &clientlen)) > 0) {
                handle(client);
            } else {
                throw;
            }
        } catch(...) {
            closeSocket();
        }
    }
    closeSocket();
}

void
UnixDomainSocketStepServer::handle(int client) {
    bool is_success;
    SocketAck ack;
    if (is_success = getRequest(client, ack)) {
        switch(ack.type) {
            case ASK_SHM:
                askShmKey(ack);
                sendDoorShmKey(client, ack);
                break;
            default:
                break;
        }
    }
}

bool
UnixDomainSocketStepServer::getRequest(int client, SocketAck &ack) {
    std::cout << "UnixDomainSocketStepServer::getRequest" << std::endl;
    int cc;
    if ((cc=recv(client, &ack, sizeof(ack), 0)) > 0) {
        return true;
    } else {
        return false;
    }
}

void
UnixDomainSocketStepServer::askShmKey(SocketAck &ack) {
    UnixDomainSocketClient client = UnixDomainSocketClient(workerSocketName_, ASK_SHM);
    client.run();
    std::string data = client.getRecievedData();
    // TODO; save shmkey to vector
    strcpy(ack.data, data.c_str());
}

void
UnixDomainSocketStepServer::sendDoorShmKey(int client, SocketAck &ack) {
    std::cout << "UnixDomainSocketStepServer::sendDoorShmKey" << std::endl;
    int cc;
    try {
        if ((cc = send(client, &ack, sizeof(ack), 0)) < 0) {
            std::cerr << "UnixDomainSocketStepServer" << std::endl;
            throw;
        } else {
            std::cout << "success" << std::endl;
        }
    } catch(...) {
        closeSocket();
    }

}

void
UnixDomainSocketStepServer::closeSocket() {
    std::cout << "UnixDomainSocketStepServer::closeSocket()" << std::endl;
    unlink(librarySocketName_.c_str());
}

