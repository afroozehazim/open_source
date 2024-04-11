#include "alp/alp.hpp"
#include "datasets.hpp"
#include "alp/ffor.hpp"
#include "alp/unffor.hpp"
#include "mapper.hpp"
#include "metadata.hpp"
#include "gtest/gtest.h"

namespace ffor = alp::generated::ffor::fallback::scalar;
namespace unffor = alp::generated::unffor::fallback::scalar;


/*
 * ALP overhead per vector in a hypothetic file format = bit_width + factor-idx + exponent-idx + ffor base;
 */
double overhead_per_vector{static_cast<double>(8 + 8 + 8 + 64) / ALP_VECTOR_SIZE};

double estimate_alp_compression_size(std::vector<alp::metadata> &vector_metadata) {
    double avg_bits_per_value{0};
    for (auto &metadata: vector_metadata) {
        avg_bits_per_value = avg_bits_per_value + metadata.bit_width;
        avg_bits_per_value = avg_bits_per_value + (static_cast<double>(metadata.exceptions_count) * (alp::exception_size + alp::exception_position_size) / ALP_VECTOR_SIZE);
    }

    avg_bits_per_value = avg_bits_per_value / vector_metadata.size();
    avg_bits_per_value = avg_bits_per_value + overhead_per_vector;
    return avg_bits_per_value;
}

/*
 * ALPRD Overhead per vector in a hypothetic file format in which the left parts dictionary is at the start of a rowgroup
 */
double alprd_overhead_per_vector{static_cast<double>(MAX_RD_DICTIONARY_SIZE * 16) / ALP_ROWGROUP_SIZE};

double estimate_alprd_compression_size(std::vector<alp::metadata> &vector_metadata) {
    double avg_bits_per_value{0};
    for (auto &metadata: vector_metadata) {
        avg_bits_per_value = avg_bits_per_value + metadata.right_bit_width + metadata.left_bit_width + static_cast<double>(metadata.exceptions_count * (alp::rd_exception_size + alp::rd_exception_position_size)) / ALP_VECTOR_SIZE;
    }

    avg_bits_per_value = avg_bits_per_value / vector_metadata.size();
    avg_bits_per_value = avg_bits_per_value + alprd_overhead_per_vector;

    return avg_bits_per_value;
}

double get_average_exception_count(std::vector<alp::metadata> &vector_metadata) {
    double avg_exceptions_count{0};
    for (auto &metadata: vector_metadata) {
        avg_exceptions_count = avg_exceptions_count + metadata.exceptions_count;
    }

    avg_exceptions_count = avg_exceptions_count / vector_metadata.size();
    return avg_exceptions_count;
}

class alp_test : public ::testing::Test {
public:
    double *dbl_arr;
    double *exc_arr;
    uint16_t *rd_exc_arr;
    uint16_t *pos_arr;
    uint16_t *exc_c_arr;
    int64_t *ffor_arr;
    int64_t *unffor_arr;
    int64_t *base_arr;
    int64_t *encoded_arr;
    double *dec_dbl_arr;
    double *smp_arr;
    uint64_t *ffor_right_arr;
    uint16_t *ffor_left_arr;
    uint64_t *right_arr;
    uint16_t *left_arr;
    uint64_t *unffor_right_arr;
    uint16_t *unffor_left_arr;
    double *glue_arr;

    alp::state state;

    uint8_t bit_width;

    void SetUp() override {
        dbl_arr = new double[ALP_VECTOR_SIZE];
        exc_arr = new double[ALP_VECTOR_SIZE];
        rd_exc_arr = new uint16_t[ALP_VECTOR_SIZE];
        pos_arr = new uint16_t[ALP_VECTOR_SIZE];
        encoded_arr = new int64_t[ALP_VECTOR_SIZE];
        dec_dbl_arr = new double[ALP_VECTOR_SIZE];
        exc_c_arr = new uint16_t[ALP_VECTOR_SIZE];
        ffor_arr = new int64_t[ALP_VECTOR_SIZE];
        unffor_arr = new int64_t[ALP_VECTOR_SIZE];
        base_arr = new int64_t[ALP_VECTOR_SIZE];
        smp_arr = new double[ALP_VECTOR_SIZE];
        right_arr = new uint64_t[ALP_VECTOR_SIZE];
        left_arr = new uint16_t[ALP_VECTOR_SIZE];
        ffor_right_arr = new uint64_t[ALP_VECTOR_SIZE];
        ffor_left_arr = new uint16_t[ALP_VECTOR_SIZE];
        unffor_right_arr = new uint64_t[ALP_VECTOR_SIZE];
        unffor_left_arr = new uint16_t[ALP_VECTOR_SIZE];
        glue_arr = new double[ALP_VECTOR_SIZE];
    }

