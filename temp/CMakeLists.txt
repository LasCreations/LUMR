cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-O3 -Wall -g")
project(LURM C CXX)

# C++ source files
file(GLOB SOURCES 
    "server/src/*.cpp"
    "routes/src/*.cpp"
    "controllers/src/*.cpp"
    "utils/*.cpp"
    "database/connection/src/*.cpp"
    "database/queries/src/*.cpp"
    "middleware/cache/src/*.cpp"
    "middleware/authenticate/src/*.cpp"
    "jsonparsing/src/*.cpp"
    )

# Include directories
include_directories(
    utils/
    controllers/lib
    server/lib
    routes/lib
    database/connection/lib
    database/queries/lib
    middleware/cache/lib
    middleware/authenticate/lib
    jsonparsing/lib
)

# Create an executable for C++ sources
add_executable(LURM ${SOURCES})

target_include_directories(LURM PRIVATE 
                                server/lib
                                routes/lib
                                utils/
                                controllers/lib
                                database/connection/lib
                                database/queries/lib
                                middleware/cache/lib
                                middleware/authenticate/lib
                                jsonparsing/lib
)

find_package(jsoncpp REQUIRED)

# Link against MySQL libraries
target_link_libraries(LURM -lmysqlcppconn jsoncpp_lib)