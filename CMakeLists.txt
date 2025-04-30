cmake_minimum_required(VERSION 3.10)
project(Autoclicker)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(vendors/XInputSimulator)
add_subdirectory(vendors/libuiohook)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} XInputSimulator uiohook)