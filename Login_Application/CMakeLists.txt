cmake_minimum_required(VERSION 3.21)
project(Login_Application)
set(CMAKE_CXX_STANDARD 17)

# Set the build output location to a common directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(OpenXLSX)
add_executable(Login_Application LoginApp.cpp LoginFunc.h LoginFunc.cpp)
target_link_libraries(Login_Application OpenXLSX::OpenXLSX)