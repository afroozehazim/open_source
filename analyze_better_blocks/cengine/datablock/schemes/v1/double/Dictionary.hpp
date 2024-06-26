#pragma once
#include "datablock/schemes/CScheme.hpp"
#include "datablock/schemes/v1/templated/FixedDictionary.hpp"
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
namespace cengine {
namespace db {
namespace v1 {
namespace d {
// -------------------------------------------------------------------------------------
class Dictionary8 : public DoubleScheme {
public:
   inline double expectedCompressionRatio(DoubleStats &stats, u8 allowed_cascading_level) override
   {
      return FDictExpectedCompressionRatio<u8, DOUBLE>(stats);
   }
   inline u32 compress(const DOUBLE *src, const BITMAP *nullmap, u8 *dest, DoubleStats &stats, u8 allowed_cascading_level) override
   {
      return FDictCompressColumn<u8, DOUBLE>(src, nullmap, dest, stats);
   }
   inline void decompress(DOUBLE *dest, BitmapWrapper *nullmap, const u8 *src, u32 tuple_count, u32 level) override
   {
      return FDictDecompressColumn<u8, DOUBLE>(dest, nullmap, src, tuple_count, level);
   }
   inline virtual DoubleSchemeType schemeType()
   {
      return staticSchemeType();
   }
   inline static DoubleSchemeType staticSchemeType()
   {
      return DoubleSchemeType::DICTIONARY_8;
   }
};
// -------------------------------------------------------------------------------------
class Dictionary16 : public DoubleScheme {
public:
   inline double expectedCompressionRatio(DoubleStats &stats, u8 allowed_cascading_level) override
   {
      return FDictExpectedCompressionRatio<u16, DOUBLE>(stats);
   }
   inline u32 compress(const DOUBLE *src, const BITMAP *nullmap, u8 *dest, DoubleStats &stats, u8) override
   {
      return FDictCompressColumn<u16, DOUBLE>(src, nullmap, dest, stats);
   }
   void decompress(DOUBLE *dest, BitmapWrapper *bitmap, const u8 *src, u32 tuple_count, u32 level) override
   {
      return FDictDecompressColumn<u16, DOUBLE>(dest, bitmap, src, tuple_count, level);
   }
   inline virtual DoubleSchemeType schemeType()
   {
      return staticSchemeType();
   }
   inline static DoubleSchemeType staticSchemeType()
   {
      return DoubleSchemeType::DICTIONARY_16;
   }
};
// -------------------------------------------------------------------------------------
}
}
}
}
// -------------------------------------------------------------------------------------
