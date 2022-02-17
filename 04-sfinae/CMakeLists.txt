add_executable(sfinae-cli main.cpp)

install(TARGETS allocator-cli RUNTIME DESTINATION bin)

#if (TESTING_ENABLED)
#    add_executable(allocator-tests 03-tests.cpp)
#    target_link_libraries(allocator-tests PRIVATE allocator gtest)
#
#    add_test(allocator-tests allocator-tests)
#endif()
