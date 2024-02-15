cmake_minimum_required(VERSION 3.0)
project(SocketProgramming)

# Set the C standard to use
set(CMAKE_C_STANDARD 99)

# Set compiler flags
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

# Include directories for TCP and UDP
include_directories(${CMAKE_SOURCE_DIR}/TCP)
include_directories(${CMAKE_SOURCE_DIR}/UDP)

# Add executables for TCP client and server
add_executable(tcp_server TCP/tcp_server.c)
add_executable(tcp_client TCP/tcp_client.c)

# Add executables for UDP client and server
add_executable(udp_server UDP/udp_server.c)
add_executable(udp_client UDP/udp_client.c)
