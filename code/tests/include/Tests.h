#include <gtest/gtest.h>
#include "BLOSUMAlgorithmTest.h"
#include "BLOSUMAlgorithm.h"
#include <QPair>
using namespace MBI_project::Tests;
using namespace MBI_project::Algorithm;
namespace MBI_project{
namespace Algorithm{

TEST_F(BLOSUMAlgorithmTest, SequenceLengthCheck)
{
  BLOSUMAlgorithm<char, QByteArray, int, float> alg;

  ASSERT_NO_THROW(alg.addSequence(new QByteArray("ALA")));

  ASSERT_ANY_THROW(alg.addSequence(new QByteArray("ABCD")));

  ASSERT_NO_THROW(alg.addSequence(new QByteArray("TOM")));
}

TEST_F(BLOSUMAlgorithmTest, CountPairsTest)
{
  ASSERT_FLOAT_EQ(alg_->getNmbOfAllPairs(), 30); 
}

TEST_F(BLOSUMAlgorithmTest, CountAllPairsNmbTest)
{
  //TODO
}

TEST_F(BLOSUMAlgorithmTest, normalizeTest)
{
  //TODO
}

TEST_F(BLOSUMAlgorithmTest, CountProbabilitiesTest)
{
  //TODO
}

TEST_F(BLOSUMAlgorithmTest, CountExpectedFrequency)
{
  //TODO
}

TEST_F(BLOSUMAlgorithmTest, CountBlosum)
{
  //TODO
}

}
}
