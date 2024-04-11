#include "datasets.hpp"
#include "mapper.hpp"
#include "gtest/gtest.h"
#include "zstd/zstd.h"
#include "common.h"

class zstd_test : public ::testing::Test {
public:
    double *dbl_arr;
    void *enc_dbl_arr;
    void *dec_dbl_arr;
    size_t ENC_SIZE_UPPER_BOUND = 1024 * 8;
    size_t INPUT_SIZE = 1024 * 8;
    size_t VEC_C = 1024;
    size_t DEC_SIZE = INPUT_SIZE;

    void SetUp() override {
        dbl_arr = new double[VEC_C];
        enc_dbl_arr = malloc(INPUT_SIZE);
        dec_dbl_arr = malloc(INPUT_SIZE);
    }

    ~zstd_test() override {
        delete[] dbl_arr;
        free(enc_dbl_arr);
        free(dec_dbl_arr);
    }
};

TEST_F(zstd_test, test_zstd_on_whole_datasets) {
    for (auto &dataset: alp_bench::datasets) {
        if (dataset.name.find("bw") != std::string::npos) { continue; }

        size_t tup_c;
        double *col = (double *) mapper::mmap_file(tup_c, dataset.binary_file_path);
        double num = 0.0;
        size_t c{0};

        std::cout << dataset.binary_file_path << "\n";

        /* Encode - Decode - Validate. */
        for (size_t i = 0; i < tup_c; i++) {
            num = col[i];
            dbl_arr[c] = num;
            c = c + 1;

            if (c != VEC_C) { continue; }

            // Encode
            size_t const ENC_SIZE = ZSTD_compress(enc_dbl_arr, ENC_SIZE_UPPER_BOUND, dbl_arr, INPUT_SIZE, 3); // Level 3
            printf("%6u -> %7u\n", (unsigned)INPUT_SIZE, (unsigned)ENC_SIZE);
            // Decode
            ZSTD_decompress(dec_dbl_arr, DEC_SIZE, enc_dbl_arr, ENC_SIZE);

            double *dec_dbl_arr_tmp = (double *) dec_dbl_arr;
            for (size_t j = 0; j < VEC_C; ++j) {
                auto l = dbl_arr[j];
                auto r = dec_dbl_arr_tmp[j];
                if (l != r) { std::cerr << j << ", " << dataset.name << "\n"; }
                ASSERT_EQ(dbl_arr[j], dec_dbl_arr_tmp[j]);
            }
            c = 0;
        }
    }
}
