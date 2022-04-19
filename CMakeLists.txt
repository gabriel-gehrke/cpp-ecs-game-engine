# Almost all CMake files should start with this
# You should always specify a range with the newest
# and oldest tested versions of CMake. This will ensure
# you pick up the best policies.
cmake_minimum_required(VERSION 3.12...3.23)

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()


# This is your project statement. You should always list languages;
# Listing the version is nice here since it sets lots of useful variables
project(
        cpp-ecs-game-engine
        VERSION 1.0
        LANGUAGES CXX)

set(ENGINE_LIB_NAME engine_lib)
set(EXEC_NAME game)

# If you set any CMAKE_ variables, that can go here.
# (But usually don't do this, except maybe for C++ standard)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Find packages go here.

# Add SDL2 library
find_package(SDL2 REQUIRED)
# Add SDL2 image
find_package(SDL2_image REQUIRED)

# Build resources
execute_process(
        COMMAND "python3" "${CMAKE_SOURCE_DIR}/scripts/make-resources.py"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

# add all CMakeList files to the
add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(test)

