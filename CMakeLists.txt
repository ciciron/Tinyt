cmake_minimum_required (VERSION 3.5)

project (TinyTestServer)

set (${PROJECT_NAME}_VERSION_MAJOR 1)
set (${PROJECT_NAME}_VERSION_MINOR 1)
set (${PROJECT_NAME}_VERSION_PATCH 1)
set (${PROJECT_NAME}_VERSION_TWEAK 1)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pthread -std=c++14")

include_directories("${PROJECT_SOURCE_DIR}/include/")
file (GLOB source_files "src/*.cpp")

add_executable (TinyTestServer ${source_files})
