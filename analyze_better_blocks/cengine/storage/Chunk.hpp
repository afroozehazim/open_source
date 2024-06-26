#pragma once
#include "Units.hpp"
#include "Column.hpp"
#include "Relation.hpp"
#include "StringArrayViewer.hpp"
#include "StringPointerArrayViewer.hpp"
#include "datablock/schemes/v2/bitmap/RoaringBitmap.hpp"
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
#include <memory>
// -------------------------------------------------------------------------------------
namespace cengine {
class Relation;
// -------------------------------------------------------------------------------------
class Chunk {
public:
   const Relation &relation;
   unique_ptr<unique_ptr<u8[]>[]> columns;
   unique_ptr<unique_ptr<BITMAP[]>[]> bitmaps;
   unique_ptr<bool[]> column_requires_copy;
   unique_ptr<SIZE[]> sizes;
   const u64 tuple_count;

   Chunk(unique_ptr<unique_ptr<u8[]>[]> &&columns, unique_ptr<unique_ptr<BITMAP[]>[]> &&bitmaps,
         unique_ptr<bool[]> &&column_requires_copy, u64 tuple_count, const Relation &relation,
         unique_ptr<SIZE[]> &&sizes);

   Chunk(unique_ptr<unique_ptr<u8[]>[]> &&columns, unique_ptr<unique_ptr<BITMAP[]>[]> &&bitmaps,
         u64 tuple_count, const Relation &relation, unique_ptr<SIZE[]> &&sizes);

   template<typename T>
   inline T &get(u32 c, u32 i) const
   {
      return reinterpret_cast<T *>(columns[c].get())[i];
   }

   inline BITMAP has(u32 c, u32 i) const
   {
      return bitmaps.get()[c].get()[i];
   }

   inline const str operator()(u32 c, u32 i) const
   {
      if (column_requires_copy[c]) {
          StringPointerArrayViewer viewer(columns[c].get());
          return viewer(i);
      } else {
          return StringArrayViewer::get(columns[c].get(), i);
      }
   }

   template<typename T>
   inline const T *array(u32 c) const
   {
      return reinterpret_cast<const T *>(columns[c].get());
   }

   inline const BITMAP *nullmap(u32 c) const
   {
      return bitmaps.get()[c].get();
   }

   inline SIZE size(u32 c) const { return sizes[c]; }

   bool operator==(const Chunk &other) const;

   void reset();
};

class InputChunk {
    /*
     * Chunk of a single column before compression
     */
public:
    unique_ptr<u8[]> data;
    unique_ptr<BITMAP[]> nullmap;
    ColumnType type;
    SIZE size;
    const u64 tuple_count;

    InputChunk(unique_ptr<u8[]> &&data, unique_ptr<BITMAP[]> &&bitmap, ColumnType type, u64 tuple_count, SIZE size);

    bool compareContents(u8 *their_data, BitmapWrapper *bitmapWrapper, u64 their_tuple_count, bool requires_copy) const;
};

struct ColumnPartMetadata {
    u32 num_chunks;
    u32 offsets[];
};

class ColumnPart {
    /*
     * Multiple compressed chunks of a single column, so they have at minimum the target file size
     */
public:
    SIZE total_size = 0;
    vector<vector<u8>> chunks;

    [[nodiscard]] bool canAdd(SIZE chunk_size);
    void addCompressedChunk(vector<u8> &&chunk);
    u32 writeToDisk(const std::string& outputfile);
    void reset();
};
// -------------------------------------------------------------------------------------
}
// -------------------------------------------------------------------------------------
