cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

message("PROJECT_VERSION: ${PROJECT_VERSION}")

project(alex_ruban_otus_course VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 17)

## Options
option(TESTING_ENABLED "Enable test framework and project tests to the build" ON)
if (TESTING_ENABLED)
    enable_testing()
endif()


## Helpers
add_subdirectory(3d-party)

## Homeworks
add_subdirectory(01-cicd-setup)
add_subdirectory(02-ip-filter)
add_subdirectory(03-allocator)

## Package config
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT test@example.com)
include(CPack)
