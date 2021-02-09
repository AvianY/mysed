cmake_minimum_required(VERSION 3.5)

project(mysed LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libs/argparse)

add_executable(mysed main.cc)
target_link_libraries(mysed argparse)

file(COPY "thefile.txt" DESTINATION ${CMAKE_BINARY_DIR})
