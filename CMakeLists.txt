cmake_minimum_required(VERSION 3.10)
project(CyberRT-MX C CXX ASM)
enable_language(ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(FastDDS_INSTALL "/home/yang/Fast-DDS/install")

set(CMAKE_BUILD_RPATH "${FastDDS_INSTALL}/lib")
set(CMAKE_INSTALL_RPATH "${FastDDS_INSTALL}/lib")
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
# 禁用 RUNPATH，使用传统的 RPATH（对间接依赖有效）
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--disable-new-dtags")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--disable-new-dtags")

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories(/usr/local/include) 
include_directories(src)
link_directories(/usr/local/lib)
link_directories(${FastDDS_INSTALL}/lib)

include_directories(/)
include_directories(cyber)
include_directories(thirdparty)
include_directories(${FastDDS_INSTALL}/include)

file(GLOB_RECURSE SOURCES cyber/*.cpp)

add_library(cyber_mx ${SOURCES})
link_libraries(cyber_mx
    uuid
    pthread
    fastrtps
)

add_subdirectory(example)