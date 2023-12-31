file(GLOB SOURCES "src/*.cpp")

add_library(CSR STATIC ${SOURCES})

target_include_directories(CSR PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)