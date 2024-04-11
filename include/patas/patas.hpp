#pragma once

#include "chimp/byte_reader.hpp"
#include "chimp/byte_writer.hpp"
#include "chimp/chimp_utils.hpp"
#include "chimp/packed_data.hpp"
#include "chimp/ring_buffer.hpp"
#include <iostream>
#include <unordered_map>

namespace alp_bench {

namespace patas {

struct PatasUnpackedValueStats {
		uint8_t significant_bytes;
		uint8_t trailing_zeros;
		uint8_t index_diff;
	};

template <class EXACT_TYPE, bool EMPTY>
class PatasCompressionState {
public:
	PatasCompressionState() : index(0), first(true) {
	}

public:
	void Reset() {
		index = 0;
		first = true;
		ring_buffer.Reset();
		packed_data_buffer.Reset();
	}
	void SetOutputBuffer(uint8_t *output) {
		byte_writer.SetStream(output);
		Reset();
	}
	idx_t Index() const {
		return index;
	}

public:
	void UpdateMetadata(uint8_t trailing_zero, uint8_t byte_count, uint8_t index_diff) {
		if (!EMPTY) {
			packed_data_buffer.Insert(PackedDataUtils<EXACT_TYPE>::Pack(index_diff, byte_count, trailing_zero));
		}
		index++;
	}

public:
	ByteWriter<EMPTY> byte_writer;
	PackedDataBuffer<EMPTY> packed_data_buffer;
	std::unordered_map<uint8_t, int> trailing_zeros_counter;
	idx_t index;
	RingBuffer<EXACT_TYPE> ring_buffer;
	bool first;
};

template <class EXACT_TYPE, bool EMPTY>
struct PatasCompression {
	using State = PatasCompressionState<EXACT_TYPE, EMPTY>;
	static constexpr uint8_t EXACT_TYPE_BITSIZE = sizeof(EXACT_TYPE) * 8;

	static void Store(EXACT_TYPE value, State &state) {
		if (state.first) {
			StoreFirst(value, state);
		} else {
			StoreCompressed(value, state);
		}
	}

	static void StoreFirst(EXACT_TYPE value, State &state) {
		// write first value, uncompressed
		state.ring_buffer.template Insert<true>(value);
		state.byte_writer.template WriteValue<EXACT_TYPE, EXACT_TYPE_BITSIZE>(value);
		state.first = false;
		state.UpdateMetadata(0, sizeof(EXACT_TYPE), 0);
	}

	static void StoreCompressed(EXACT_TYPE value, State &state) {
		auto key = state.ring_buffer.Key(value);
		uint64_t reference_index = state.ring_buffer.IndexOf(key);

		// Find the reference value to use when compressing the current value
		const bool exceeds_highest_index = reference_index > state.ring_buffer.Size();
		const bool difference_too_big =
		    ((state.ring_buffer.Size() + 1) - reference_index) >= ChimpConstants::BUFFER_SIZE;
		if (exceeds_highest_index || difference_too_big) {
			// Reference index is not in range, use the directly previous value
			reference_index = state.ring_buffer.Size();
		}
		const auto reference_value = state.ring_buffer.Value(reference_index % ChimpConstants::BUFFER_SIZE);

		// XOR with previous value
		EXACT_TYPE xor_result = value ^ reference_value;

		// Figure out the trailing zeros (max 6 bits)
		const uint8_t trailing_zero = CountZeros<EXACT_TYPE>::Trailing(xor_result);
		// if (state.trailing_zeros_counter.find(trailing_zero) != state.trailing_zeros_counter.end()){
		// 	//std::cout << "Hwllo";
		// 	state.trailing_zeros_counter[trailing_zero] += 1;
		// } else {
		// 	state.trailing_zeros_counter[trailing_zero] = 1;
		// }


		const uint8_t leading_zero = CountZeros<EXACT_TYPE>::Leading(xor_result);

		const bool is_equal = xor_result == 0;

		// Figure out the significant bytes (max 3 bits)
		const uint8_t significant_bits = !is_equal * (EXACT_TYPE_BITSIZE - trailing_zero - leading_zero);
		const uint8_t significant_bytes = (significant_bits >> 3) + ((significant_bits & 7) != 0);

		// Avoid an invalid shift error when xor_result is 0
		state.byte_writer.template WriteValue<EXACT_TYPE>(xor_result >> (trailing_zero - is_equal), significant_bits);

		state.ring_buffer.Insert(value);

		const uint8_t index_difference = state.ring_buffer.Size() - reference_index;
		state.UpdateMetadata(trailing_zero - is_equal, significant_bytes, index_difference);
	}
};

// Decompression

template <class EXACT_TYPE>
struct PatasDecompression {
	static inline EXACT_TYPE DecompressValue(ByteReader &byte_reader, uint8_t byte_count, uint8_t trailing_zero,
	                                         EXACT_TYPE previous) {
		return (byte_reader.ReadValue<EXACT_TYPE>(byte_count, trailing_zero) << trailing_zero) ^ previous;
	}
};

} // namespace patas

} // namespace lwcbench
