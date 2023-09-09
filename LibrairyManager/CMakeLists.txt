cmake_minimum_required(VERSION 3.10)

project(MyLibraryProject)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR})

add_library(Book SHARED Book.cpp Book.h)
add_library(Library SHARED Library.cpp Library.h)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE Book Library)
