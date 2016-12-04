#include "shared_memory.h"

SharedMemory::SharedMemory(std::string sharedMemoryName) {
    m_sharedMemoryName_ =  sharedMemoryName.c_str();
}

SharedMemory::~SharedMemory() {
    // TODO: check shared memory is alreadly deleted
    if (m_sharedMemoryBuffer != NULL) {
        shared_memory_object::remove(m_sharedMemoryName_);
    }

}

std::string
SharedMemory::init() {
    std::cout << "init" << std::endl;
    shared_memory_object shm(open_only, m_sharedMemoryName_, read_write);
    mapped_region region(shm, read_write);
    void *addr = region.get_address();
    m_sharedMemoryBuffer = static_cast<SharedMemoryBuffer*>(addr);
    std::cout << "ready" << std::endl;

    try {
        m_sharedMemoryBuffer->reader.wait();
        std::string shmKey = m_sharedMemoryBuffer->appShmKey;
        std::cout << m_sharedMemoryBuffer->appShmKey << std::endl;
        m_sharedMemoryBuffer->writer.post();
        std::cout << "writer post" << std::endl;
        return shmKey;
    } catch (interprocess_exception& e) {
        std::cout << e.what() << std::endl;
    }
}


