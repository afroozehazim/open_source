#ifndef ALP_CONFIG_HPP
#define ALP_CONFIG_HPP

#include <cstddef>
#include <cmath>

/*
 * ALP Configs
 */
namespace alp { namespace config {
// ALP Vector size (We recommend against changing this; it should be constant)
constexpr size_t ALP_VECTOR_SIZE = 1024;
// Rowgroup size 
constexpr size_t ALP_ROWGROUP_SIZE = 100UL * ALP_VECTOR_SIZE;
// Vectors from the rowgroup from which to take samples; this will be used to then calculate the jumps
constexpr size_t ROWGROUP_VECTOR_SAMPLES = 8;
// We calculate how many equidistant vector we must jump within a rowgroup
constexpr size_t ROWGROUP_SAMPLES_JUMP = (ALP_ROWGROUP_SIZE / ROWGROUP_VECTOR_SAMPLES) / ALP_VECTOR_SIZE;
// Values to sample per vector
constexpr size_t SAMPLES_PER_VECTOR = 32;
// Maximum number of combinations obtained from row group sampling
constexpr size_t MAX_K_COMBINATIONS = 5;
// 48 bits per value * 32 values in the sampled vector
constexpr size_t RD_SIZE_THRESHOLD_LIMIT = 48 * SAMPLES_PER_VECTOR; 
constexpr size_t CUTTING_LIMIT = 16;
constexpr size_t MAX_RD_DICT_BIT_WIDTH = 3;
constexpr size_t MAX_RD_DICTIONARY_SIZE = (1 << MAX_RD_DICT_BIT_WIDTH);

}} // namespace alp::config

using namespace alp::config;
#endif