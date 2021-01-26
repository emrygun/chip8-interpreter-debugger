cmake_minimum_required(VERSION 3.1)

if (CMAKE_VERSION VERSION_LESS "3.1")
  add_definitions(-std=c++11)
else()
  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

project(chip8interpreter-debugger)

find_package(Curses REQUIRED)

include_directories( ${CURSES_INCLUDE_DIRS} )

set(SOURCES
	src/main.c
	src/chip8.c
   	src/utils.c
	src/chip8.h
 	src/utils.h)

add_executable(chip8interpreter-debugger ${SOURCES})

target_link_libraries(chip8interpreter-debugger ${CURSES_LIBRARY})

install(TARGETS chip8interpreter-debugger DESTINATION make)
