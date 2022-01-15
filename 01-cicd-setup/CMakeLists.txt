add_executable(helloworld_cli hello_world.cpp)
add_definitions(-DMINOR_PATCH_VERSION=${PATCH_VERSION})

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

