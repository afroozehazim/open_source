# ALP: Adaptive Lossless Floating-Point Compression
Lossless floating-point compression algorithm for `double`/`float` data type. ALP significantly improves previous floating-point encodings in both speed and compression ratio (figure below; each dot represents a dataset). We created ALP after carefully studying floating-point data found in real databases.

<p align="center">
        <img src="/alp_pub/alp_results.png" alt="ALP Benchmarks" height="350">
</p>


ALP high speeds stem from our implementation in scalar code that auto-vectorizes thanks to [FastLanes](https://github.com/cwida/FastLanes), and an efficient two-stage compression algorithm that first samples row-groups and then vectors to adapt to the data.

To **rigurously benchmark** ALP with your own data we mainly recommend using the [ALP primitives](#alp-primitives). To *quickly* test ALP we recommend following [our examples in the Quickstart guide](#quickstart) or [using it on DuckDB](#alp-in-duckdb) (note that ALP inside DuckDB is slower than using our primitives).

ALP details can be found in the [publication](https://dl.acm.org/doi/pdf/10.1145/3626717).

## Contents
  - [ALP in a Nutshell](#alp-in-a-nutshell)
  - [Quickstart](#quickstart)
  - [Building and Running](#building-and-running)
  - [ALP Primitives](#alp-primitives)
  - [ALP in DuckDB](#alp-in-duckdb)
  - [Replicating Paper Experiments](#replicating-paper-experiments)
    - [Build](#build)
    - [Downloading Data](#downloading-data)
    - [Environment Variables](#environment-variables)
    - [Setup Data](#setup-data)
    - [Compression Ratios Experiment](#compression-ratios-experiment)
    - [Speed Tests](#speed-tests)

## ALP in a Nutshell
ALP has two compression schemes: `ALP` for doubles/floats which were once decimals, and `ALP_RD` for true double/floats (e.g. the ones which stem from many calculations). 

`ALP` transforms doubles/floats to integer values with two multiplications to FOR+BitPack them into only the necessary bits. This is an strongly enhanced version of [PseudoDecimals](https://dl.acm.org/doi/abs/10.1145/3589263).

`ALP_RD` splits the doubles/floats bitwise representations into two parts (left and right). The left part is encoded with a Dictionary compression and the right part is Bitpacked to just the necessary bits.

Both encodings operate in vectors of 1024 values at a time (fit vectorized execution) and leverage in-vector commonalities to achieve higher compression ratios than other methods (Chimp128, Elf, PseudoDecimals, Zstd, Patas).

## Quickstart 

[Usage examples](/examples/) are available under the `examples` directory. In here, we use a simple [de]compression API to store/read ALP data in/from memory. 
- [Simple compress](/examples/simple_compress.cpp): An example to compress a buffer of random doubles with limited decimal precision.   
- [RD Compress](/examples/rd_compress.cpp): An example to directly compress using `ALP_RD` scheme if the data are true doubles.
- [Adaptive Compress](/examples/adaptive_compress.cpp): An example in which half of the data is of limited decimal precision and half of the data are true doubles.  

***Note that the [de]compression API used by these examples is only a wrapper of the real ALP core: the primitives. As such, it may contain bugs or unoptimized statements. 

## Building and Running
Requirements: 
1) __Clang++__
2) __CMake__ 3.20 or higher

Building and running the [simple compress](/examples/simple_compress.cpp) example:
```sh
cmake .
make
cd examples && ./simple_compress
```

This will also generate the ALP Primitives.


## ALP Primitives
You can make your own [de]compression API by using ALP primitives. An example of the usage of these can be found in our simple [compression API](/include/alp/api/). The decoding primitives of ALP are auto-vectorized thanks to [FastLanes](https://github.com/cwida/FastLanes). For **benchmarking** purposes, we recommend you to use these primitives.

You can use these by including our library in your code: `#include "alp/alp.hpp"`

### ALP

#### alp::init
```c++
init(double* data_column, 
    size_t column_offset, 
    size_t tuples_count, 
    double* sample_arr, 
    alp::state& stt)
```
Initializes the algorithm by performing the first-level sampling on the `data_column` buffer and deciding the adequate scheme to use (by default `ALP`). The sampling is performed from the `column_offset` index until `column_offset + ALP_ROUWGROUP_SIZE`. 

#### alp::encode
```c++
encode( double* input_vector,
        double* exceptions,
        uint16_t* exceptions_positions,
        uint16_t* exceptions_count,
        int64_t* encoded_integers,
        alp::state& stt)
```
Uses `ALP` to encode the values in `input_vector` into integers using the state (`stt`) `factor` and `exponent`. Encoded values are stored in `encoded_integers` alongside their `exceptions`, their `exceptions_positions` and the `exceptions_count`. Input vector is assumed to point to `ALP_VECTOR_SIZE` (1024) elements. On here, the second-level sampling is performed if neccessary. 

#### alp::generated::ffor::fallback::scalar::ffor
```c++
ffor(int64_t* in, 
    int64_t* out, 
    uint8_t bit_width, 
    int64_t* ffor_base)
```
Encode `in` using FFOR (FOR + BP) and writing to `out`. `in` is assumed to point to `ALP_VECTOR_SIZE` (1024) elements. The target `bit_width` and the frame of reference (`ffor_base`) must be given. `alp::analyze_ffor()` primitive can be used to obtain both from an array of integers.


#### alp::analyze_ffor
```c++
analyze_ffor(int64_t* input_vector, 
            uint8_t& bit_width, 
            int64_t* ffor_base)
```
Reads values in `input_vector` and set the proper `bit_width` and frame of reference (`ffor_base`) to compress the array. 

#### alp::decode
```c++
decode(uint64_t* encoded_integers, 
        uint8_t fac_idx, 
        uint8_t exp_idx, 
        double* output)
```
Uses `ALP` to decode the values in `encoded_integers` into `output` using `factor` and `exponent` for the decoding multiplication. The size of the encoded integers array and the output buffer are assumed to be `ALP_VECTOR_SIZE` (1024).

#### alp::generated::unffor::fallback::scalar::unffor
```c++
unffor(int64_t* in, 
        int64_t* out, 
        uint8_t bit_width, 
        int64_t* ffor_base)
```
Decode `in` by reversing the FFOR (FOR + BP) and writing to `out`. `in` is assumed to point to `ALP_VECTOR_SIZE` (1024) elements. The target `bit_width` and the frame of reference (`ffor_base`) must be given. 

#### generated::falp::fallback::scalar::falp
```c++
falp(uint64_t* in,
    double* out,
    uint8_t bit_width,
    uint64_t* ffor_base,
    uint8_t factor,
    uint8_t exponent)
```
Fused implementation of `decode` and `unffor`. Decode `in` with ALP, reverse the FFOR (FOR + BP) and write to `out`. `in` is assumed to point to `ALP_VECTOR_SIZE` (1024) elements. The target `bit_width`, the frame of reference (`ffor_base`), and the encoding `factor` and `exponent` indexes must be given. 

#### alp::patch_exceptions
```c++
patch_exceptions(double* output, 
                double* exceptions, 
                uint16_t* exceptions_positions, 
                uint16_t* exceptions_count)
```
Patch the exceptions in `output` using their positions and respective count.


### ALP_RD
#### alp::rd_init
```c++
rd_init(double* data_column, 
        size_t column_offset, 
        size_t tuples_count, 
        double* sample_arr, 
        alp::state& stt)
```
Initializes the algorithm by performing the first-level sampling on the `data_column` buffer. The sampling is performed from the `column_offset` index until `column_offset + ALP_ROUWGROUP_SIZE`. Afterwards, the best position to cut the floating-point values is found and the dictionary to encode the left parts is built and stored in `stt.left_parts_dict`.

#### alp::rd_encode
```c++
rd_encode(const double* input_vector,
        uint16_t*     exceptions,
        uint16_t*     exception_positions,
        uint16_t*     exceptions_count,
        uint64_t*     right_parts,
        uint16_t*     left_parts,
        alp::state&   stt)
```
Uses `ALPRD` to encode the values in `input_vector` into their left and right parts alongside their `exceptions`, their `exceptions_positions` and the `exceptions_count`. Input vector is assumed to point to `ALP_VECTOR_SIZE` (1024) elements. On here, the second-level sampling is performed if neccessary. 

#### alp::rd_decode
```c++
rd_decode(double* a_out, 
            uint64_t* unffor_right_arr,  
            uint16_t* unffor_left_arr, 
            uint16_t* exceptions, 
            uint16_t* exceptions_positions, 
            uint16_t* exceptions_count,
            state& stt)
```
Uses `ALP_RD` to decode the values in `unffor_right_arr` and `unffor_left_arr` by glueing them. The size of the encoded integers array and the output buffer are assumed to be `ALP_VECTOR_SIZE` (1024). Exception patching is fused in this function. 

### Using the Primitives

##### Rowgroup Primitives
Both `init` and `rd_init` are primitives that should be called per rowgroup. They set the neccessary `state` that other primitives need. All other primitives should be called per vector.

##### ALP Encoding
Encoding is comprised of the `encode`, `analyze_ffor`, and `ffor` primitives. 

##### ALP Decoding
Fused decoding is comprised of the `falp` and the `patch_exceptions` primitives. Unfused decoding is comprised of the `unffor`, `decode` and `patch_exceptions` primitives. 

##### ALP RD Encoding
Encoding is comprised of `rd_encode` and two calls to `ffor` (for both the left and right parts).

##### ALP RD Decoding
Decoding is comprised of two calls to `unffor` (for both the left and right parts) and the `rd_decode` primitives. 

##### Last Vector Encoding (`vector_size != ALP_VECTOR_SIZE`)
ALP primitives operate on blocks of 1024 values. Using 1024 as a constant value in loops enables the optimizer to easily auto-vectorize code. This means that for the majority of datasets the last vector may be incomplete. A few strategies can be implemented to encode an incomplete vector:   
- Fill the missing values of the vector with the first value. Pros: Easy to implement and efficient. Cons: Value may be an exception, which will lead to a bunch of exceptions being encoded.   
- Fill the missing values with `0.0`. Pros: Easy to implement and efficient. Cons: Could negatively affect the bit width of the vector after FFOR (or the exceptions number in ALP_RD).   
- Fill the vector with the first non-exception value after encoding (implemented in our example Compression API). Pros: Will yield the best compression ratio for the last vector. Cons: The vector must be encoded twice.   

## ALP in DuckDB
There is [an implementation of ALP](https://github.com/duckdb/duckdb/pull/9635) written inside DuckDB (using DuckDB compression API). Inside DuckDB, ALP is **x2-4 times faster** than Patas (at decompression) achieving **twice as high compression ratios** (sometimes even much more). DuckDB can be used to quickly test ALP on custom data, however we advise against doing so if your purpose is to rigurously benchmark ALP against other algorithms.

[Here](https://github.com/duckdb/duckdb/blob/main/benchmark/micro/compression/alp/alp_read.benchmark) you can find a basic example on how to load data in DuckDB forcing ALP to be used as compression method. These statements can be called using the Python API.

**Please note**: In this implementation we adhere to DuckDB compression API which restricted us from doing certain optimizations. That being said, for scientific purposes we do NOT recommend to benchmark ALP inside DuckDB: i) It is slower than using our primitives presented here, and ii) compression ratios can be slighly worse due to the metadata needed to skip vectors and DuckDB storage layout.

To benchmark ALP against other algorithms we recommend mainly using the [ALP primitives](#alp-primitives) by taking a look at our simple [compression API](/include/alp/api/).


## Replicating Paper Experiments
Here we estate how to replicate the experiments presented in our [publication](https://dl.acm.org/doi/pdf/10.1145/3626717). To test ALP with your own data we recommend either following [the examples](/examples/) or implementing the ALP primitives in your own compression API. 


### Build


```shell
mkdir build ; cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=../alp_toolchains/example.cmake ..
make
```

### Downloading Data

Inside `data/datasets_transformer.ipynb` you can find a [Jupyter Notebook script](/data/datasets_transformer.ipynb) to download the datasets we present in the [publication](https://dl.acm.org/doi/pdf/10.1145/3626717) and convert them to a binary format (64 bits doubles). Note that some of these require a heavy pre-processing phase.

### Environment Variables
If needed, set the environment variables `DATASETS_COMPLETE_PATH`, `DATASETS_1024_SAMPLES_PATH`, `ALP_RESULT_DIR_PATH`; either on your env, or manually on the [dataset.hpp](/include/dataset.hpp) file. These variables configure where to find the datasets relative to where the test executable is located. 

### Setup Data
Inside `include/datasets.hpp` you can find an array containing information regarding the datasets used to benchmark ALP. Datasets information include a path to a sample of one vector (1024 values) in CSV format (inside `/data/1024_data_samples/`), and a path to the entire file in binary format. The binary file is used to benchmark ALP compression ratios, while the CSV sample is used to benchmark ALP speed. To ensure the correctness of the speed tests we also keep extra variables from each dataset, which include the number of exceptions and the bitwidth resulting after compression (unless the algorithm change, these should remain consistent), and the factor/exponent indexes used to encode/decode the doubles into integers. 

To setup the data you want to run the test on, add or remove entries in the array found in [datasets.hpp](/include/datasets.hpp) and `make` again. The data needed for each entry is detailed in [dataset.hpp](/include/dataset.hpp). To replicate the compression ratio tests you only need to set the dataset id, name, and binary_file_path. 

### Compression Ratios Experiment
After building and setting up the data, run the following:
```sh
cd alp_benchmarks/speed/test/ && ./test_alp_vectorized
```
This will execute the tests found in the [test_alp.cpp](/alp_benchmarks/speed/test/test_alp.cpp) file, which will compress an entire binary file and write the resulting (estimated) compression ratio results (in bits/value) from the datasets in [datasets.hpp](/include/datasets.hpp), on the `alp_pub` directory. One CSV file will be created for the datasets which use the `ALP` scheme and another one for the ones which uses the `ALP_RD` scheme. Note that this is a dry compression (compressed data is not stored).

### Speed Tests

All of these tests read the CSV sample files locations from the dataset array. Therefore, to test with your own data, add your dataset to this array. Note that these experiments are performed on 1024 values. Why? Check Section 4 of the [publication](https://dl.acm.org/doi/pdf/10.1145/3626717).

#### ALP Encoding Speed Test
Encoding is comprised of the `encode`, `analyze_ffor`, and `ffor` primitives. Benchmarked by running: `./alp_benchmarks/speed/bench/bench_alp_encode`. Results are located on `alp_pub/results/`.

#### ALP Decoding Speed Test
Fused decoding is comprised of the `falp` and the `patch_exceptions` primitives. Unfused decoding is comprised of the `unffor`, `decode` and `patch_exceptions` primitives. Benchmark both fused and unfused at the same time on different implementations and Architectures/ISAs by running the commands below. Results are located on `alp_pub/results/`.

| Implementation  | Command                                                                                                    |
|-----------------|------------------------------------------------------------------------------------------------------------|
| Scalar          | `./alp_generated/fallback/scalar_nav_uf1/fallback_scalar_nav_1024_uf1_falp_bench`                          |
| SIMD            | `./alp_generated/{Arch}/{Arch}_{extension}_intrinsic_uf1/{Arch}_{extension}_intrinsic_1024_uf1_falp_bench` |
| Auto-Vectorized | `./alp_generated/fallback/scalar_aav_uf1/fallback_scalar_aav_1024_uf1_falp_bench`                          |

While the *correctness* can be tested by running:

| Implementation  | Command                                                                                                   |
|-----------------|-----------------------------------------------------------------------------------------------------------|
| Scalar          | `./alp_generated/fallback/scalar_nav_uf1/fallback_scalar_nav_1024_uf1_falp_test`                          |
| SIMD            | `./alp_generated/{Arch}/{Arch}_{extension}_intrinsic_uf1/{Arch}_{extension}_intrinsic_1024_uf1_falp_test` |
| Auto-Vectorized | `./alp_generated/fallback/scalar_aav_uf1/fallback_scalar_aav_1024_uf1_falp_test`                          |

The source file of the `falp` primitive (FUSED ALP+FOR+Bitpack generated by [FastLanes](https://github.com/cwida/FastLanes)) for each different implementation are at:

| Implementation  | Source File                                                                                                |
|-----------------|------------------------------------------------------------------------------------------------------------|
| Scalar          | `alp_generated/fallback/scalar_nav_uf1/fallback_scalar_nav_1024_uf1_falp_src.cpp`                          |
| SIMD            | `alp_generated/{Arch}/{Arch}_{extension}_intrinsic_uf1/{Arch}_{extension}_intrinsic_1024_uf1_falp_src.cpp` |
| Auto-Vectorized | `alp_generated/fallback/scalar_aav_uf1/fallback_scalar_aav_1024_uf1_falp_src.cpp`                          |


Architectures and ISAs:

| Architecture {Arch} | ISA {extension}    |
|--------------|---------|
| arm64v8      | neon    |
| arm64v8      | sve     |
| wasm         | simd128 |
| x86_64       | sse     |
| x86_64       | avx2    |
| x86_64       | avx512bw|

#### ALP RD Encoding Speed Test
Encoding is comprised of `rd_encode` and two calls to `ffor` (for both the left and right parts). Benchmarked by running: `./alp_benchmarks/speed/bench/bench_alp_cutter_encode`. Results are located on `alp_pub/results/`.

#### ALP RD Decoding Speed Test
Decoding is comprised of two calls to `unffor` (for both the left and right parts) and the `rd_decode` primitives. Benchmarked by running: `./alp_benchmarks/speed/bench/bench_alp_cutter_decode`. Results are located on `alp_pub/results/`.

#### Chimp, Chimp128, Gorillas, Patas, Zstd Speed Test
Benchmarked both decoding and encoding by running `./alp_benchmarks/speed/bench/bench_{algorithm}`, in which `algorithm` can be: `chimp|chimp128|gorillas|patas|zstd`. Results are located on `alp_pub/results/i4i`.

#### PseudoDecimals Speed Test
We benchmarked PseudoDecimals within BtrBlocks. Results are located on `alp_pub/results/i4i`.

#### ELF Speed Test
We benchmarked Elf using their Java implementation.

