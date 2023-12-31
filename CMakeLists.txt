cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O3 -Wall -g")
project(LURM C CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/utils/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/models)

add_subdirectory(server)
add_subdirectory(utils)

add_executable(LURM main.cpp)

find_package(jsoncpp REQUIRED)

target_link_libraries(LURM PUBLIC server utils -lmysqlcppconn jsoncpp_lib)