set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

message("PROJECT_VERSION: ${PROJECT_VERSION}")
project(helloworld VERSION ${PROJECT_VERSION})

add_executable(helloworld_cli hello_world.cpp)
add_definitions(-DMINOR_PATCH_VERSION=${PATCH_VERSION})
