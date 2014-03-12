#if !defined(PAIRS_TEST_H_INCLUDED__)
#define PAIRS_TEST_INCLUDED__

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

using namespace MBI_project::Algorithm;

class BLOSUMAlgorithmTest : public ::testing::Test
{
protected:

  static void SetUpTestCase(); 
  static void TearDownTestCase(); 

  static QList<BLOSUMAlgorithm<char, QByteArray, int, float>*> alg_;
  static QList<TestCaseRepresentation*> tests_;
  
};

}
}
#endif
