cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O3 -Wall")
project(LUMR C CXX)

# C++ source files
file(GLOB SOURCES 
        "server/src/*.cpp"
        "server/src/*.c"
        "main.cpp"
        )

# Include directories
include_directories(
    lib
)

# Create an executable for C++ sources
add_executable(LUMR ${SOURCES})

# Set C++ standard
set_property(TARGET LUMR PROPERTY CXX_STANDARD 11)  # adjust to your preferred C++ standard

# Link against MySQL libraries
target_link_libraries(LUMR -lmysqlcppconn)
