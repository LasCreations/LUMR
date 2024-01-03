cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O3 -Wall -g")
project(LURM C CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/utils/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/CSR/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cache/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/database/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/controllers/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/models)

add_subdirectory(server)
add_subdirectory(utils)
add_subdirectory(CSR)
add_subdirectory(cache)
add_subdirectory(database)
add_subdirectory(controllers)


add_executable(LURM main.cpp)

find_package(jsoncpp REQUIRED)

cmake_policy(SET CMP0079 NEW)

target_link_libraries(controllers PUBLIC utils)

target_link_libraries(LURM PUBLIC
                            server
                            utils
                            CSR  
                            cache 
                            database
                            controllers
                            -lmysqlcppconn 
                            jsoncpp_lib
                    )


