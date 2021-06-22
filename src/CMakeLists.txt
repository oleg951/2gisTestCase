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
target_include_directories (CommandLineLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${Boost_INCLUDE_DIRS} )
target_link_libraries(CommandLineLib ${Boost_LIBRARIES})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} CommandLineLib)