    ~alp_test() override {
        delete[] dbl_arr;
        delete[] exc_arr;
        delete[] rd_exc_arr;
        delete[] pos_arr;
        delete[] encoded_arr;
        delete[] dec_dbl_arr;
        delete[] exc_c_arr;
        delete[] ffor_arr;
        delete[] unffor_arr;
        delete[] base_arr;
        delete[] smp_arr;
        delete[] right_arr;
        delete[] left_arr;
        delete[] unffor_right_arr;
        delete[] unffor_left_arr;
    }
};

/*
 * Test used for correctness of bitwidth and exceptions on the first vector of each dataset
 */
TEST_F(alp_test, test_alp_on_one_vector) {
    for (auto &dataset: alp_bench::datasets) {
        std::ifstream ifile(dataset.sample_csv_file_path, std::ios::in);
        std::vector<alp::metadata> compression_metadata;
        alp::state stt;
        size_t tuples_count {ALP_VECTOR_SIZE};
        size_t rowgroup_offset{0};

        if (dataset.name == "bw43") { continue; } // Todo
        if (dataset.name == "bw52") { continue; }
        if (dataset.name == "bw53") { continue; }
        if (dataset.name == "bw54") { continue; }
        if (dataset.name == "bw55") { continue; }
        if (dataset.name == "bw56") { continue; }
        if (dataset.name == "bw57") { continue; }
        if (dataset.name == "bw58") { continue; }
        if (dataset.name == "bw59") { continue; }
        if (dataset.name == "bw60") { continue; }
        if (dataset.name == "bw61") { continue; }
        if (dataset.name == "bw62") { continue; }
        if (dataset.name == "bw63") { continue; }
        if (dataset.name == "bw64") { continue; }

        // check to see that the file was opened correctly:
        if (!ifile.is_open()) {
            std::cerr << "There was a problem opening the input file for dataset : " << dataset.name << "!\n";
            continue; // exit or do additional error checking
        }

        double value_to_encode = 0.0;
        // keep storing values from the text file so long as data exists:
        size_t vector_idx{0};
        while (ifile >> value_to_encode) {
            dbl_arr[vector_idx] = value_to_encode;
            vector_idx += 1;
        }

        // Init
        alp::init(dbl_arr, rowgroup_offset, tuples_count, smp_arr, stt);

        switch (stt.scheme) {
            case alp::ALP_RD: {
                alp::rd_init(dbl_arr, rowgroup_offset, tuples_count, smp_arr, stt);

                alp::rd_encode(dbl_arr, rd_exc_arr, pos_arr, exc_c_arr, right_arr, left_arr, stt);
                ffor::ffor(right_arr, ffor_right_arr, stt.right_bit_width, &stt.right_for_base);
                ffor::ffor(left_arr, ffor_left_arr, stt.left_bit_width, &stt.left_for_base);

                // Decode
                unffor::unffor(ffor_right_arr, unffor_right_arr, stt.right_bit_width, &stt.right_for_base);
                unffor::unffor(ffor_left_arr, unffor_left_arr, stt.left_bit_width, &stt.left_for_base);
                alp::rd_decode(glue_arr, unffor_right_arr, unffor_left_arr, rd_exc_arr, pos_arr, exc_c_arr, stt);

                size_t vector_idx{0};
                for (size_t i = 0; i < ALP_VECTOR_SIZE; ++i) {
                    auto l = dbl_arr[i];
                    auto r = glue_arr[i];
                    if (l != r) { std::cout << vector_idx++ << " | " << i << " r : " << r << " l : " << l << std::endl; }
                    ASSERT_EQ(r, l);
                }

                break;
            }
            case alp::ALP: { // Encode
                alp::encode(dbl_arr, exc_arr, pos_arr, exc_c_arr, encoded_arr, stt);
                alp::analyze_ffor(encoded_arr, bit_width, base_arr);
                ffor::ffor(encoded_arr, ffor_arr, bit_width, base_arr);

                // Decode
                generated::falp::fallback::scalar::falp(reinterpret_cast<uint64_t *>(ffor_arr),
                                                             dec_dbl_arr,
                                                             bit_width,
                                                             reinterpret_cast<uint64_t *>(base_arr),
                                                             stt.fac,
                                                             stt.exp);
                alp::patch_exceptions(dec_dbl_arr, exc_arr, pos_arr, exc_c_arr);

                auto exceptions_count = exc_c_arr[0];
                if (dataset.exceptions_count != exceptions_count) {
                    std::cout << dataset.name << " with exceptions_count : " << dataset.exceptions_count << " should be " << exceptions_count << "\n";
                }

                if (dataset.bit_width != bit_width) {
                    std::cout << dataset.name << " with bit_width " << static_cast<uint64_t>(dataset.bit_width) << " should be "
                              << static_cast<uint64_t>(bit_width) << "\n";
                }

                for (size_t i = 0; i < ALP_VECTOR_SIZE; ++i) {
                    auto l = dbl_arr[i];
                    auto r = dec_dbl_arr[i];
                    if (l != r) { std::cerr << i << ", " << dataset.name << "\n"; }

                    ASSERT_EQ(dbl_arr[i], dec_dbl_arr[i]);
                }

                ASSERT_EQ(dataset.exceptions_count, exceptions_count);
                ASSERT_EQ(dataset.bit_width, bit_width);
            }
        }

        std::cout << "Testing ALP on one vector on dataset: " << dataset.name << " OK" << std::endl;

        ifile.close();
    }
}

