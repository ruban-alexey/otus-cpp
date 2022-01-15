add_library(ip-filter lib.cpp)
target_include_directories(ip-filter PRIVATE ${CMAKE_SOURCE_DIR})

add_executable(ip-filter-cli main.cpp)
target_link_libraries(ip-filter-cli PRIVATE ip-filter)

install(TARGETS ip-filter-cli RUNTIME DESTINATION bin)

if (TESTING_ENABLED)
    set(RESOURCES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/resources)
    add_executable(ip-filter-tests 02-tests.cpp)
    target_link_libraries(ip-filter-tests PRIVATE ip-filter gtest)
    target_compile_definitions(ip-filter-tests PUBLIC -DRESOURCES_PATH="${RESOURCES_PATH}")

    add_test(ip-filter-tests ip-filter-tests)
endif()