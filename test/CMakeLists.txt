file(GLOB_RECURSE TEST_SOURCES ${CMAKE_SOURCE_DIR}/test/*.cpp)

message(${TEST_SOURCES})
add_executable(system-test-exe ${TEST_SOURCES})
target_link_libraries(system-test-exe ${ENGINE_LIB_NAME})

add_test(NAME System-Test
        COMMAND system-test-exe)



add_custom_target(system-test COMMAND ${CMAKE_CTEST_COMMAND}
        DEPENDS system-test)