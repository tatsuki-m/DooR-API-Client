#include "shared_memory.h"

SharedMemory::SharedMemory(std::string sharedMemoryName) {
    strcpy(m_sharedMemoryName_, sharedMemoryName.c_str());
    m_shm_ = NULL;
}

SharedMemory::~SharedMemory() {
    if (m_shm_ != NULL) delete m_shm_;
}

bool
SharedMemory::init() {
    int m_size;
    m_size = sizeof(SharedSt) + 1024 * 10;
    std::cout << m_size << "byte" << std::endl;

    m_shm_ = new managed_shared_memory(open_or_create, m_sharedMemoryName_, m_size);
    std::cout << "memory instance create" << std::endl;

    return true;
}

