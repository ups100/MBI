#include <gtest/gtest.h>
#include "TestCaseRepresentation.h"

namespace MBI_project {
namespace Tests {

TestCaseRepresentation::TestCaseRepresentation() {
   m_blosum = new QHash<QPair<SymbolType, SymbolType>, FloatType>();
}

TestCaseRepresentation::~TestCaseRepresentation() {
  delete m_blosum;
}


void TestCaseRepresentation::addExpectedResult(QByteArray array) {
  char *data = array.data();

  QPair<SymbolType, SymbolType> pair = qMakePair(data[0], data[1]);

  QByteArray tmp = array.mid(3);

  m_blosum->insert(pair,QString(tmp).toInt());
}

void TestCaseRepresentation::check(const QHash<QPair<SymbolType, SymbolType>, IntType>* results) {
  QHash<QPair<SymbolType, SymbolType>, FloatType>::const_iterator i;
  for (i = m_blosum->begin(); i != m_blosum->end(); ++i) {
    EXPECT_EQ(results->value(i.key()), i.value());
  }
}
}
}
