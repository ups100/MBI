#include <gtest/gtest.h>
#include "BLOSUMAlgorithmTest.h"
#include "BLOSUMAlgorithm.h"
#include <QPair>
using namespace MBI_project::Tests;
using namespace MBI_project::Algorithm;
namespace MBI_project {
namespace Tests   {

TEST_F(BLOSUMAlgorithmTest, ProvidedPairsTest)
{
  ASSERT_EQ(tests_.size(), alg_.size());
  for(int i = 0; i < tests_.size(); ++i) {
    tests_[i]->check(alg_[i]->getBlosum());
  }
}

TEST_F(BLOSUMAlgorithmTest, NormalizationTest)
{
  for(int i = 0; i < alg_.size(); ++i) {
  
    BLOSUMAlgorithm<char, QByteArray, int, float> *alg = alg_[i];

    QList<QPair<char, char> > pairs = alg->getPairsNumbers()->keys();

    qSort(pairs);

    QList<QPair<char, char> >::Iterator it;

    for(it = pairs.begin(); it != pairs.end(); ++it) {
      ASSERT_NEAR(((float)((*alg->getPairsNumbers())[*it])
        / alg->getNmbOfAllPairs()),((*alg->getPairsNumbersNormalized())
        [*it]), 0.01);
    }
  }
}

}
}
