
file(GLOB SOURCES "src/*.cpp")

add_library(server STATIC ${SOURCES})
target_include_directories(server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)