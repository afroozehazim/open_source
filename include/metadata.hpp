#ifndef ALP_MTD_HPP
#define ALP_MTD_HPP

#include <cstdint>
#include <iostream>
namespace alp {
struct metadata {
	uint8_t                                    bit_width {0};
	uint16_t                                   exceptions_count {0};
	uint64_t                                   unq_c {0};
	uint16_t                                   freq {0};
	double                                     size {0};
	uint64_t                                   right_bit_width {0};
	uint64_t                                   left_bit_width {0};
	std::vector<std::pair<uint16_t, uint64_t>> repetition_vec;
};
} // namespace alp

#endif