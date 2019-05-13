cmake_minimum_required( VERSION 2.8 )
project(Viterbi)

find_package(SystemCLanguage CONFIG REQUIRED)

set (CMAKE_CXX_STANDARD ${SystemC_CXX_STANDARD} CACHE STRING
     "C++ standard to build all targets. Supported values are 98, 11, and 14.")

set (CMAKE_CXX_STANDARD_REQUIRED ${SystemC_CXX_STANDARD_REQUIRED} CACHE BOOL
          "The with CMAKE_CXX_STANDARD selected C++ standard is a requirement.")

add_executable(${PROJECT_NAME}
	ViterbiEncoder.cpp
	ViterbiEncoder.h
	driver.cpp
	testbench.cpp
	monitor.cpp
	monitor.h)

target_link_libraries(${PROJECT_NAME}
	SystemC::systemc)