/*
 * Test to encode and decode whole datasets using ALP
 * This test will output and write a file with the estimated bits/value after compression with alp
 */
TEST_F(alp_test, test_alp_on_whole_datasets) {
    std::ofstream ofile(alp_bench::PATHS.ALP_RESULT_DIR_PATH + "/alp_estimated_compression.csv", std::ios::out);
    ofile << "dataset,size,rowgroups_count,vectors_count\n";

    for (auto &dataset: alp_bench::datasets) {
        if (dataset.suitable_for_cutting) { continue; }
        if (dataset.name.find("bw") != std::string::npos) { continue; }

        std::vector<alp::metadata> compression_metadata;
        size_t tuples_count;
        double *data_column = (double *) mapper::mmap_file(tuples_count, dataset.binary_file_path);
        double value_to_encode {0.0};
        size_t vector_idx {0};
        size_t rowgroup_counter {0};
        size_t rowgroup_offset {0};
        alp::state stt;
        size_t rowgroups_count = std::ceil(static_cast<double>(tuples_count) / ALP_ROWGROUP_SIZE);
        size_t vectors_count = tuples_count / ALP_VECTOR_SIZE;
        /* Init */
        alp::init(data_column, rowgroup_offset, tuples_count, smp_arr, stt);
        /* Encode - Decode - Validate. */
        for (size_t i = 0; i < tuples_count; i++) {
            value_to_encode = data_column[i];
            dbl_arr[vector_idx] = value_to_encode;
            vector_idx = vector_idx + 1;
            rowgroup_offset = rowgroup_offset + 1;
            rowgroup_counter = rowgroup_counter + 1;

            if (vector_idx != ALP_VECTOR_SIZE) { continue; }
            if (rowgroup_counter == ALP_ROWGROUP_SIZE) {
                rowgroup_counter = 0;
                alp::init(data_column, rowgroup_offset, tuples_count, smp_arr, stt);
            }
            alp::encode(dbl_arr, exc_arr, pos_arr, exc_c_arr, encoded_arr, stt);
            alp::analyze_ffor(encoded_arr, bit_width, base_arr);
            ffor::ffor(encoded_arr, ffor_arr, bit_width, base_arr);

            // Decode
            // todo
            //			generated::falp::fallback::scalar::falp(reinterpret_cast<uint64_t*>(ffor_arr),
            //			                                        dec_dbl_arr,
            //			                                        bit_width,
            //			                                        reinterpret_cast<uint64_t*>(base_arr),
            //			                                        stt.fac,
            //			                                        stt.exp);

            unffor::unffor(ffor_arr, unffor_arr, bit_width, base_arr);
            alp::decode(reinterpret_cast<uint64_t *>(unffor_arr), stt.fac, stt.exp, dec_dbl_arr);
            alp::patch_exceptions(dec_dbl_arr, exc_arr, pos_arr, exc_c_arr);

            for (size_t j = 0; j < ALP_VECTOR_SIZE; j++) {
                auto l = dbl_arr[j];
                auto r = dec_dbl_arr[j];
                if (l != r) { std::cerr << j << ", " << rowgroup_offset << ", " << dataset.name << "\n"; }
                ASSERT_EQ(dbl_arr[j], dec_dbl_arr[j]);
            }
            compression_metadata.push_back({bit_width, exc_c_arr[0]});
            vector_idx = 0;
            bit_width = 0;
        }
        auto estimated_compression_size = estimate_alp_compression_size(compression_metadata);
        ofile << dataset.name << "," << estimated_compression_size << "," << rowgroups_count << "," << vectors_count << std::endl;
        std::cout << "Dataset: " << dataset.name << " | Estimated Compression Size (bits/value): " << estimated_compression_size << " | Rowgroups count: " << rowgroups_count << " | Vectors count: " << vectors_count << std::endl;
    }
}

