cmake_minimum_required(VERSION 3.2)

set(PROJ_NAME l6)

project(${PROJ_NAME})

find_package(Threads)

add_executable(${PROJ_NAME} main.cpp)

set_target_properties(${PROJ_NAME} PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

target_link_libraries(${PROJ_NAME}
  ${CMAKE_THREAD_LIBS_INIT}
)

configure_file("${PROJECT_SOURCE_DIR}/1.py" "${PROJECT_BINARY_DIR}/1.py" COPYONLY)
# configure_file("${PROJECT_SOURCE_DIR}/1.txt" "${PROJECT_BINARY_DIR}/1.txt" COPYONLY)
# configure_file("${PROJECT_SOURCE_DIR}/shuffle.txt" "${PROJECT_BINARY_DIR}/shuffle.txt" COPYONLY)


