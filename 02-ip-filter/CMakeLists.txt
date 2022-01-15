add_library(ip-filter lib.cpp)
target_include_directories(ip-filter PRIVATE ${CMAKE_SOURCE_DIR})

add_executable(ip-filter-cli main.cpp)
target_link_libraries(ip-filter-cli PRIVATE ip-filter)