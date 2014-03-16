#include <gtest/gtest.h>
#include "BLOSUMAlgorithm.h"
#define FLOAT_PRECISION 0.01
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

  alg->addSequence(new QByteArray("AAI"));
  alg->addSequence(new QByteArray("SAL"));
  alg->addSequence(new QByteArray("TAL"));
  alg->addSequence(new QByteArray("TAV"));
  alg->addSequence(new QByteArray("AAL"));

  alg->run();

  return alg;
}

TEST(BLOSUMExampleTests, NumberOfPairsTest)
{
  BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType> *alg = getInstanceForTests();

  ASSERT_EQ(alg->getNmbOfAllPairs(), 30);

  ASSERT_EQ((*alg->getPairsNumbers())[qMakePair('A','A')], 11);  

  ASSERT_EQ((*alg->getPairsNumbers())[qMakePair('A','S')], 2);
  
  ASSERT_EQ((*alg->getPairsNumbers())[qMakePair('A','T')], 4);

  ASSERT_EQ((*alg->getPairsNumbers())[qMakePair('I','L')], 3);

  ASSERT_EQ((*alg->getPairsNumbers())[qMakePair('I','V')], 1);

  ASSERT_EQ((*alg->getPairsNumbers())[qMakePair('L','L')], 3);

  ASSERT_EQ((*alg->getPairsNumbers())[qMakePair('L','V')], 3);

  ASSERT_EQ((*alg->getPairsNumbers())[qMakePair('S','T')], 2);

  ASSERT_EQ((*alg->getPairsNumbers())[qMakePair('T','T')], 1); 

  delete alg;
}

TEST(BLOSUMExampleTests, NumberOfPairsNormalizedTest)
{
  BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType> *alg = getInstanceForTests();

  ASSERT_NEAR((*alg->getPairsNumbersNormalized())[qMakePair('A','A')], 0.367, FLOAT_PRECISION);

  ASSERT_NEAR((*alg->getPairsNumbersNormalized())[qMakePair('A','S')], 0.067, FLOAT_PRECISION);

  ASSERT_NEAR((*alg->getPairsNumbersNormalized())[qMakePair('A','T')], 0.133, FLOAT_PRECISION);

  ASSERT_NEAR((*alg->getPairsNumbersNormalized())[qMakePair('I','L')], 0.1,   FLOAT_PRECISION);

  ASSERT_NEAR((*alg->getPairsNumbersNormalized())[qMakePair('I','V')], 0.033, FLOAT_PRECISION);

  ASSERT_NEAR((*alg->getPairsNumbersNormalized())[qMakePair('L','L')], 0.1,   FLOAT_PRECISION);

  ASSERT_NEAR((*alg->getPairsNumbersNormalized())[qMakePair('L','V')], 0.1,   FLOAT_PRECISION);

  ASSERT_NEAR((*alg->getPairsNumbersNormalized())[qMakePair('S','T')], 0.067, FLOAT_PRECISION);

  ASSERT_NEAR((*alg->getPairsNumbersNormalized())[qMakePair('T','T')], 0.033, FLOAT_PRECISION);

  delete alg;
}


TEST(BLOSUMExampleTests, NormalizationTest)
{
  BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType> *alg = getInstanceForTests();

  ASSERT_NEAR(((float)((*alg->getPairsNumbers())[qMakePair('A','A')])
    / alg->getNmbOfAllPairs()),((*alg->getPairsNumbersNormalized())
    [qMakePair('A','A')]), 0.01);

  ASSERT_NEAR(((float)((*alg->getPairsNumbers())[qMakePair('A','S')])
    / alg->getNmbOfAllPairs()),((*alg->getPairsNumbersNormalized())
    [qMakePair('A','S')]), FLOAT_PRECISION);

  ASSERT_NEAR(((float)((*alg->getPairsNumbers())[qMakePair('A','T')])
    / alg->getNmbOfAllPairs()),((*alg->getPairsNumbersNormalized())
    [qMakePair('A','T')]), FLOAT_PRECISION);

  ASSERT_NEAR(((float)((*alg->getPairsNumbers())[qMakePair('I','L')])
    / alg->getNmbOfAllPairs()),((*alg->getPairsNumbersNormalized())
    [qMakePair('I','L')]), FLOAT_PRECISION);

  ASSERT_NEAR(((float)((*alg->getPairsNumbers())[qMakePair('I','V')])
    / alg->getNmbOfAllPairs()),((*alg->getPairsNumbersNormalized())
    [qMakePair('I','V')]), FLOAT_PRECISION);

  ASSERT_NEAR(((float)((*alg->getPairsNumbers())[qMakePair('L','L')])
    / alg->getNmbOfAllPairs()),((*alg->getPairsNumbersNormalized())
    [qMakePair('L','L')]), FLOAT_PRECISION);

  ASSERT_NEAR(((float)((*alg->getPairsNumbers())[qMakePair('L','V')])
    / alg->getNmbOfAllPairs()),((*alg->getPairsNumbersNormalized())
    [qMakePair('L','V')]), FLOAT_PRECISION);

  ASSERT_NEAR(((float)((*alg->getPairsNumbers())[qMakePair('S','T')])
    / alg->getNmbOfAllPairs()),((*alg->getPairsNumbersNormalized())
    [qMakePair('S','T')]), FLOAT_PRECISION);

  ASSERT_NEAR(((float)((*alg->getPairsNumbers())[qMakePair('T','T')])
    / alg->getNmbOfAllPairs()),((*alg->getPairsNumbersNormalized())
    [qMakePair('T','T')]), FLOAT_PRECISION);

  delete alg;
}

TEST(BLOSUMExampleTests, SymbolsProbabilitiesTest)
{
  BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType> *alg = getInstanceForTests();

  ASSERT_NEAR((*alg->getSymbolProbabilities())['A'], 0.467, FLOAT_PRECISION);

  ASSERT_NEAR((*alg->getSymbolProbabilities())['I'], 0.067, FLOAT_PRECISION);

  ASSERT_NEAR((*alg->getSymbolProbabilities())['L'], 0.2,   FLOAT_PRECISION);

  ASSERT_NEAR((*alg->getSymbolProbabilities())['S'], 0.067, FLOAT_PRECISION);

  ASSERT_NEAR((*alg->getSymbolProbabilities())['T'], 0.133, FLOAT_PRECISION);
 
  ASSERT_NEAR((*alg->getSymbolProbabilities())['V'], 0.067, FLOAT_PRECISION);

  delete alg;
}

TEST(BLOSUMExampleTests, FinalBlosumTest)
{
  BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType> *alg = getInstanceForTests();

  ASSERT_EQ((*alg->getBlosum())[qMakePair('A','A')], 2);

  ASSERT_EQ((*alg->getBlosum())[qMakePair('A','S')], 0);

  ASSERT_EQ((*alg->getBlosum())[qMakePair('A','T')], 0);

  ASSERT_EQ((*alg->getBlosum())[qMakePair('I','L')], 4);

  ASSERT_EQ((*alg->getBlosum())[qMakePair('I','V')], 4);

  ASSERT_EQ((*alg->getBlosum())[qMakePair('L','L')], 3);

  ASSERT_EQ((*alg->getBlosum())[qMakePair('L','V')], 4);

  ASSERT_EQ((*alg->getBlosum())[qMakePair('S','T')], 4);

  ASSERT_EQ((*alg->getBlosum())[qMakePair('T','T')], 2);

  delete alg;
}

}
}
