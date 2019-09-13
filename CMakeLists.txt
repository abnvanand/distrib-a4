cmake_minimum_required(VERSION 3.15)
project(distrib_a4)

set(CMAKE_CXX_STANDARD 14)

add_executable(distrib_a4 main.cpp)
include_directories(/home/abnv/.openmpi/include)