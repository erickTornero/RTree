cmake_minimum_required(VERSION 3.22.1)
project(RTREE)
set(INCLUDES_DIR rtree/includes)
set(SOURCE_DIR rtree/src)
include_directories(${INCLUDES_DIR})
#target_include_directories(binary PRIVATE "./rtree/includes")
#set(SOURCES RTree.cpp Object.cpp RTree.hpp Objects.hpp source.cpp)


set(SOURCES ${SOURCE_DIR}/source.cpp ${SOURCE_DIR}/Objects.cpp ${SOURCE_DIR}/RTree.cpp)
add_executable(rtree ${SOURCES})