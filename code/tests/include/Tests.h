#include <gtest/gtest.h>
#include "BLOSUMAlgorithmTest.h"
#include "BLOSUMAlgorithm.h"
#include <QPair>
using namespace MBI_project::Tests;
using namespace MBI_project::Algorithm;
namespace MBI_project{
namespace Algorithm{

TEST(BLOSUMSimpleTest, SequenceLengthCheck)
{
  BLOSUMAlgorithm<char, QByteArray, int, float> alg;

  ASSERT_NO_THROW(alg.addSequence(new QByteArray("ALA")));

  ASSERT_ANY_THROW(alg.addSequence(new QByteArray("ABCD")));

  ASSERT_NO_THROW(alg.addSequence(new QByteArray("TOM")));
}

TEST_F(BLOSUMAlgorithmTest, MainTest)
{
  ASSERT_EQ(tests_.size(), alg_.size());
  for(int i = 0; i < tests_.size(); ++i) {
    alg_[i]->getBlosum();
    tests_[i]->check(alg_[i]->getBlosum());
  }
}


}
}
