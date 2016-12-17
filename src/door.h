#ifndef DOOR_H_
#define DOOR_H_

#include <iostream>
#include <string>

#include "shared_memory.h"

class Door
{
public:
    Door();
    ~Door();
private:
    bool init();

    std::string baseShmKeyName_;
    std::string appShmKeyName_;

};

#endif

