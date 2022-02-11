cmake_minimum_required(VERSION 3.21)
project(clientServer)

set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.78.0 REQUIRED)
message(STATUS "Boost version: ${Boost_VERSION}")

add_subdirectory(server)
add_subdirectory(client)
