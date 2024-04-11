#ifndef ALP_DATASETS_HPP
#define ALP_DATASETS_HPP

#include "dataset.hpp"
#include "string"
#include <cstdint>
#include <vector>

namespace alp_bench {

inline std::vector<Dataset> datasets = {
    {1,
     "arade4",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "arade4.csv", 
     PATHS.DATASETS_BINARY_PATH + "arade4.bin", 14, 10, 8, 24
    },

    {2,
     "basel_temp_f",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "basel_temp_f.csv",
     PATHS.DATASETS_BINARY_PATH + "basel_temp_f.bin", 14, 7, 47, 28
     },

    {3,
     "basel_wind_f",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "basel_wind_f.csv",
     PATHS.DATASETS_BINARY_PATH + "basel_wind_f.bin", 14, 7, 9, 29
    }, 

    {4,
     "bird_migration_f",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "bird_migration_f.csv",
     PATHS.DATASETS_BINARY_PATH + "bird_migration_f.bin", 14, 9, 2, 17  
    }, 

    {5,
     "bitcoin_f",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "bitcoin_f.csv",
     PATHS.DATASETS_BINARY_PATH + "bitcoin_f.bin", 14, 10, 10, 25 
},  

    {6,
     "bitcoin_transactions_f",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "bitcoin_transactions_f.csv",
     PATHS.DATASETS_BINARY_PATH + "bitcoin_transactions_f.bin", 14, 10, 11, 30               
},

    {7,
     "city_temperature_f",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "city_temperature_f.csv",
     PATHS.DATASETS_BINARY_PATH + "city_temperature_f.bin", 14, 13, 0, 11 
     }, 

    {8,
     "cms1",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "cms1.csv",
     PATHS.DATASETS_BINARY_PATH + "cms1.bin", 14, 5, 10, 41               
    },

    {9,
     "cms9",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "cms9.csv",
     PATHS.DATASETS_BINARY_PATH + "cms9.bin", 16, 16, 2, 10               
    },

    {10,
     "cms25",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "cms25.csv",
     PATHS.DATASETS_BINARY_PATH + "cms25.bin", 14, 4, 6, 42
    },

    {11,
     "food_prices",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "food_prices.csv",
     PATHS.DATASETS_BINARY_PATH + "food_prices.bin", 16, 12, 46, 20
     },

    {12,
     "gov10",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "gov10.csv",
     PATHS.DATASETS_BINARY_PATH + "gov10.bin", 3, 1, 72, 27
     },

    {13,
     "gov26",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "gov26.csv",
     PATHS.DATASETS_BINARY_PATH + "gov26.bin", 18, 18, 0, 0
     },

    {14,
     "gov30",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "gov30.csv",
     PATHS.DATASETS_BINARY_PATH + "gov30.bin", 18, 18, 4, 0
     },

    {15,
     "gov31",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "gov31.csv",
     PATHS.DATASETS_BINARY_PATH + "gov31.bin", 18, 18, 1, 0 
     },

    {16,
     "gov40",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "gov40.csv",
     PATHS.DATASETS_BINARY_PATH + "gov40.bin", 18, 18, 3, 0
     },

    {17,
     "medicare1",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "medicare1.csv", 
     PATHS.DATASETS_BINARY_PATH + "medicare1.bin", 14, 5, 37, 38
     },

    {18,
     "medicare9",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "medicare9.csv", 
     PATHS.DATASETS_BINARY_PATH + "medicare9.bin", 16, 16, 3, 10 
    },

    // {19,
    //  "neon_air_pressure",
    //  PATHS.DATASETS_SAMPLE_CSV_PATH + "neon_air_pressure.csv", 
    //  PATHS.DATASETS_BINARY_PATH + "neon_air_pressure.bin", 14, 9, 3, 16 
     
    // },

    // {20,
    //  "neon_bio_temp_c",
    //  PATHS.DATASETS_SAMPLE_CSV_PATH + "neon_bio_temp_c.csv", 
    //  PATHS.DATASETS_BINARY_PATH + "neon_bio_temp_c.bin", 14, 2, 0, 10 
    // },

    {21,
     "neon_dew_point_temp",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "neon_dew_point_temp.csv", 
     PATHS.DATASETS_BINARY_PATH + "neon_dew_point_temp.bin", 14, 11, 6, 13 
    },

    {22,
     "neon_pm10_dust",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "neon_pm10_dust.csv",
     PATHS.DATASETS_BINARY_PATH + "neon_pm10_dust.bin", 14, 11, 0, 8              
     
    },

    // {23,
    //  "neon_wind_dir",
    //  PATHS.DATASETS_SAMPLE_CSV_PATH + "neon_wind_dir.csv", 
    //  PATHS.DATASETS_BINARY_PATH + "neon_wind_dir.bin", 14, 12, 0, 16 
    // },

    {24,
     "nyc29",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "nyc29.csv",
     PATHS.DATASETS_BINARY_PATH + "nyc29.bin", 14, 1, 5, 42              
     },

    {25,
     "poi_lat",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "poi_lat.csv", 
     PATHS.DATASETS_BINARY_PATH + "poi_lat.bin", 16, 0, 157, 55,  
     true},

    {26,
     "poi_lon",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "poi_lon.csv",
     PATHS.DATASETS_BINARY_PATH + "poi_lon.bin", 16, 0, 199, 56,              
     true},

    {27,
     "ssd_hdd_benchmarks_f",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "ssd_hdd_benchmarks_f.csv",
     PATHS.DATASETS_BINARY_PATH + "ssd_hdd_benchmarks_f.bin", 14, 13, 0, 17                 
    },

    {28,
     "stocks_de",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "stocks_de.csv", 
     PATHS.DATASETS_BINARY_PATH + "stocks_de.bin", 14, 11, 5, 10 
     
    },

    {29,
     "stocks_uk",
     PATHS.DATASETS_SAMPLE_CSV_PATH + "stocks_uk.csv", 
     PATHS.DATASETS_BINARY_PATH + "stocks_uk.bin", 14, 13, 0, 9 
     },

    // {30,
    //  "stocks_usa_c",
    //  PATHS.DATASETS_SAMPLE_CSV_PATH + "stocks_usa_c.csv", 
    //  PATHS.DATASETS_BINARY_PATH + "stocks_usa_c.bin", 14, 12, 0, 7
    // },
    {
        0,
        "bw0",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw0.csv", 
        "", 0, 0, 0, 0
    },

    {
        1,
        "bw1",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw1.csv", 
        "", 0, 0, 0, 1
    },

    {
        2,
        "bw2",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw2.csv", 
        "", 0, 0, 0, 2
    },

    {
        3,
        "bw3",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw3.csv", 
        "", 0, 0, 0, 3

    },

    {
        4,
        "bw4",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw4.csv", 
        "", 0, 0, 0, 4
    },

    {
        5,
        "bw5",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw5.csv", 
        "", 0, 0, 0, 5
    },
    {
        6,
        "bw6",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw6.csv", 
        "", 0, 0, 0, 6
    },

    {
        7,
        "bw7",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw7.csv", 
        "", 0, 0, 0, 7
    },

    {
        8,
        "bw8",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw8.csv", 
        "", 0, 0, 0, 8
    },

    {
        9,
        "bw9",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw9.csv", 
        "", 0, 0, 0, 9
    },

    {
        10,
        "bw10",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw10.csv", 
        "", 0, 0, 0, 10
    },

    {
        11,
        "bw11",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw11.csv", 
        "", 0, 0, 0, 11
    },

    {
        12,
        "bw12",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw12.csv", 
        "", 0, 0, 0, 12
    },

    {
        13,
        "bw13",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw13.csv", 
        "", 0, 0, 0, 13
    },

    {
        14,
        "bw14",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw14.csv", 
        "", 0, 0, 0, 14
    },

    {
        15,
        "bw15",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw15.csv", 
        "", 0, 0, 0, 15
    },

    {
        16,
        "bw16",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw16.csv", 
        "", 0, 0, 0, 16
    },

    {
        17,
        "bw17",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw17.csv", 
        "", 0, 0, 0, 17
    },

    {
        18,
        "bw18",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw18.csv", 
        "", 0, 0, 0, 18
    },

    {
        19,
        "bw19",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw19.csv", 
        "", 0, 0, 0, 19
    },

    {
        20,
        "bw20",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw20.csv", 
        "", 0, 0, 0, 20
    },

    {
        21,
        "bw21",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw21.csv", 
        "", 0, 0, 0, 21
    },

    {
        22,
        "bw22",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw22.csv", 
        "", 0, 0, 0, 22
    },

    {
        23,
        "bw23",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw23.csv", 
        "", 0, 0, 0, 23
    },

    {
        24,
        "bw24",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw24.csv", 
        "", 0, 0, 0, 24
    },

    {
        25,
        "bw25",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw25.csv", 
        "", 0, 0, 0, 25
    },

    {
        26,
        "bw26",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw26.csv", 
        "", 0, 0, 0, 26
    },

    {
        27,
        "bw27",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw27.csv", 
        "", 0, 0, 0, 27
    },

    {
        28,
        "bw28",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw28.csv", 
        "", 0, 0, 0, 28
    },

    {
        29,
        "bw29",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw29.csv", 
        "", 0, 0, 0, 29
     },

    {
        30,
        "bw30",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw30.csv", 
        "", 0, 0, 0, 30
     },

    {
        31,
        "bw31",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw31.csv", 
        "", 0, 0, 0, 31
     },

    {
        32,
        "bw32",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw32.csv", 
        "", 0, 0, 0, 32
     },

    {
        33,
        "bw33",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw33.csv", 
        "", 0, 0, 0, 33
     },

    {
        34,
        "bw34",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw34.csv", 
        "", 0, 0, 0, 34
     },

    {
        35,
        "bw35",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw35.csv", 
        "", 0, 0, 0, 35
     },

    {
        36,
        "bw36",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw36.csv", 
        "", 0, 0, 0, 36
     },

    {
        37,
        "bw37",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw37.csv", 
        "", 0, 0, 0, 37
     },

    {
        38,
        "bw38",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw38.csv", 
        "", 0, 0, 0, 38
     },

    {
        39,
        "bw39",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw39.csv", 
        "", 0, 0, 0, 39
     },

    {
        40,
        "bw40",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw40.csv", 
        "", 0, 0, 0, 40
     },

    {
        41,
        "bw41",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw41.csv", 
        "", 0, 0, 0, 41
     },

    {
        42,
        "bw42",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw42.csv", 
        "", 0, 0, 0, 42
     },

    {
        43,
        "bw43",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw43.csv", 
        "", 0, 0, 0, 43
     },

    {
        44,
        "bw44",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw44.csv", 
        "", 0, 0, 0, 44
     },

    {
        45,
        "bw45",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw45.csv", 
        "", 0, 0, 0, 45
     },

    {
        46,
        "bw46",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw46.csv", 
        "", 0, 0, 0, 46
     },

    {
        47,
        "bw47",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw47.csv", 
        "", 0, 0, 0, 47
     },

    {
        48,
        "bw48",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw48.csv", 
        "", 0, 0, 0, 48
     },

    {
        49,
        "bw49",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw49.csv", 
        "", 0, 0, 0, 49
     },

    {
        50,
        "bw50",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw50.csv", 
        "", 0, 0, 0, 50
     },

    {
        51,
        "bw51",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw51.csv", 
        "", 0, 0, 0, 51
     },

    {
        52,
        "bw52",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw52.csv", 
        "", 0, 0, 0, 52
     },

    {
        53,
        "bw53",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw53.csv", 
        "", 0, 0, 0, 53
     },

    {
        54,
        "bw54",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw54.csv", 
        "", 0, 0, 0, 54
     },

    {
        55,
        "bw55",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw55.csv", 
        "", 0, 0, 0, 55
     },

    {
        56,
        "bw56",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw56.csv", 
        "", 0, 0, 0, 56
     },

    {
        57,
        "bw57",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw57.csv", 
        "", 0, 0, 0, 57
     },

    {
        58,
        "bw58",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw58.csv", 
        "", 0, 0, 0, 58
     },

    {
        59,
        "bw59",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw59.csv", 
        "", 0, 0, 0, 59
     },

    {
        60,
        "bw60",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw60.csv", 
        "", 0, 0, 0, 60
     },

    {
        61,
        "bw61",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw61.csv", 
        "", 0, 0, 0, 61
     },

    {
        62,
        "bw62",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw62.csv", 
        "", 0, 0, 0, 62
     },

    {
        63,
        "bw63",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw63.csv", 
        "", 0, 0, 0, 63
     },

    {
        64,
        "bw64",
        PATHS.DATASETS_GENERATED_CSV_PATH + "generated_doubles_bw64.csv", 
        "", 0, 0, 0, 64
     }

};
} // namespace alp_bench
#endif