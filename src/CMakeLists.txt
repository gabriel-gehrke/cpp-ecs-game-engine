# add all sources and headers recursively
file(GLOB_RECURSE HEADER ${CMAKE_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE PROJECT_SOURCE ${CMAKE_SOURCE_DIR}/src/*.cpp)


# add resources file
list(APPEND PROJECT_SOURCE ${CMAKE_SOURCE_DIR}/build/resources.cpp)

# TEMP: Temporary solution to make cmake build easily compatible with make build
list(REMOVE_ITEM PROJECT_SOURCE ${CMAKE_SOURCE_DIR}/src/main.cpp)

# sets the Library that contains the engine code

# create the engine lib with all source and header files
add_library(${ENGINE_LIB_NAME} ${PROJECT_SOURCE} ${HEADER})

# link SDL2 and SDL2_image lib to the engine lib

target_link_libraries(${ENGINE_LIB_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${ENGINE_LIB_NAME} ${SDL2IMAGE_LIBRARIES})
target_link_libraries(${ENGINE_LIB_NAME} ${SDL2TTF_LIBRARIES})


target_include_directories(${ENGINE_LIB_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_features(${ENGINE_LIB_NAME} PUBLIC cxx_std_17)

source_group(
        TREE "${CMAKE_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${HEADER}
)