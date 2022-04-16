#add all sources and headers recursively
file(GLOB_RECURSE HEADER ${CMAKE_SOURCE_DIR}/include/engine/*.h)
file(GLOB_RECURSE PROJECT_SOURCE ${CMAKE_SOURCE_DIR}/src/*.cpp)

# sets the Library that contains the engine code

#create the engine lib with all source and header files
add_library(${ENGINE_LIB_NAME} ${PROJECT_SOURCE} ${HEADER})
#link SDL2 lib to the engine lib
target_link_libraries(${ENGINE_LIB_NAME} ${SDL2_LIBRARIES})
#link SDL2_image lib to the engine Lib
target_link_libraries(${ENGINE_LIB_NAME} SDL2_image)


target_include_directories(${ENGINE_LIB_NAME} PUBLIC ../include)
target_compile_features(${ENGINE_LIB_NAME} PUBLIC cxx_std_17)

source_group(
        TREE "${PROJECT_SOURCE_DIR}/include"
        PREFIX "Header Files"
        FILES ${HEADER}
)