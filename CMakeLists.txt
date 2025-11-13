cmake_minimum_required(VERSION 3.10)
project(CyberRT-MX C CXX ASM)
enable_language(ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(/usr/local/include) 
include_directories(src)
link_directories(/usr/local/lib)

include_directories(/)
include_directories(cyber)
include_directories(thirdparty)

file(GLOB_RECURSE SOURCES cyber/*.cpp)

add_library(cyber_mx ${SOURCES})
link_libraries(cyber_mx 
    uuid
    pthread
)