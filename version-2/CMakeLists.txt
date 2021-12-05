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
        src/calc_rccm_base.cpp
        src/calc_rccm_C3.cpp
        src/calc_selective_adder_base.cpp
        src/calc_selective_adder_typ_a.cpp
        src/calc_selective_adder_typ_b.cpp
        src/evaluate_result.cpp
        src/selective_add.cpp
        src/rccm.cpp
        src/permutator.cpp
        inc/rccm.h
        inc/evaluate_result.h
        inc/selective_add.h
        inc/calc_rccm_base.h
        inc/calc_rccm_C3.h
        inc/calc_selective_adder_base.h
        inc/permutator.h
        inc/calc_selective_adder_typ_a.h
        inc/calc_selective_adder_typ_b.h inc/debug.h src/debug.cpp src/base_obj.cpp inc/base_obj.h inc/datatyps.h src/calc_rccm_C1.cpp inc/calc_rccm_C1.h inc/calc_base.h src/helper.cpp inc/helper.h src/calc_rccm_C2.cpp inc/calc_rccm_C2.h src/search_space_plan.cpp inc/search_space_plan.h src/calc_selective_adder_typ_c.cpp inc/calc_selective_adder_typ_c.h src/evaluate_base.cpp inc/evaluate_base.h src/evaluate_count.cpp inc/evaluate_count.h)
