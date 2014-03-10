#if !defined(PAIRS_TEST_H_INCLUDED__)
#define PAIRS_TEST_INCLUDED__

#include <gtest/gtest.h>
#include "BLOSUMAlgorithm.h"
#include <QDebug>
#include <QList>
#include <QByteArray>
namespace MBI_project {
namespace Tests {

using namespace MBI_project::Algorithm;

class BLOSUMAlgorithmTest : public ::testing::Test
{
protected:

  static void SetUpTestCase(); 
  static void TearDownTestCase(); 

  virtual void SetUp();
  virtual void TearDown(); 

  static BLOSUMAlgorithm<char, QByteArray, int, float>* alg_;
  
private:
};

}
}
#endif
