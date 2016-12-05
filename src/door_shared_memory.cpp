#include "door_shared_memory.h"

DoorSharedMemory::DoorSharedMemory(std::string sharedMemoryName) {
    m_sharedMemoryName_ = sharedMemoryName.c_str();
}

DoorSharedMemory::~DoorSharedMemory() {
}

std::string
DoorSharedMemory::init() {
    shared_memory_object shm(open_only, m_sharedMemoryName_, read_write);
    mapped_region region(shm, read_write);
    void *addr = region.get_address();
    m_sharedMemoryBuffer = static_cast<SharedMemoryBuffer*>(addr);

    try {
        m_sharedMemoryBuffer->reader.wait();
        // Do sth
        m_sahredMemoryBuffer->writer.post();
        return "hoge";
    } catch (interprocess_exception& e) {
        std::cout << e.what() << std::endl;
    }
}

