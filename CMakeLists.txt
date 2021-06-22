cmake_minimum_required(VERSION 3.16)

project(TestCase
        VERSION 1.0.0
        DESCRIPTION "2gis test"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -Wpedantic")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(src)

add_subdirectory(src)

enable_testing()

add_subdirectory(test)
