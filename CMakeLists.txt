cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

message("PROJECT_VERSION: ${PROJECT_VERSION}")

project(alex_ruban_otus_course VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(01-cicd-setup)

