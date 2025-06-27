cmake_minimum_required(VERSION 3.13)
set(target "rp2x_sim7080g_lib")

project(${target} C CXX ASM)
add_library(${target} INTERFACE)

target_sources(${target} INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/src/rp2x_sim7080g.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/command_buffer.c
	${CMAKE_CURRENT_SOURCE_DIR}/src/response_parser.c
)

target_include_directories(${target} INTERFACE 
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${target} INTERFACE
	pico_stdlib
	hardware_spi
	pico_rand
)
