#include "TestCaseRepresentation.h"
#include "BLOSUMAlgorithmTest.h"
namespace MBI_project {
namespace Tests {
using namespace MBI_project::Algorithm;

QList<BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>*> BLOSUMAlgorithmTest::alg_ = QList<BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>*>();
QList<TestCaseRepresentation*> BLOSUMAlgorithmTest::tests_ = QList<TestCaseRepresentation*>();


void BLOSUMAlgorithmTest::SetUpTestCase() {

   QRegExp regExp("^[A-Za-z]{2}=.*$");

   QDirIterator dirIt(QDir::current(),QDirIterator::Subdirectories);

   while (dirIt.hasNext()) {
     dirIt.next();
     if (QFileInfo(dirIt.filePath()).isFile()) {
       if (QFileInfo(dirIt.filePath()).suffix() == "mbi") {
         BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType> *alg = new BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>;
         
         TestCaseRepresentation *test = new TestCaseRepresentation;

       	 QFile file(dirIt.filePath());
         if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
           continue; 
	
         QByteArray data = file.readAll();
         QList<QByteArray> list = data.split(';');
         QList<QByteArray>::iterator i;
         for (i = list.begin(); i != list.end(); ++i) {
           if((*i).size() <= 1) 
             continue;
           if(regExp.exactMatch(*i))
             test->addExpectedResult(*i);
           else {
             alg->addSequence(new QByteArray(*i));
	   }             
 	 }
         alg_.append(alg);
         tests_.append(test);         
       }
    }  
  }
  
  QList<BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>*>::iterator it;
  for(it = alg_.begin(); it != alg_.end(); ++it)
    (*it)->run();
}

void BLOSUMAlgorithmTest::TearDownTestCase() {
  alg_.clear();
  tests_.clear();
}

}
}
