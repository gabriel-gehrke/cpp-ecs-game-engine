add_executable(${EXEC_NAME} main.cpp)

target_compile_features(${EXEC_NAME} PRIVATE cxx_std_17)
target_link_libraries(${EXEC_NAME} PRIVATE ${ENGINE_LIB_NAME})
