cmake_minimum_required( VERSION 2.8 )
project(Viterbi)


find_package(SystemCLanguage CONFIG REQUIRED)
set (CMAKE_CXX_STANDARD ${SystemC_CXX_STANDARD})

add_executable(${PROJECT_NAME}
	ViterbiEncoder.cpp
	ViterbiEncoder.h
	driver.cpp
	testbench.cpp
	monitor.cpp
	monitor.h)

target_link_libraries(${PROJECT_NAME}
	SystemC::systemc)
