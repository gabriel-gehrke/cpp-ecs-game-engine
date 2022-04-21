

add_executable(event-test-exe engine/event/event-test.cpp)
target_link_libraries(event-test-exe ${ENGINE_LIB_NAME})
add_test(NAME Event-System-Test
        COMMAND event-test-exe)



add_custom_target(event-test COMMAND ${CMAKE_CTEST_COMMAND}
        DEPENDS event-test)