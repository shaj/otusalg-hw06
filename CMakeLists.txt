cmake_minimum_required(VERSION 3.2)

set(PROJ_NAME l6)

project(${PROJ_NAME})

find_package(Threads)

add_executable(${PROJ_NAME} main.cpp generators.cpp)

set_target_properties(${PROJ_NAME} PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

target_link_libraries(${PROJ_NAME}
  ${CMAKE_THREAD_LIBS_INIT}
)

