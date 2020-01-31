cmake_minimum_required (VERSION 3.5)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules")

project (tinyts VERSION 1.0.1)

include(cxx-project-environ)

set(INCLUDE_BASE_DIR include)
set(INCLUDE_DIR ${INCLUDE_BASE_DIR})

file (GLOB include_files "${INCLUDE_BASE_DIR}/*.h")

#include_directories("${PROJECT_SOURCE_DIR}/include/")

set (abuser_src src/Main.cpp src/Abuser.cpp)
set (tinysrv_src src/Realm.cpp src/Commands.cpp src/ServerImpl.cpp)

add_library(tinysrv ${tinysrv_src})

set_library_properties(tinysrv
    BUILD_INCLUDE_DIRS
        ${PROJECT_SOURCE_DIR}/${INCLUDE_BASE_DIR}
    PUBLIC_HEADERS
        ${include_files}
    )

add_executable (tinyts ${abuser_src})
target_link_libraries(tinyts tinysrv)

create_library_package(
    PACKAGE tinysrv 
    TARGETS tinysrv
    NAMESPACE Once::
    RELATIVE_INCLUDE_DIR tinysrv
    )


find_package(GTest 1.8 CONFIG)

if (GTest_FOUND)
    message("Testing ON")
    set(test_enabled ENABLED)
    enable_testing()
endif()

add_test_option(
    OPTION TSRV_TEST
    ${test_enabled}
    TEST_DIRS test
    )

if (CLANG_TIDY)
    message("Clang tidy ON")
    add_for_code_static_analize(TARGET tinysrv)
    add_clang_tidy_check_target(clang-tidy-check)
endif()

