#ifndef ALP_DATASETS32_HPP
#define ALP_DATASETS32_HPP

#include "dataset.hpp"
#include "string"
#include <cstdint>
#include <vector>

namespace alp_bench {

inline std::vector<Dataset> sp_datasets = {

    {1,
     "sp_dino_vitb16",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "sp_dino_vitb16.csv",
     PATHS.DATASETS_BINARY_PATH + "sp_dino_vitb16.bin", 0, 0, 0, 0,            
     true
    },

    {2,
     "sp_word2vec_tweets",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "sp_word2vec_tweets.csv",
     PATHS.DATASETS_BINARY_PATH + "sp_word2vec_tweets.bin", 0, 0, 0, 0,
     true               
    },


    {3,
     "sp_grammarly_coedit_lg",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "sp_grammarly_coedit_lg.csv",
     PATHS.DATASETS_BINARY_PATH + "sp_grammarly_coedit_lg.bin", 0, 0, 0, 0,             
     true
    },

    {4,
     "sp_gpt2",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "sp_gpt2.csv",
     PATHS.DATASETS_BINARY_PATH + "sp_gpt2.bin", 0, 0, 0, 0,             
     true},


    {5,
     "poi_lat",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "poi_lat.csv", 
     PATHS.DATASETS_BINARY_PATH + "poi_lat.bin", 0, 0, 0, 0,
     true},

    {6,
     "poi_lon",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "poi_lon.csv",
     PATHS.DATASETS_BINARY_PATH + "poi_lon.bin", 0, 0, 0, 0,              
     true}

};
} // namespace alp_bench
#endif