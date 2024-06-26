#pragma once
#include "Units.hpp"
#include "storage/Chunk.hpp"
#include "storage/Relation.hpp"
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
namespace cengine {
// -------------------------------------------------------------------------------------
struct OutputBlockStats {
   vector<SIZE> data_sizes;
   vector<SIZE> nullmap_sizes;
   vector<u8> used_compression_schemes;
   // -------------------------------------------------------------------------------------
   // Aux
   SIZE total_data_size;
   SIZE total_nullmap_size;
   SIZE total_db_size;
   double compression_ratio; //before /old data size
};
// -------------------------------------------------------------------------------------
class CMachine {
protected:
   const Relation &relation;
public:
   CMachine(const Relation &relation)
     : relation(relation) {}

   virtual OutputBlockStats compress(const Chunk &input_chunk, BytesArray &output_block) = 0;
   virtual cengine::Chunk decompress(const BytesArray &input_block) = 0;
};
}
// -------------------------------------------------------------------------------------