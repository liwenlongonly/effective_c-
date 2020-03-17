cmake_minimum_required(VERSION 3.15)
project(effective_c++)

set(CMAKE_CXX_STANDARD 14)

include_directories(/)

file(GLOB SOURCES "/*.cpp" )

add_executable(effective_c++ main.cpp ${SOURCES})