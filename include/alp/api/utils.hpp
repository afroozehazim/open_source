#ifndef ALP_API_UTILS_HPP
#define ALP_API_UTILS_HPP

#include "alp/config.hpp"

#include <random>
#include <cmath>

namespace alp {
struct AlpApiUtils {

    static size_t get_rowgroup_count(size_t values_count){
        return std::ceil((double)values_count / ALP_ROWGROUP_SIZE);
    };

    static size_t get_vector_count(size_t values_count){
        return std::floor((double)values_count / ALP_VECTOR_SIZE); // Floor because we dont want to directly compress incomplete vectors
    }

    /*
     * Function to get the size of a vector after bit packing 
     * Note that we always store ALP_VECTOR_SIZE size vectors
     */
    static size_t get_size_after_bitpacking(uint8_t bit_width){
        return align_value<size_t, 8>(ALP_VECTOR_SIZE * bit_width) / 8;
    }

    template<class T, T val=8>
    static inline T align_value(T n) {
        return ((n + (val - 1)) / val) * val;
    }

    static void fill_random_data(double* in, size_t tuples_to_generate, uint8_t precision){
        std::uniform_real_distribution<double> unif(100, 300);
        std::default_random_engine re;
        re.seed(42);
        uint8_t doubles_intrinsic_precision = precision;
        const double precision_multiplier = std::pow(10.0, doubles_intrinsic_precision);
        for (size_t i = 0; i < tuples_to_generate; i++){
            double random_value = unif(re);
            double fixed_precision_random_value = std::round(random_value * precision_multiplier) / precision_multiplier;
            in[i] = fixed_precision_random_value;
        }
    }

    static void fill_incomplete_alp_vector(double* input_vector,
				   double* exceptions,
				   uint16_t* exceptions_positions,
				   uint16_t* exceptions_count,
				   int64_t* encoded_integers,
				   state& stt){
        // We fill a vector with 0s since these values will never be exceptions
        for (size_t i = stt.vector_size; i < ALP_VECTOR_SIZE; i++) {
            input_vector[i] = 0.0;
        }
        // We encode the vector filled with the dummy values
        alp::encode(input_vector, exceptions, exceptions_positions, exceptions_count, encoded_integers, stt);
        double a_non_exception_value = 0.0;
        // We lookup the first non exception value from the true vector values
        for (size_t i {0}; i < stt.vector_size; i++) {
            if (i != tmp_index[i]) {
                a_non_exception_value = input_vector[i];
                break;
            }
        }
        // We fill the vector with this dummy value
        for (size_t i = stt.vector_size; i < ALP_VECTOR_SIZE; i++) {
            input_vector[i] = a_non_exception_value;
        }
    }

    static void fill_incomplete_alprd_vector(double* input_vector, state& stt){
        // We just fill the vector with the first value
        double first_vector_value = input_vector[0];
        for (size_t i = stt.vector_size; i < ALP_VECTOR_SIZE; i++) {
            input_vector[i] = first_vector_value;
        }
    }

};
}

#endif