#include "BLOSUMAlgorithmTest.h"
namespace MBI_project {
namespace Tests {

BLOSUMAlgorithm<char, QByteArray, int, float>* BLOSUMAlgorithmTest::alg_ = NULL;

void BLOSUMAlgorithmTest::SetUpTestCase() {
  alg_ = new BLOSUMAlgorithm<char,QByteArray,int,float>;
  

  //TODO Working on bigger sequences
  alg_->addSequence(new QByteArray("AAI"));
  alg_->addSequence(new QByteArray("SAL"));
  alg_->addSequence(new QByteArray("TAL"));
  alg_->addSequence(new QByteArray("TAV"));
  alg_->addSequence(new QByteArray("AAL"));

  alg_->run();
}

void BLOSUMAlgorithmTest::TearDownTestCase() {
  delete alg_;
}

void BLOSUMAlgorithmTest::SetUp() {
}

void BLOSUMAlgorithmTest::TearDown() {
}


}
}
