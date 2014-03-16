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
namespace Tests {

typedef char SymbolType;
typedef QByteArray SequenceType;
typedef int IntType;
typedef float FloatType;

class TestCaseRepresentation {
    
public:
  
  /**
   * @brief Constructor
   */
  TestCaseRepresentation();
  
  /**
   * @brief Destructor
   */
  ~TestCaseRepresentation();
  
  /**
   * @brief Method used to fill object with
   * information about expected results
   */
  void addExpectedResult(QByteArray);
  
  /**
   * @brief Checks results provided by algorithm and data,
   * that was written in a file, used GoogleTest asserts instead
   * of return value
   */
  void check(const QHash<QPair<SymbolType,SymbolType>, int>*);

private:
  
  /**
   * @brief List of all expected results,
   * that are used to compare with actual results
   * from algorithm
   */
  QHash<QPair<SymbolType, SymbolType>, FloatType> *m_blosum;	

};

}
}

#endif
