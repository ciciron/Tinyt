cmake_minimum_required(VERSION 3.5)

add_executable(realm_t realmtest.cpp)
target_link_libraries(realm_t tinysrv GTest::gtest_main GTest::gmock)
add_test(NAME realm_test COMMAND realm_t DESCRIPTION "Realm")

add_executable(srvc_t srvctest.cpp)
target_link_libraries(srvc_t tinysrv GTest::gtest_main GTest::gmock)
add_test(NAME srvc_test COMMAND srvc_t DESCRIPTION "Service")