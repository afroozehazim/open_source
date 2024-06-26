#pragma once
#include "datablock/schemes/CScheme.hpp"
#include "datablock/schemes/v1/templated/FixedDictionary.hpp"
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
namespace cengine {
namespace db {
namespace v1 {
namespace integer {
// -------------------------------------------------------------------------------------
class Dictionary16 : public IntegerScheme {
public:
   double expectedCompressionRatio(SInteger32Stats &stats, u8 allowed_cascading_level) override
   {
      return FDictExpectedCompressionRatio<u16, INTEGER>(stats);
   }
   // -------------------------------------------------------------------------------------
   u32 compress(const INTEGER *src, const BITMAP *nullmap, u8 *dest, SInteger32Stats &stats, u8) override
   {
      return FDictCompressColumn<u16, INTEGER>(src, nullmap, dest, stats);
   }
   void decompress(INTEGER *dest, BitmapWrapper *nullmap, const u8 *src, u32 tuple_count, u32 level) override
   {
      return FDictDecompressColumn<u16>(dest, nullmap, src, tuple_count, level);
   }
   // -------------------------------------------------------------------------------------
   inline virtual IntegerSchemeType schemeType()
   {
      return staticSchemeType();
   }
   inline static IntegerSchemeType staticSchemeType()
   {
      return IntegerSchemeType::DICTIONARY_16;
   }
   // -------------------------------------------------------------------------------------
   INTEGER lookup(u32) { UNREACHABLE(); }
   void scan(Predicate, BITMAP *, const u8 *, u32) { UNREACHABLE(); }
};
// -------------------------------------------------------------------------------------
class Dictionary8 : public IntegerScheme {
public:
   double expectedCompressionRatio(SInteger32Stats &stats, u8 allowed_cascading_level) override
   {
      return FDictExpectedCompressionRatio<u8, UINTEGER>(stats);
   }
   // -------------------------------------------------------------------------------------
   u32 compress(const INTEGER *src, const BITMAP *nullmap, u8 *dest, SInteger32Stats &stats, u8 allowed_cascading_level) override
   {
      return FDictCompressColumn<u8, INTEGER>(src, nullmap, dest, stats);
   }
   void decompress(INTEGER *dest, BitmapWrapper *nullmap, const u8 *src, u32 tuple_count, u32 level) override
   {
      return FDictDecompressColumn<u8, INTEGER>(dest, nullmap, src, tuple_count, level);
   }
   // -------------------------------------------------------------------------------------
   inline virtual IntegerSchemeType schemeType()
   {
      return staticSchemeType();
   }
   inline static IntegerSchemeType staticSchemeType()
   {
      return IntegerSchemeType::DICTIONARY_8;
   }
   // -------------------------------------------------------------------------------------
   INTEGER lookup(u32) { UNREACHABLE(); }
   void scan(Predicate, BITMAP *, const u8 *, u32) { UNREACHABLE(); }
};
// -------------------------------------------------------------------------------------
}
}
}
}