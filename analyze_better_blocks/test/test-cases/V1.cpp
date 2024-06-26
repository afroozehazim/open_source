#include "storage/Relation.hpp"
#include "datablock/Datablock.hpp"
#include "TestHelper.hpp"
#include "datablock/schemes/CSchemePool.hpp"
// -------------------------------------------------------------------------------------
#include "gtest/gtest.h"
#include "gflags/gflags.h"
// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------
DECLARE_uint32(force_string_scheme);
DECLARE_uint32(force_integer_scheme);
DECLARE_uint32(force_double_scheme);
// -------------------------------------------------------------------------------------
using namespace cengine;
namespace harbook {
using namespace db;
// -------------------------------------------------------------------------------------
TEST(V1, IntegerOneValue)
{
   Relation relation;
   relation.addColumn(TEST_DATASET("integer/ONE_VALUE.integer"));
   cengine::db::Datablock Datablock(relation);
   TestHelper::CheckRelationCompression(relation, Datablock, {CB(IntegerSchemeType::ONE_VALUE)});
}
// -------------------------------------------------------------------------------------
TEST(V1, IntegerTruncate8)
{
   FLAGS_force_integer_scheme = CB(IntegerSchemeType::TRUNCATION_8);
   Relation relation;
   relation.addColumn(TEST_DATASET("integer/TRUNCATE_8.integer"));
   cengine::db::Datablock Datablock(relation);
   TestHelper::CheckRelationCompression(relation, Datablock, {CB(IntegerSchemeType::TRUNCATION_8)});
   FLAGS_force_integer_scheme = AUTO_SCHEME;
}
// -------------------------------------------------------------------------------------
TEST(V1, IntegerTruncate16)
{
   FLAGS_force_integer_scheme = CB(IntegerSchemeType::TRUNCATION_16);
   Relation relation;
   relation.addColumn(TEST_DATASET("integer/TRUNCATE_16.integer"));
   cengine::db::Datablock Datablock(relation);
   TestHelper::CheckRelationCompression(relation, Datablock, {CB(IntegerSchemeType::TRUNCATION_16)});
   FLAGS_force_integer_scheme = AUTO_SCHEME;
}
// -------------------------------------------------------------------------------------
TEST(V1, IntegerDictionary8)
{
   Relation relation;
   relation.addColumn(TEST_DATASET("integer/DICTIONARY_8.integer"));
   cengine::db::Datablock Datablock(relation);
   TestHelper::CheckRelationCompression(relation, Datablock, {CB(IntegerSchemeType::DICTIONARY_8)});
}
// -------------------------------------------------------------------------------------
TEST(V1, IntegerDictionary16)
{
   Relation relation;
   relation.addColumn(TEST_DATASET("integer/DICTIONARY_16.integer"));
   cengine::db::Datablock Datablock(relation);
   TestHelper::CheckRelationCompression(relation, Datablock, {CB(IntegerSchemeType::DICTIONARY_16)});
}
// -------------------------------------------------------------------------------------
TEST(V1, IntegerDictionary)
{
   Relation relation;
   relation.addColumn(TEST_DATASET("integer/DICTIONARY_8.integer"));
   relation.addColumn(TEST_DATASET("integer/DICTIONARY_16.integer"));
   cengine::db::Datablock Datablock(relation);
   TestHelper::CheckRelationCompression(relation, Datablock, {CB(IntegerSchemeType::DICTIONARY_8), CB(IntegerSchemeType::DICTIONARY_16)});
}
// -------------------------------------------------------------------------------------
TEST(V1, Integer)
{
   cengine::db::CSchemePool::refresh();
   // -------------------------------------------------------------------------------------
   Relation relation;
   relation.addColumn(TEST_DATASET("integer/ONE_VALUE.integer"));
   relation.addColumn(TEST_DATASET("integer/TRUNCATE_8.integer"));
   relation.addColumn(TEST_DATASET("integer/TRUNCATE_16.integer"));
   relation.addColumn(TEST_DATASET("integer/DICTIONARY_8.integer"));
   relation.addColumn(TEST_DATASET("integer/DICTIONARY_16.integer"));
   cengine::db::Datablock Datablock(relation);
   TestHelper::CheckRelationCompression(relation, Datablock,
                                        {
                                          CB(IntegerSchemeType::ONE_VALUE), CB(IntegerSchemeType::TRUNCATION_8), CB(IntegerSchemeType::TRUNCATION_16), CB(IntegerSchemeType::DICTIONARY_8)
                                          , CB(IntegerSchemeType::DICTIONARY_16)
                                        });
}
// -------------------------------------------------------------------------------------
TEST(V1, MixedTest)
{
   Relation relation;
   relation.addColumn(TEST_DATASET("integer/ONE_VALUE.integer"));
   relation.addColumn(TEST_DATASET("integer/TRUNCATE_8.integer"));
   relation.addColumn(TEST_DATASET("integer/TRUNCATE_16.integer"));
   relation.addColumn(TEST_DATASET("integer/DICTIONARY_8.integer"));
   relation.addColumn(TEST_DATASET("integer/DICTIONARY_16.integer"));
   relation.addColumn(TEST_DATASET("double/ONE_VALUE.double"));
   relation.addColumn(TEST_DATASET("string/ONE_VALUE.string"));
   relation.addColumn(TEST_DATASET("string/DICTIONARY_8.string"));
   relation.addColumn(TEST_DATASET("string/DICTIONARY_16.string"));
   cengine::db::Datablock datablockV2(relation);
   TestHelper::CheckRelationCompression(relation, datablockV2);
}
// -------------------------------------------------------------------------------------
TEST(V1, DoubleOneValue)
{
   Relation relation;
   relation.addColumn(TEST_DATASET("double/ONE_VALUE.double"));
   cengine::db::Datablock Datablock(relation);
   TestHelper::CheckRelationCompression(relation, Datablock, {CB(DoubleSchemeType::ONE_VALUE)});
}
// -------------------------------------------------------------------------------------
TEST(V1, DoubleDict8)
{
   FLAGS_force_double_scheme = CB(DoubleSchemeType::DICTIONARY_8);
   Relation relation;
   relation.addColumn(TEST_DATASET("double/DICTIONARY_8.double"));
   cengine::db::Datablock Datablock(relation);
   TestHelper::CheckRelationCompression(relation, Datablock, {CB(DoubleSchemeType::DICTIONARY_8)});
   FLAGS_force_double_scheme = AUTO_SCHEME;
}
// -------------------------------------------------------------------------------------
TEST(V1, DoubleDict16)
{
   FLAGS_force_double_scheme = CB(DoubleSchemeType::DICTIONARY_16);
   Relation relation;
   relation.addColumn(TEST_DATASET("double/DICTIONARY_16.double"));
   cengine::db::Datablock Datablock(relation);
   TestHelper::CheckRelationCompression(relation, Datablock, {CB(DoubleSchemeType::DICTIONARY_16)});
   FLAGS_force_double_scheme = AUTO_SCHEME;
}
// -------------------------------------------------------------------------------------
TEST(V1, DoubleRandom)
{
   Relation relation;
   relation.addColumn(TEST_DATASET("double/RANDOM.double"));
   cengine::db::Datablock Datablock(relation);
   TestHelper::CheckRelationCompression(relation, Datablock, {CB(DoubleSchemeType::UNCOMPRESSED)});
}
// -------------------------------------------------------------------------------------
TEST(V1, StringOneValue)
{
   Relation relation;
   relation.addColumn(TEST_DATASET("string/ONE_VALUE.string"));

   cengine::db::Datablock datablockV2(relation);
   TestHelper::CheckRelationCompression(relation, datablockV2, {CB(StringSchemeType::ONE_VALUE)});
}
// -------------------------------------------------------------------------------------
TEST(V1, StringDictionary)
{
   Relation relation;
   relation.addColumn(TEST_DATASET("string/DICTIONARY_8.string"));
   relation.addColumn(TEST_DATASET("string/DICTIONARY_16.string"));

   cengine::db::Datablock datablockV2(relation);
   TestHelper::CheckRelationCompression(relation, datablockV2, {CB(StringSchemeType::DICTIONARY_8), CB(StringSchemeType::DICTIONARY_16)});
}
// -------------------------------------------------------------------------------------
}
// -------------------------------------------------------------------------------------
