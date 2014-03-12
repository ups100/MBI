#include <gtest/gtest.h>
#include "BLOSUMAlgorithm.h"

using namespace MBI_project::Tests;
using namespace MBI_project::Algorithm;

namespace MBI_project {
namespace Tests {

TEST(BLOSUMSimpleTests, SequenceLengthTest) 
{
  BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType> alg;
  
  ASSERT_NO_THROW(alg.addSequence(new QByteArray("ALA")));
  ASSERT_ANY_THROW(alg.addSequence(new QByteArray("ABCD")));
  ASSERT_NO_THROW(alg.addSequence(new QByteArray("TOM")));
}

TEST(BLOSUMSimpleTests, SameTestRunTest)
{
  BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType> alg;

  alg.addSequence(new QByteArray("ABCD"));
  alg.addSequence(new QByteArray("BCDA"));
  alg.addSequence(new QByteArray("CDBA"));

  ASSERT_NO_THROW(alg.run());

  ASSERT_ANY_THROW(alg.run());
}


TEST(BLOSUMSimpleTests, GetResultBeforeRunTest)
{
  BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType> alg;
  
  alg.addSequence(new QByteArray("ALA"));

  alg.addSequence(new QByteArray("TOM"));
 
  EXPECT_EQ(NULL, alg.getBlosum());

  ASSERT_NO_THROW(alg.run());

  EXPECT_TRUE(alg.getBlosum() != NULL);
}

TEST(BLOSUMSimpleTests, NoSequencesTest)
{
  BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType> alg;
  
  ASSERT_ANY_THROW(alg.run());

  EXPECT_TRUE(alg.getPairsNumbers() == NULL);
  
  EXPECT_EQ(alg.getNmbOfAllPairs(), -1);
  
  EXPECT_TRUE(alg.getPairsNumbersNormalized() == NULL);
  
  EXPECT_TRUE(alg.getSymbolProbabilities() == NULL);
 
  EXPECT_TRUE(alg.getExpectedFreq() == NULL);

  EXPECT_TRUE(alg.getLogs() == NULL);

  EXPECT_TRUE(alg.getBlosum() == NULL);
}

TEST(BLOSUMSimpleTests, WithSequencesTest)
{
  BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType> alg;
 
  alg.addSequence(new QByteArray("ALA"));

  alg.addSequence(new QByteArray("AAA"));
  
  alg.run();

  EXPECT_TRUE(alg.getPairsNumbers() != NULL);

  EXPECT_TRUE(alg.getPairsNumbersNormalized() != NULL);

  EXPECT_TRUE(alg.getSymbolProbabilities() != NULL);

  EXPECT_TRUE(alg.getExpectedFreq() != NULL);

  EXPECT_TRUE(alg.getLogs() != NULL);

  EXPECT_TRUE(alg.getBlosum() != NULL);
}

TEST(BLOSUMSimpleTests, ReusabilityTest) 
{
  BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType> alg;
  
  alg.addSequence(new QByteArray("AAA"));
  alg.addSequence(new QByteArray("ABA"));
  alg.addSequence(new QByteArray("BAB"));

  alg.run();

  alg.clear();

  ASSERT_NO_THROW(alg.addSequence(new QByteArray("AAAA")));
  ASSERT_NO_THROW(alg.addSequence(new QByteArray("ABBA")));

  ASSERT_NO_THROW(alg.run()); 
}

BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>*  getInstanceForTests()
{
  BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>* alg = new BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>;

  alg->addSequence(new QByteArray("CCAAABAC"));
  alg->addSequence(new QByteArray("CCAABBAB"));
  alg->addSequence(new QByteArray("BBCACBAB"));
  alg->addSequence(new QByteArray("CBCACBAB"));
  alg->addSequence(new QByteArray("CCCABBAB"));
  alg->addSequence(new QByteArray("CCCBBBAB"));

  alg->run();

  return alg;
}

TEST(BLOSUMExampleTests, NumberOfPairsTest)
{
  BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType> *alg = getInstanceForTests();

  ASSERT_EQ(alg->getNmbOfAllPairs(),120);

  ASSERT_EQ((*alg->getPairsNumbers())[qMakePair('A','A')], 26);  

  ASSERT_EQ((*alg->getPairsNumbers())[qMakePair('A','B')], 8);

  ASSERT_EQ((*alg->getPairsNumbers())[qMakePair('A','C')], 10);

  ASSERT_EQ((*alg->getPairsNumbers())[qMakePair('B','B')], 29);

  ASSERT_EQ((*alg->getPairsNumbers())[qMakePair('B','C')], 24);

  ASSERT_EQ((*alg->getPairsNumbers())[qMakePair('C','C')], 23);
 
  delete alg;
}

TEST(BLOSUMExampleTests, NumberOfPairsNormalizedTest)
{
  BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType> *alg = getInstanceForTests();

  ASSERT_NEAR((*alg->getPairsNumbersNormalized())[qMakePair('A','A')], 0.216, 0.01);

  ASSERT_NEAR((*alg->getPairsNumbersNormalized())[qMakePair('A','B')], 0.066, 0.01);

  ASSERT_NEAR((*alg->getPairsNumbersNormalized())[qMakePair('A','C')], 0.083, 0.01);

  ASSERT_NEAR((*alg->getPairsNumbersNormalized())[qMakePair('B','B')], 0.242, 0.01);

  ASSERT_NEAR((*alg->getPairsNumbersNormalized())[qMakePair('B','C')], 0.2, 0.01);

  ASSERT_NEAR((*alg->getPairsNumbersNormalized())[qMakePair('C','C')], 0.192, 0.01);

  delete alg;
}


TEST(BLOSUMExampleTests, NormalizationTest)
{
  BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType> *alg = getInstanceForTests();

  ASSERT_NEAR(((float)((*alg->getPairsNumbers())[qMakePair('A','A')])
    / alg->getNmbOfAllPairs()),((*alg->getPairsNumbersNormalized())
    [qMakePair('A','A')]), 0.01);

  ASSERT_NEAR(((float)((*alg->getPairsNumbers())[qMakePair('A','B')])
    / alg->getNmbOfAllPairs()),((*alg->getPairsNumbersNormalized())
    [qMakePair('A','B')]), 0.01);

  ASSERT_NEAR(((float)((*alg->getPairsNumbers())[qMakePair('A','C')])
    / alg->getNmbOfAllPairs()),((*alg->getPairsNumbersNormalized())
    [qMakePair('A','C')]), 0.01);
  
  ASSERT_NEAR(((float)((*alg->getPairsNumbers())[qMakePair('B','B')])
    / alg->getNmbOfAllPairs()),((*alg->getPairsNumbersNormalized())
    [qMakePair('B','B')]), 0.01);

  ASSERT_NEAR(((float)((*alg->getPairsNumbers())[qMakePair('B','C')])
    / alg->getNmbOfAllPairs()),((*alg->getPairsNumbersNormalized())
    [qMakePair('B','C')]), 0.01);

  ASSERT_NEAR(((float)((*alg->getPairsNumbers())[qMakePair('C','C')])
    / alg->getNmbOfAllPairs()),((*alg->getPairsNumbersNormalized())
    [qMakePair('C','C')]), 0.01);

  delete alg;
}

TEST(BLOSUMExampleTests, SymbolsProbabilitiesTest)
{
  BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType> *alg = getInstanceForTests();

  ASSERT_NEAR((*alg->getSymbolProbabilities())['A'], 0.291, 0.01);

  ASSERT_NEAR((*alg->getSymbolProbabilities())['B'], 0.375, 0.01);

  ASSERT_NEAR((*alg->getSymbolProbabilities())['C'], 0.333, 0.01);

  delete alg;
}

TEST(BLOSUMExampleTests, FinalBlosumTest)
{
  BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType> *alg = getInstanceForTests();

  ASSERT_EQ((*alg->getBlosum())[qMakePair('A','A')], 3);

  ASSERT_EQ((*alg->getBlosum())[qMakePair('A','B')], -2);

  ASSERT_EQ((*alg->getBlosum())[qMakePair('A','C')], -1);

  ASSERT_EQ((*alg->getBlosum())[qMakePair('B','B')], 2);

  ASSERT_EQ((*alg->getBlosum())[qMakePair('B','C')], 0);

  ASSERT_EQ((*alg->getBlosum())[qMakePair('C','C')], 2);

  delete alg;
}

}
}
