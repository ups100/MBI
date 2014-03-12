#ifndef __BLOSUM_ALGORITHM_TEST_H__
#define __BLOSUM_ALGORITHM_TEST_H__

#include <gtest/gtest.h>
#include "BLOSUMAlgorithm.h"
#include "TestCaseRepresentation.h"
#include <QDebug>
#include <QList>
#include <QByteArray>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>

namespace MBI_project {
namespace Tests {

typedef char SymbolType;
typedef QByteArray SequenceType;
typedef int IntType;
typedef float FloatType; 

using namespace MBI_project::Algorithm;

class BLOSUMAlgorithmTest : public ::testing::Test
{
protected:
  
  /**
   * @brief Invoked by GTest before all tests,
   * used to read all examples with .mbi suffix
   * and create necessary TestCaseRepresentation 
   * objects
   * @see TestCaseRepresentation
   */
  static void SetUpTestCase();

  /**
   * @brief Kind of destructor for all tests,
   * deletes data stored in TestCases and in
   * BLOSUMAlgorithm objects
   */ 
  static void TearDownTestCase(); 

  /**
   * @brief static list of all used instances, 
   * each of them is responsible for one group 
   * of sequences
   */
  static QList<BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>*> alg_;
  
  /**
   * @brief List of objects used to representate examples
   * that are read from external files
   */
  static QList<TestCaseRepresentation*> tests_;
  
};

}
}
#endif
