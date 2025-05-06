add_executable(comp_club_tests CompClubTest.cpp)

target_link_libraries(comp_club_tests PRIVATE comp_club GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(comp_club_tests)