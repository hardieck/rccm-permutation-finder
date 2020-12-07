cmake_minimum_required(VERSION 3.14)
project(AddNet_Permutator_v2)

set(CMAKE_CXX_STANDARD 14)

set(dir ${CMAKE_CURRENT_SOURCE_DIR}/bin/)
set(EXECUTABLE_OUTPUT_PATH ${dir} CACHE PATH "build" FORCE)
set(LIBRARY_OUTPUT_PATH ${dir} CACHE PATH "build" FORCE)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir})
set(CMAKE_BUILD_FILES_DIRECTORY ${dir})
set(CMAKE_BUILD_DIRECTORY ${dir})
set(CMAKE_BINARY_DIR  ${dir})

SET(EXECUTABLE_OUTPUT_PATH ${dir}bin)
SET(LIBRARY_OUTPUT_PATH ${dir}lib)
SET(CMAKE_CACHEFILE_DIR ${dir})

add_executable(AddNet_Permutator_v2
        src/main.cpp
        src/rccm_base.cpp
        src/rccm_3add.cpp
        src/selective_adder_base.cpp
        src/selective_adder_typ_a.cpp
        src/selective_adder_typ_b.cpp
        src/evaluate_result.cpp
        src/config_selective_add.cpp
        src/config_rccm.cpp
        src/permutator.cpp
        inc/config_rccm.h
        inc/evaluate_result.h
        inc/config_selective_add.h
        inc/rccm_base.h
        inc/rccm_3add.h
        inc/selective_adder_base.h
        inc/permutator.h
        inc/selective_adder_typ_a.h
        inc/selective_adder_typ_b.h inc/debug.h src/debug.cpp inc/types.h src/base_obj.cpp inc/base_obj.h)
