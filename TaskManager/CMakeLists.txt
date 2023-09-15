
cmake_minimum_required(VERSION 3.10)

project(TaskManager)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR}/include)


add_executable(TaskManager 
    db/sqlite3.o
    src/main.cpp 
    src/models/Board.cpp 
    src/models/Task.cpp 
    src/utils/commands.cpp
    src/utils/DBManager.cpp
)

