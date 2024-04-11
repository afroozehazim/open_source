cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
project(ALP)

add_compile_options(-fPIC)

# Options : ------------------------------------------------------------------------------------------------------------
option(BUILD_EXAMPLE "Build Example" OFF)

#-----------------------------------------------------------------------------------------------------------------------
include(FetchContent)
include(CheckCXXCompilerFlag)
include(CMakePrintHelpers)
include(CTest)

# Gtest: ---------------------------------------------------------------------------------------------------------------
include(GoogleTest)
FetchContent_Declare(googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Include --------------------------------------------------------------------------------------------------------------
include_directories(include)

# third_party: -------------------------------------------------------------------------------------------------------
add_subdirectory(third_party)

# ALP Primitives: -------------------------------------------------------------------------------------------------------
#add_subdirectory(alp_generated)

# ALP Benchmark: -------------------------------------------------------------------------------------------------------
add_subdirectory(alp_benchmarks)


# Example : ------------------------------------------------------------------------------------------------------------
if (BUILD_EXAMPLE)
    message("---------------------------------------------------------------------------------------------------------")
    message("- Example:")
    add_subdirectory(${CMAKE_SOURCE_DIR}/example)
endif ()