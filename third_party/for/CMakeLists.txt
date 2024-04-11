add_library(alp_ffor OBJECT
        fallback_scalar_av_1024_uf1_ffor_src.cpp
        fallback_scalar_av_1024_uf1_unffor_src.cpp
        alp_ffor.cpp
        alp_unffor.cpp)

target_compile_definitions(alp_ffor PRIVATE IS_SCALAR)
set(FLAG -o3)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if (HAS_FLAG)
else ()
    message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif ()
target_compile_options(alp_ffor PUBLIC ${FLAG})

cmake_print_properties(TARGETS alp_ffor
        PROPERTIES COMPILE_DEFINITIONS
        PROPERTIES COMPILE_OPTIONS)
LIST(APPEND ALP_GENERATED_OBJECT_FILES
        $<TARGET_OBJECTS:alp_ffor>)

get_target_property(TARGET_NAME alp_ffor NAME)
get_target_property(TARGET_COMPILE_OPTIONS alp_ffor COMPILE_OPTIONS)