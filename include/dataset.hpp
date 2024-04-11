#ifndef DATASET_HPP
#define DATASET_HPP

#include "string"
#include <cstdint>
#include <vector>

namespace alp_bench {
struct Dataset {
	uint64_t    id;
	std::string name;
	std::string sample_csv_file_path {""};
	std::string binary_file_path {""};
	uint8_t factor {0};
	uint16_t exponent {0};
	uint16_t exceptions_count {0};
	uint8_t  bit_width {0};
	bool        suitable_for_cutting {false};
};

struct paths {
	std::string DATASETS_GENERATED_CSV_PATH        = "../../../data/1024_data_generated/";
	std::string DATASETS_SAMPLE_CSV_PATH           = "../../../data/1024_data_samples/";
	std::string DATASETS_BINARY_PATH               = "../../../data/raw_binaries/";
	std::string ALP_RESULT_DIR_PATH                = "../../../alp_pub";

	explicit paths() {
		if (auto v = std::getenv("DATASETS_1024_SAMPLES_PATH")) { DATASETS_SAMPLE_CSV_PATH = v; }
		if (auto v = std::getenv("DATASETS_COMPLETE_PATH")) { DATASETS_BINARY_PATH = v; }
		if (auto v = std::getenv("ALP_RESULT_DIR_PATH")) { ALP_RESULT_DIR_PATH = v; }
	}
};

inline paths PATHS;

} // namespace alp_bench

#endif