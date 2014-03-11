#include <gtest/gtest.h>
#include "TestCaseRepresentation.h"

namespace MBI_project {
namespace Algorithm {
TestCaseRepresentation::TestCaseRepresentation() {
  m_blosum = new QHash<QPair<char,char>,int>();
}

TestCaseRepresentation::~TestCaseRepresentation() {
 delete m_blosum;
}


void TestCaseRepresentation::addExpectedResult(QByteArray array) {
  char *data = array.data();
  QPair<char, char> pair = qMakePair(data[0], data[1]);
  int a = (int)data[3] - 48;
  m_blosum->insert(pair,a);
}

void TestCaseRepresentation::check(const QHash<QPair<char,char>,int>* results) {
  QHash<QPair<char,char>,int>::const_iterator i;
  for (i = m_blosum->begin(); i != m_blosum->end(); ++i) {
    EXPECT_EQ(results->value(i.key()), i.value());
  }
}
}
}
