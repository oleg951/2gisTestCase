cmake_minimum_required(VERSION 3.5)

project(TestCase LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(SOURCES ${CMAKE_SOURCE_DIR}/src/main.cpp
            ${CMAKE_SOURCE_DIR}/src/CommandLineParser.cpp
            ${CMAKE_SOURCE_DIR}/src/CommandLineArgument.cpp)
set (HEADERS ${CMAKE_SOURCE_DIR}/src/CommandLineParser.h
             ${CMAKE_SOURCE_DIR}/src/CommandLineArgument.h
             ${CMAKE_SOURCE_DIR}/src/CommandLineConsts.h)

add_executable(TestCase ${SOURCES})
