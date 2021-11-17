cmake_minimum_required(VERSION 3.10) 

project(TFCore VERSION 0.1)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
set(GCC_COVERAGE_LINK_FLAGS "-lpthread")

add_executable(TFCore main.cc)

set(CMAKE_CXX_FLAGS  ${GCC_COVERAGE_LINK_FLAGS})
# SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

# target_link_libraries(TFCore test)
# aux_source_directory(. DIR_LIB_SRCS)
# add_library(test ${DIR_LIB_SRCS})