cmake_minimum_required(VERSION 3.7 FATAL_ERROR)

project("Cloth_sim")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

add_executable(Generate main.cpp Point.h Spring.h Common.h Grid.h Cloth.h force.h integrate.h)

find_package(OpenMP)

if(OpenMP_CXX_FOUND)
	target_link_libraries(Generate PUBLIC OpenMP::OpenMP_CXX)
endif()

if (MSVC)

else()
	add_compile_options("$<$<CONFIG:Debug>:-Wall -Wextra -Wfloat-equal-Woverloaded-virtual -Wmissing-include-dirs -Wunknown-pragmas -Wduplicated-cond -Wshadow -Wpacked")
	add_compile_options("$<$<CONFIG:Release>:-O2")
endif()
