#include "bridge_manager.h"

BridgeManager::BridgeManager(std::string workerSocketName) {
    workerSocketName_ = workerSocketName;
    init();
}

BridgeManager::~BridgeManager() {
}

void
BridgeManager::init() {
    std::cout << "BridgeManger::init()" << std::endl;
    UnixDomainSocketStepServer socket = UnixDomainSocketStepServer(workerSocketName_);
    socket.run();
}

