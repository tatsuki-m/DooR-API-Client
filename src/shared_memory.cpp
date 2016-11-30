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
    unsigned int m_size;
    m_size = sizeof(unsigned int);
    std::cout << m_size << "byte" << std::endl;

    m_shm_ = new managed_shared_memory(open_or_create, m_sharedMemoryName_, m_size);
    std::cout << "memory instance create" << std::endl;

    return true;
}

bool
SharedMemory::getStruct() {
    if ( m_shm_ == NULL )
        return false;
    interprocess_mutex* mx = m_shm_->find_or_construct<interprocess_mutex>("TheMutext")();
    unsigned int* SharedMemoryPointer = m_shm_->find_or_construct<unsigned int>("Integer")();

    scoped_lock<interprocess_mutex> *lock = new scoped_lock<interprocess_mutex>(*mx);
    memcpy(SharedMemoryPointer, shmKey_, sizeof(unsigned int));

    delete lock;
    return true;
}

