include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG 609281088cfefc76f9d0ce82e1ff6c30cc3591e5
    )

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

set (HEADERS
    Fixture.h)

set(SOURCES
    ChecksummTest.cpp
    WordCountTest.cpp
    ArgumentsTest.cpp
    Fixture.cpp
    )

add_executable(UnitTests ${SOURCES})
target_link_libraries(UnitTests gtest_main gmock_main CommandLineLib)

include(GoogleTest)
gtest_add_tests(TARGET UnitTests)
