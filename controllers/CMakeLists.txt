file(GLOB SOURCES "src/*.cpp")

add_library(controllers STATIC ${SOURCES})

target_include_directories(controllers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)