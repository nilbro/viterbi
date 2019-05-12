cmake_minimum_required( VERSION 2.8 )
project(Viterbi)

set (CMake_PREFIX_PATH /usr/local/systemc-2.3.2)

include_directories(${CMAKE_PREFIX_PATH}/include)

find_library(systemc systemc ${CMAKE_PREFIX_PATH}/lib-linux64)

add_executable(${PROJECT_NAME}
	ViterbiEncoder.cpp
	ViterbiEncoder.h
	driver.cpp
	testbench.cpp
	monitor.cpp)

target_link_libraries(${PROJECT_NAME}
	SystemC::systemc)

