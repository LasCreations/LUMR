cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O3 -Wall")
project(pageserving C CXX)

# C++ source files
file(GLOB SOURCES 
        "src/*.cpp"
        "src/*.c"
        "data/src/*cpp"
        "*cpp"
        )

# Include directories
include_directories(
    lib
)

# Create an executable for C++ sources
add_executable(pageserving ${SOURCES})

# Set C++ standard
set_property(TARGET pageserving PROPERTY CXX_STANDARD 11)  # adjust to your preferred C++ standard

# Link against MySQL libraries
target_link_libraries(pageserving -lmysqlcppconn)
