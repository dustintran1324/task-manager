cmake_minimum_required(VERSION 3.26)
project(DLLTaskManager)
set(CMAKE_CXX_STANDARD 14)
include_directories(.)

add_executable(DLLTaskManager
        MainDLL.cpp
        DLL.cpp
        DLL.hpp
        DNode.cpp
        DNode.hpp
        Task.cpp
        Task.hpp
        TaskManager.cpp
        TaskManager.hpp
)