/*
 * Test to encode and decode whole datasets using ALP RD (aka ALP Cutter)
 * This test will output and write a file with the estimated bits/value after compression with alp
 */
TEST_F(alp_test, test_alprd_on_whole_datasets) {
    std::ofstream ofile(alp_bench::PATHS.ALP_RESULT_DIR_PATH + "/alp_rd_estimated_compression.csv", std::ios::out);
    ofile << "dataset,size,rowgroups_count,vectors_count\n";

    for (auto &dataset: alp_bench::datasets) {
        if (!dataset.suitable_for_cutting) { continue; }
        if (dataset.name.find("bw") != std::string::npos) { continue; }

        std::vector<alp::metadata> compression_metadata;
        size_t tuples_count;
        double *data_column = (double *) mapper::mmap_file(tuples_count, dataset.binary_file_path);
        double value_to_encode = 0.0;
        size_t vector_idx{0};
        size_t rowgroup_counter{0};
        size_t rowgroup_offset{0};
        alp::state stt;
        size_t rowgroups_count{1};
        size_t vectors_count{1};

        /* Init */
        alp::init(data_column, rowgroup_offset, tuples_count, smp_arr, stt);

        ASSERT_EQ(stt.scheme, alp::SCHEME::ALP_RD);

        alp::rd_init(data_column, rowgroup_offset, tuples_count, smp_arr, stt);

        /* Encode - Decode - Validate. */
        for (size_t i = 0; i < tuples_count; i++) {
            value_to_encode = data_column[i];
            dbl_arr[vector_idx] = value_to_encode;
            vector_idx = vector_idx + 1;
            rowgroup_offset = rowgroup_offset + 1;
            rowgroup_counter = rowgroup_counter + 1;

            if (vector_idx != ALP_VECTOR_SIZE) { continue; }

            if (rowgroup_counter == ALP_ROWGROUP_SIZE) {
                rowgroup_counter = 0;
                rowgroups_count = rowgroups_count + 1;
            }

            // Encode
            alp::rd_encode(dbl_arr, rd_exc_arr, pos_arr, exc_c_arr, right_arr, left_arr, stt);
            ffor::ffor(right_arr, ffor_right_arr, stt.right_bit_width, &stt.right_for_base);
            ffor::ffor(left_arr, ffor_left_arr, stt.left_bit_width, &stt.left_for_base);

            // Decode
            unffor::unffor(ffor_right_arr, unffor_right_arr, stt.right_bit_width, &stt.right_for_base);
            unffor::unffor(ffor_left_arr, unffor_left_arr, stt.left_bit_width, &stt.left_for_base);
            alp::rd_decode(glue_arr, unffor_right_arr, unffor_left_arr, rd_exc_arr, pos_arr, exc_c_arr, stt);

            auto *dbl_glue_arr = reinterpret_cast<double *>(glue_arr);
            for (size_t j = 0; j < ALP_VECTOR_SIZE; ++j) {
                auto l = dbl_arr[j];
                auto r = dbl_glue_arr[j];
                if (l != r) { std::cerr << j << ", " << dataset.name << "\n"; }

                ASSERT_EQ(dbl_arr[j], dbl_glue_arr[j]);
            }

            alp::metadata vector_metadata;
            vector_metadata.right_bit_width = stt.right_bit_width;
            vector_metadata.left_bit_width = stt.left_bit_width;
            vector_metadata.exceptions_count = stt.exceptions_count;

            compression_metadata.push_back(vector_metadata);
            vector_idx = 0;
            bit_width = 0;

            vectors_count = vectors_count + 1;
        }

        auto estimated_compression_size = estimate_alprd_compression_size(compression_metadata);
        auto average_exception_count = get_average_exception_count(compression_metadata);

        ofile << dataset.name << "," << estimated_compression_size << "," << rowgroups_count << "," << vectors_count << std::endl;
        std::cout << "Dataset: " << dataset.name << " | Right Bit Width: " << static_cast<uint16_t>(stt.right_bit_width)
                  << " | Left Bit Width (dict encoded): " << static_cast<uint16_t>(stt.left_bit_width) << " | Estimated compression size (bits/value): " << estimated_compression_size << " | Rowgroups Count: " << rowgroups_count
                  << " | Vectors Count: " << vectors_count << " | Avg. Exceptions Count per vector: " << average_exception_count << std::endl;
    }
}