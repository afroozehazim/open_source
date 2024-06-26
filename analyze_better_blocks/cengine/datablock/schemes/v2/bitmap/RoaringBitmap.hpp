#pragma once
#include "Units.hpp"
#include "roaring/roaring.hh"
#include <boost/dynamic_bitset.hpp>
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
namespace cengine::db::v2::bitmap {
class BitmapWrapper {
private:
    u32 m_tuple_count;
    u32 m_cardinality;
    Roaring m_roaring;
    boost::dynamic_bitset<> *m_bitset = nullptr;
    bool m_bitset_initialized = false;
    BitmapType m_type;
public:
    BitmapWrapper(const u8 *src, BitmapType type, u32 tuple_count, boost::dynamic_bitset<> *bitset = nullptr);
    virtual ~BitmapWrapper();
    void writeBITMAP(BITMAP *dest);
    boost::dynamic_bitset<> *get_bitset();
    void releaseBitset();
    [[nodiscard]] inline bool test(u32 idx) {
        return this->get_bitset()->test(idx);
    }
    [[nodiscard]] inline u32 cardinality() const {
        return this->m_cardinality;
    };
    [[nodiscard]] inline BitmapType type() const {
        return this->m_type;
    };
    [[nodiscard]] inline Roaring &roaring() {
        return this->m_roaring;
    };
};
class RoaringBitmap {
public:
   static std::pair<u32, BitmapType> compress(const BITMAP *bitmap, u8 *dest, u32 tuple_count);
};
// -------------------------------------------------------------------------------------
}
using BitmapWrapper = cengine::db::v2::bitmap::BitmapWrapper;