cmake_minimum_required(VERSION 3.19)
project(3d-constructor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -O3)

add_subdirectory(engine)
add_subdirectory(ui)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC engine)
target_link_libraries(${PROJECT_NAME} ui)
target_include_directories(${PROJECT_NAME} PRIVATE ui/qt)
