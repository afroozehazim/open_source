# Test Patas: ----------------------------------------------------------------------------------------------------------
add_executable(test_patas test_patas.cpp)
target_link_libraries(test_patas PRIVATE gtest_main)
gtest_discover_tests(test_patas)


# Test CHIMP128: -------------------------------------------------------------------------------------------------------
add_executable(test_chimp128 test_chimp128.cpp)
target_link_libraries(test_chimp128 PRIVATE gtest_main)
gtest_discover_tests(test_chimp128)


# Test CHIMP: ----------------------------------------------------------------------------------------------------------
add_executable(test_chimp test_chimp.cpp)
target_link_libraries(test_chimp PRIVATE gtest_main)
gtest_discover_tests(test_chimp)


# Test GORILLAS: ----------------------------------------------------------------------------------------------------------
add_executable(test_gorillas test_gorillas.cpp)
target_link_libraries(test_gorillas PRIVATE gtest_main)
gtest_discover_tests(test_gorillas)


# Test ALP: ------------------------------------------------------------------------------------------------------------
add_executable(test_alp_vectorized test_alp.cpp)
target_link_libraries(test_alp_vectorized PRIVATE fallback_scalar_aav_1024_uf1_falp alp_ffor)
target_link_libraries(test_alp_vectorized PRIVATE gtest_main)
gtest_discover_tests(test_alp_vectorized)
set(FLAG -o3)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if (HAS_FLAG)
else ()
    message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif ()
target_compile_options(test_alp_vectorized PUBLIC ${FLAG})


# Test ZSTD: ----------------------------------------------------------------------------------------------------------
add_executable(test_zstd test_zstd.cpp)
target_link_libraries(test_zstd PRIVATE gtest_main)
target_link_libraries(test_zstd PRIVATE ${CMAKE_SOURCE_DIR}/include/zstd/libzstd.a)
gtest_discover_tests(test_zstd)
set(FLAG -o3)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if (HAS_FLAG)
else ()
    message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif ()
target_compile_options(test_zstd PUBLIC ${FLAG})
