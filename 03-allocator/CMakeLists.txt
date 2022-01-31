add_library(allocator INTERFACE)
target_include_directories(allocator INTERFACE ${CMAKE_SOURCE_DIR})

add_executable(allocator-cli main.cpp)
target_link_libraries(allocator-cli PRIVATE allocator)

install(TARGETS allocator-cli RUNTIME DESTINATION bin)

if (TESTING_ENABLED)

endif()