execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE CMAKE_STATUS_CODE
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/googletest"
        )

if(CMAKE_STATUS_CODE)
    message(FATAL_ERROR "CMake step for `googletest` has failed: status code=${CMAKE_STATUS_CODE}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE CMAKE_STATUS_CODE
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/googletest
)

if(CMAKE_STATUS_CODE)
    message(FATAL_ERROR "Build step for `googletest` has failed: status code=${CMAKE_STATUS_CODE}")
endif()

#set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)

add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/build"
    EXCLUDE_FROM_ALL
)
