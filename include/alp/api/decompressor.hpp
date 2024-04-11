#include "alp/alp.hpp"
#include "alp/api/utils.hpp"
#include "alp/api/storer.hpp"

namespace alp {

/*
 * API Decompressor
 */
struct AlpDecompressor {

    alp::state stt;
    alp::storer::MemReader reader;

    size_t out_offset = 0;

    double exceptions[ALP_VECTOR_SIZE];
    int64_t encoded_integers[ALP_VECTOR_SIZE];
    int64_t alp_encoded_array[ALP_VECTOR_SIZE];
    uint16_t exceptions_rd[ALP_VECTOR_SIZE];
    uint16_t exceptions_position[ALP_VECTOR_SIZE];

    // 'right' & 'left' refer to the respective parts of the floating numbers after splitting
    uint64_t alp_bp_size;
    uint64_t left_bp_size; 
    uint64_t right_bp_size; 
    uint64_t right_parts[ALP_VECTOR_SIZE];
    uint64_t right_parts_encoded[ALP_VECTOR_SIZE];
	uint16_t left_parts_encoded[ALP_VECTOR_SIZE];
    uint16_t left_parts[ALP_VECTOR_SIZE]; 

    AlpDecompressor(){

    };

    void load_rd_metadata(){
        reader.read(&stt.right_bit_width, sizeof(stt.right_bit_width));
        reader.read(&stt.left_bit_width, sizeof(stt.left_bit_width));
        left_bp_size = alp::AlpApiUtils::get_size_after_bitpacking(stt.left_bit_width);
        right_bp_size = alp::AlpApiUtils::get_size_after_bitpacking(stt.right_bit_width);

        reader.read(&stt.actual_dictionary_size, sizeof(stt.actual_dictionary_size));
        uint8_t actual_dictionary_size_bytes = stt.actual_dictionary_size * dictionary_element_size_bytes;

        reader.read(stt.left_parts_dict, actual_dictionary_size_bytes);
    }

    void load_alprd_vector(){
        reader.read(&stt.exceptions_count, sizeof(stt.exceptions_count));
        reader.read(left_parts_encoded, left_bp_size);
        reader.read(right_parts_encoded, right_bp_size);
        if (stt.exceptions_count){
            reader.read(exceptions_rd, alp::rd_exception_size_bytes * stt.exceptions_count);
			reader.read(exceptions_position, alp::rd_exception_position_size_bytes * stt.exceptions_count);
        }
    }

    void load_alp_vector(){
        reader.read(&stt.exp, sizeof(stt.exp));
        reader.read(&stt.fac, sizeof(stt.fac));
        reader.read(&stt.exceptions_count, sizeof(stt.exceptions_count));
        reader.read(&stt.for_base, sizeof(stt.for_base));
        reader.read(&stt.bit_width, sizeof(stt.bit_width));

        if (stt.bit_width > 0){
            alp_bp_size = alp::AlpApiUtils::get_size_after_bitpacking(stt.bit_width);
            reader.read(alp_encoded_array, alp_bp_size);
        }

        if (stt.exceptions_count > 0){
            reader.read(exceptions, alp::exception_size_bytes * stt.exceptions_count);
			reader.read(exceptions_position, alp::exception_position_size_bytes * stt.exceptions_count);
        }
    }

    void decompress_vector(double* out){
        if (stt.scheme == alp::ALP_RD){
            unffor::unffor(right_parts_encoded, right_parts, stt.right_bit_width, &stt.right_for_base);
            unffor::unffor(left_parts_encoded, left_parts, stt.left_bit_width, &stt.left_for_base);
            alp::rd_decode((out + out_offset), right_parts, left_parts, exceptions_rd, exceptions_position, &stt.exceptions_count, stt);
        } else {
            unffor::unffor(alp_encoded_array, encoded_integers, stt.bit_width, &stt.for_base);
            alp::decode(reinterpret_cast<uint64_t *>(encoded_integers), stt.fac, stt.exp, (out + out_offset));
            alp::patch_exceptions((out + out_offset), exceptions, exceptions_position, &stt.exceptions_count);
        }
    }

    void load_vector(){
        if (stt.scheme == alp::ALP_RD){
            load_alprd_vector();
        } else {
            load_alp_vector();
        }
    }

    alp::SCHEME load_rowgroup_metadata(){
        uint8_t scheme_id;
        reader.read(&scheme_id, sizeof(scheme_id));

        alp::SCHEME used_scheme = alp::SCHEME(scheme_id);
        if (used_scheme == alp::SCHEME::ALP_RD){
            load_rd_metadata();
        }

        return used_scheme;
    }

    void decompress(uint8_t* in, size_t values_count, double* out){
        reader = alp::storer::MemReader(in);
        size_t rouwgroup_count = alp::AlpApiUtils::get_rowgroup_count(values_count);
        size_t left_to_decompress = values_count;
        for (size_t current_rowgroup = 0; current_rowgroup < rouwgroup_count; current_rowgroup++){
            /*
             * Rowgroup level
             */
            stt.scheme = load_rowgroup_metadata();

            size_t values_left_in_rowgroup = std::min(ALP_ROWGROUP_SIZE, left_to_decompress);
            size_t vectors_in_rowgroup = alp::AlpApiUtils::get_vector_count(values_left_in_rowgroup);

            for (size_t vector_idx = 0; vector_idx < vectors_in_rowgroup; vector_idx++){
                /*
                * Vector level
                */
                size_t next_vector_count = std::min(ALP_VECTOR_SIZE, left_to_decompress);
                load_vector();
                decompress_vector(out);
                out_offset += next_vector_count;
                left_to_decompress -= next_vector_count;
            }
        }
        if (left_to_decompress){
            load_vector();
            decompress_vector(out);
        }
    };

};

}