
file(GLOB SOURCES "src/*.cpp")

add_library(cache STATIC ${SOURCES})
target_include_directories(cache PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)