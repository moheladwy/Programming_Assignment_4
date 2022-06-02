cmake_minimum_required(VERSION 3.21)
project(Text_Editor)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Text_Editor
        TextEditorApp.cpp
        TextEditorFunc.cpp
        TextEditorFunc.h)
