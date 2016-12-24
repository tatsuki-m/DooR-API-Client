#include "bridge_manager.h"

BridgeManager::BridgeManager(std::string workerSocketName) {
    workerSocketName_ = workerSocketName;
    init();
}

BridgeManager::~BridgeManager() {
}

void
BridgeManager::init() {
    UnixDomainSocketStepServer socket = UnixDomainSocketStepServer(workerSocketName_);
    socket.run();
}

