cmake_minimum_required(VERSION 2.8)

set (PROJECT_NAME "door_bridge")
cmake_policy(SET CMP0022 NEW)
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS_RELEASE "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_BUILD_TYPE Release)

# set version
set(serial "1.0.0")
set(soserial "1")

set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

#include file
file(GLOB Srcs "./src/*.cpp")
file(GLOB HDRS "./src/*.h")

include_directories("${PROJECT_SOURCE_DIR}")

add_library(${PROJECT_NAME} SHARED ${Srcs})

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${serial}
    SOVERSION ${soserial}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    PUBLIC_HEADER "${HDRS}"
)

install(TARGETS door_bridge
    EXPORT          door_bridge_export
    LIBRARY         DESTINATION lib
    INCLUDES        DESTINATION include
    PUBLIC_HEADER   DESTINATION "include/${PROJECT_NAME}"
)

install(EXPORT door_bridge_export
    FILE door_bridge-config.cmake
    DESTINATION "share/cmake/${PROJECT_NAME}/"
    EXPORT_LINK_INTERFACE_LIBRARIES
)

