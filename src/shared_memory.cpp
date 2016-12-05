#include "shared_memory.h"

SharedMemory::SharedMemory(std::string sharedMemoryName) {
    m_sharedMemoryName_ =  sharedMemoryName.c_str();
}

SharedMemory::~SharedMemory() {
    // TODO: check shared memory is alreadly deleted
    if (m_sharedMemoryBuffer != NULL) {
    }
}

std::string
SharedMemory::initRead() {
    std::cout << "init reading" << std::endl;
    shared_memory_object shm(open_only, m_sharedMemoryName_, read_write);
    mapped_region region(shm, read_write);
    void *addr = region.get_address();
    m_sharedMemoryBuffer = static_cast<SharedMemoryBuffer*>(addr);
    std::cout << sizeof(SharedMemoryBuffer) << std::endl;

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

bool
SharedMemory::initWrite() {
    shared_memory_object shm(open_or_create, m_sharedMemoryName_, read_write);
    shm.truncate(sizeof(SharedMemoryBuffer));
    mapped_region region(shm, read_write);
    void *addr = region.get_address();
    m_sharedMemoryBuffer = new (addr) SharedMemoryBuffer;

    try {
        while(true) {
            m_sharedMemoryBuffer->writer.wait();
                strcpy(m_sharedMemoryBuffer->appShmKey, m_sharedMemoryName_);
            m_sharedMemoryBuffer->reader.post();
        };
    } catch (interprocess_exception& e) {
        std::cout << e.what() << std::endl;
    }
    return true;
}



