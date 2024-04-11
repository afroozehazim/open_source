add_library(wasm_simd128_intrinsic_1024_uf1_falp OBJECT
            wasm_simd128_intrinsic_1024_uf1_falp_src.cpp)
target_compile_definitions(wasm_simd128_intrinsic_1024_uf1_falp PRIVATE IS_SCALAR)
set(FLAG -msimd128)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if(HAS_FLAG)
else()
 message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif()
target_compile_options(wasm_simd128_intrinsic_1024_uf1_falp PUBLIC ${FLAG})
cmake_print_properties(TARGETS wasm_simd128_intrinsic_1024_uf1_falp
                       PROPERTIES COMPILE_DEFINITIONS
                       PROPERTIES COMPILE_OPTIONS)
LIST (APPEND ALP_GENERATED_OBJECT_FILES
      $<TARGET_OBJECTS:wasm_simd128_intrinsic_1024_uf1_falp>)
get_target_property(TARGET_NAME wasm_simd128_intrinsic_1024_uf1_falp NAME)
get_target_property(TARGET_COMPILE_OPTIONS wasm_simd128_intrinsic_1024_uf1_falp COMPILE_OPTIONS)
#------------------------------------------------------------------------------------------------------
add_executable(wasm_simd128_intrinsic_1024_uf1_falp_test wasm_simd128_intrinsic_1024_uf1_falp_test.cpp)
target_link_libraries(wasm_simd128_intrinsic_1024_uf1_falp_test PRIVATE wasm_simd128_intrinsic_1024_uf1_falp)
target_link_libraries(wasm_simd128_intrinsic_1024_uf1_falp_test PRIVATE alp_ffor)
target_link_libraries(wasm_simd128_intrinsic_1024_uf1_falp_test PRIVATE gtest_main)
target_include_directories(wasm_simd128_intrinsic_1024_uf1_falp_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
gtest_discover_tests(wasm_simd128_intrinsic_1024_uf1_falp_test)
#------------------------------------------------------------------------------------------------------
configure_file(${CMAKE_SOURCE_DIR}/alp_bench/alp_bench.hpp ${CMAKE_CURRENT_BINARY_DIR}/wasm_simd128_intrinsic_1024_uf1_falp_bench.hpp)
add_executable(wasm_simd128_intrinsic_1024_uf1_falp_bench wasm_simd128_intrinsic_1024_uf1_falp_bench.cpp)
target_link_libraries(wasm_simd128_intrinsic_1024_uf1_falp_bench PRIVATE wasm_simd128_intrinsic_1024_uf1_falp)
target_link_libraries(wasm_simd128_intrinsic_1024_uf1_falp_bench PRIVATE alp_ffor)
target_include_directories(wasm_simd128_intrinsic_1024_uf1_falp_bench PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
add_alp_benchmark(wasm_simd128_intrinsic_1024_uf1_falp_bench)
