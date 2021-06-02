cmake_minimum_required(VERSION 3.5)

project(TestCase LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-o3 -Wall -Werror -Wextra -Wpedantic")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(SOURCES ${CMAKE_SOURCE_DIR}/src/main.cpp
            ${CMAKE_SOURCE_DIR}/src/CommandLineExcecutor.cpp)
set (HEADERS ${CMAKE_SOURCE_DIR}/src/CommandLineConsts.h
             ${CMAKE_SOURCE_DIR}/src/CommandLineExcecutor.h)

find_package(Boost 1.76.0 REQUIRED program_options)

add_executable(TestCase ${SOURCES})

target_compile_features(TestCase PRIVATE cxx_std_20)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
