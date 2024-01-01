
file(GLOB SOURCES "src/*.cpp")

add_library(database STATIC ${SOURCES})
target_include_directories(database PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)