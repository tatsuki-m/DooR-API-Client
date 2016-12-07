#!/bin/sh

g++ -c -fPIC ./src/door_shared_memory.cpp
g++ -c -fPIC ./src/shared_memory.cpp
g++ -c -fPIC ./src/door.cpp

g++ -shared -o libdoorapi.so -fPIC door.o door_shared_memory.o shared_memory.o

rm -f door.o door_shared_memory.o shared_memory.o

