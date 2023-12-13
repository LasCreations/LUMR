cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O3 -Wall")
project(LURM C CXX)

# C++ source files
file(GLOB SOURCES 
        "api/src/*.cpp"
        "server/src/*.c"
        "main.c"
    )

# Include directories
include_directories(
    server/lib
    api/lib
)

# Create an executable for C++ sources
add_executable(LURM ${SOURCES})

target_include_directories(LURM PRIVATE server/lib api/lib)

# Set C++ standard
set_property(TARGET LURM PROPERTY CXX_STANDARD 11)  # adjust to your preferred C++ standard

# Compiler flags
target_compile_options(LURM PRIVATE -O3 -Wall)

find_package(jsoncpp REQUIRED)

# Link against MySQL libraries
target_link_libraries(LURM -lmysqlcppconn jsoncpp_lib)