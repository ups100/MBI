#ifndef __TEST_CASE_REPRESENTATION_H__
#define __TEST_CASE_REPRESENTATION_H__
#include <QDirIterator>
#include <QFileInfo>
#include <QDebug>
#include <QHash>
#include <QVector>
#include <QDir>
#include <QRegExp>
namespace MBI_project {
namespace Algorithm {

class TestCaseRepresentation {
    
public:
  TestCaseRepresentation();

  ~TestCaseRepresentation();
  
  void addExpectedResult(QByteArray);
  void check(const QHash<QPair<char,char>, int>*);
private:
  QHash<QPair<char,char>, int> *m_blosum;	

};

}
}

#endif
