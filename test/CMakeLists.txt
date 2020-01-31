cmake_minimum_required(VERSION 3.5)

add_executable(srvc_test srvctest.cpp)
target_link_libraries(srvc_test tinysrv GTest::gtest_main GTest::gmock)
add_test(NAME srvc_test COMMAND srvc_test)
