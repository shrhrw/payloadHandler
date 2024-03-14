# Minimum version of CMake required to build this project
cmake_minimum_required( VERSION 3.22.1 )

# Name of project
project( payloadHandler LANGUAGES C )

# CMake standard (C11)
set( CMAKE_CXX_STANDARD 11 )

# Add path to all dependency directories
include_directories(
    example
    munit
    src
    test
)

add_library( munit STATIC munit/munit.c )
add_library( payloadHandler STATIC src/payloadHandler.c )

add_executable( sendPacket example/sendPacket.c )
add_executable( payloadHandlerTests test/payloadHandlerTests.c )

target_link_libraries(
    payloadHandlerTests
    payloadHandler
    munit
)
