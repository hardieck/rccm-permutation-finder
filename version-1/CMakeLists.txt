cmake_minimum_required(VERSION 3.5)  # CMake version check
project(MCM_Permutatation)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard


include_directories ("${PROJECT_SOURCE_DIR}/inc/")
include_directories ("${PROJECT_SOURCE_DIR}/src/")

# put the executable in ./bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/)


install(FILES ${HEADERS}
		DESTINATION src
		)

file(GLOB SOURCES
src/main.cpp
src/mcm_permutation.cpp
src/permutator.cpp
src/structure.cpp
src/structures.cpp
)

add_executable(MCM_Permutation ${SOURCES})

set( CMAKE_BUILD_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/)

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/bin/" ) #->define path for archive
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/bin/" ) #->define path for Library
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/bin/" ) #->define path for Runtim



# Add main.cpp file of project root directory as source file
set(SOURCE_FILES main.cpp)
