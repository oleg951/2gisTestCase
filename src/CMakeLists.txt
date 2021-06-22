set(SOURCES
    CommandLineExcecutor.cpp
    FileStream.cpp)

set (HEADERS
    CommandLineArgumentConsts.h
    CommandLineExcecutor.h
    IFileStream.h
    FileStream.h
    )

find_package(Boost 1.69.0 REQUIRED program_options)

add_library(CommandLineLib ${SOURCES})
target_link_directories(CommandLineLib PUBLIC ${HEADERS})
target_link_libraries(CommandLineLib ${Boost_LIBRARIES})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} CommandLineLib)
