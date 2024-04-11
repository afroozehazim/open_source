# Bench ALP --------------------------------------------------------------------------------------------------------
configure_file(${CMAKE_SOURCE_DIR}/alp_bench/alp_bench.hpp ${CMAKE_CURRENT_BINARY_DIR}/bench_alp.hpp)
add_executable(bench_alp_encode bench_alp_encode.cpp)
target_include_directories(bench_alp_encode PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(bench_alp_encode PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_compile_options(bench_alp_encode PUBLIC)
target_link_libraries(bench_alp_encode PRIVATE fallback_scalar_aav_1024_uf1_falp alp_ffor)
set(FLAG -mavx512dq)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if (HAS_FLAG)
else ()
    message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif ()
target_compile_options(bench_alp_encode PUBLIC ${FLAG})


# Bench ALP CUTTER ENCODE ----------------------------------------------------------------------------------------------
configure_file(${CMAKE_SOURCE_DIR}/alp_bench/alp_bench.hpp ${CMAKE_CURRENT_BINARY_DIR}/bench_alp.hpp)
add_executable(bench_alp_cutter_encode bench_alp_cutter_encode.cpp)
target_include_directories(bench_alp_cutter_encode PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(bench_alp_cutter_encode PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_compile_options(bench_alp_cutter_encode PUBLIC)
target_link_libraries(bench_alp_cutter_encode PRIVATE alp_generated alp_ffor)
set(FLAG -mavx512dq)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if (HAS_FLAG)
else ()
    message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif ()
target_compile_options(bench_alp_cutter_encode PUBLIC ${FLAG})


# Bench ALP CUTTER DECODE ----------------------------------------------------------------------------------------------
configure_file(${CMAKE_SOURCE_DIR}/alp_bench/alp_bench.hpp ${CMAKE_CURRENT_BINARY_DIR}/bench_alp.hpp)
add_executable(bench_alp_cutter_decode bench_alp_cutter_decode.cpp)
target_include_directories(bench_alp_cutter_decode PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(bench_alp_cutter_decode PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_compile_options(bench_alp_cutter_decode PUBLIC)
target_link_libraries(bench_alp_cutter_decode PRIVATE alp_generated alp_ffor)
set(FLAG -mavx512dq)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if (HAS_FLAG)
else ()
    message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif ()
target_compile_options(bench_alp_cutter_decode PUBLIC ${FLAG})


# Bench ALP without SAMPLING --------------------------------------------------------------------------------------------------------
configure_file(${CMAKE_SOURCE_DIR}/alp_bench/alp_bench.hpp ${CMAKE_CURRENT_BINARY_DIR}/bench_alp_tmp.hpp)
add_executable(bench_alp_without_sampling bench_alp_without_sampling.cpp)
target_include_directories(bench_alp_without_sampling PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(bench_alp_without_sampling PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_compile_options(bench_alp_without_sampling PUBLIC)
target_link_libraries(bench_alp_without_sampling PRIVATE fallback_scalar_aav_1024_uf1_falp alp_ffor)
set(FLAG -mavx512dq)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if (HAS_FLAG)
else ()
    message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif ()
target_compile_options(bench_alp_without_sampling PUBLIC ${FLAG})


# Bench PATAS ----------------------------------------------------------------------------------------------------------
configure_file(${CMAKE_SOURCE_DIR}/alp_bench/alp_bench.hpp ${CMAKE_CURRENT_BINARY_DIR}/bench_patas.hpp)
add_executable(bench_patas bench_patas.cpp)
target_include_directories(bench_patas PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_compile_options(bench_patas PUBLIC)
set(FLAG -march=native)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if (HAS_FLAG)
else ()
    message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif ()
target_compile_options(bench_patas PUBLIC ${FLAG})


# Bench CHIMP128 -------------------------------------------------------------------------------------------------------
configure_file(${CMAKE_SOURCE_DIR}/alp_bench/alp_bench.hpp ${CMAKE_CURRENT_BINARY_DIR}/bench_chimp128.hpp)
add_executable(bench_chimp128 bench_chimp128.cpp)
target_include_directories(bench_chimp128 PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_compile_options(bench_chimp128 PUBLIC)
set(FLAG -march=native)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if (HAS_FLAG)
else ()
    message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif ()
target_compile_options(bench_chimp128 PUBLIC ${FLAG})


# Bench CHIMP ----------------------------------------------------------------------------------------------------------
configure_file(${CMAKE_SOURCE_DIR}/alp_bench/alp_bench.hpp ${CMAKE_CURRENT_BINARY_DIR}/bench_chimp.hpp)
add_executable(bench_chimp bench_chimp.cpp)
target_include_directories(bench_chimp PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_compile_options(bench_chimp PUBLIC)
set(FLAG -march=native)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if (HAS_FLAG)
else ()
    message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif ()
target_compile_options(bench_chimp PUBLIC ${FLAG})


# Bench GORILLAS -------------------------------------------------------------------------------------------------------
configure_file(${CMAKE_SOURCE_DIR}/alp_bench/alp_bench.hpp ${CMAKE_CURRENT_BINARY_DIR}/bench_gorillas.hpp)
add_executable(bench_gorillas bench_gorillas.cpp)
target_include_directories(bench_gorillas PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_compile_options(bench_gorillas PUBLIC)
set(FLAG -march=native)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if (HAS_FLAG)
else ()
    message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif ()
target_compile_options(bench_gorillas PUBLIC ${FLAG})

# Test ZSTD: ----------------------------------------------------------------------------------------------------------
configure_file(${CMAKE_SOURCE_DIR}/alp_bench/alp_bench.hpp ${CMAKE_CURRENT_BINARY_DIR}/bench_zstd.hpp)
add_executable(bench_zstd bench_zstd.cpp)
target_include_directories(bench_zstd PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(bench_zstd PRIVATE ${CMAKE_SOURCE_DIR}/include/zstd/libzstd.a)
target_compile_options(bench_zstd PUBLIC)
#set(FLAG -march=native)
set(FLAG -O3)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if (HAS_FLAG)
else ()
    message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif ()
target_compile_options(bench_chimp PUBLIC ${FLAG})