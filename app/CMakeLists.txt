# add all source files belonging to the executable
file(GLOB_RECURSE EXEC_SOURCE ${CMAKE_SOURCE_DIR}/app/*.cpp)

# TEMP: Temporary solution to make cmake build easily compatible with make build
list(APPEND EXEC_SOURCE ${CMAKE_SOURCE_DIR}/src/game/main.cpp)

add_executable(${EXEC_NAME} ${CMAKE_SOURCE_DIR}/src/game/main.cpp)

target_compile_features(${EXEC_NAME} PRIVATE cxx_std_17)
target_link_libraries(${EXEC_NAME} PRIVATE ${ENGINE_LIB_NAME})
