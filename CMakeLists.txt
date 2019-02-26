cmake_minimum_required (VERSION 2.8.9)

project (s2dbanalyser)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -lboost_system -lboost_filesystem -lboost_regex -std=c++11")
set (source_dir "${PROJECT_SOURCE_DIR}/src/")
include_directories("${PROJECT_SOURCE_DIR}/include/")

file (GLOB source_files "${source_dir}/*.cpp" "${PROJECT_SOURCE_DIR}/include/*.h")

add_executable (s2dbanalyser ${source_files} "main.cpp")
