#include "BLOSUMAlgorithm.h"
#include <QByteArray>
#include <QList>
#include <QDebug>

//Quick remove typename keyword from this file in Visual Studio
// this compiler complains that this is bad usage of this keyword
#ifdef WIN32
	#define typename
#endif

using namespace MBI_project::Algorithm;

typedef char SymbolType;
typedef QByteArray SequenceType;
typedef int IntType;
typedef float FloatType;

int main(void)
{
    BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType> alg;

//    alg.addSequence(new QByteArray("CCAAABAC"));
//    alg.addSequence(new QByteArray("CCAABBAB"));
//    alg.addSequence(new QByteArray("BBCACBAB"));
//    alg.addSequence(new QByteArray("CBCACBAB"));
//    alg.addSequence(new QByteArray("CCCABBAB"));
//    alg.addSequence(new QByteArray("CCCBBBAB"));
      alg.addSequence(new QByteArray("MNMSRQGIFQ"));
      alg.addSequence(new QByteArray("MNTTDCFIAL"));
      alg.addSequence(new QByteArray("MGAQVSSQKV"));
      alg.addSequence(new QByteArray("MNDQRKKAKN"));
      alg.addSequence(new QByteArray("MSGRKAQGKT"));
      alg.addSequence(new QByteArray("MSKKPGGPGK"));
      alg.addSequence(new QByteArray("MESLVLGVNE"));
      alg.addSequence(new QByteArray("MALIFGTVNA"));
      alg.addSequence(new QByteArray("MELEDGVVYQ"));
      alg.addSequence(new QByteArray("MESLVLGVNE"));
      alg.addSequence(new QByteArray("MACNRVTLAV"));
      alg.addSequence(new QByteArray("MATFSATGFG"));
      alg.addSequence(new QByteArray("MASSLKQGVS"));
      alg.addSequence(new QByteArray("MRLRRLALFP"));

    alg.run();

    QList<QPair<SymbolType, SymbolType> > pairs = alg.getPairsNumbers()->keys();

    qSort(pairs);

    qDebug() << alg.getNmbOfAllPairs();
    for (typename QList<QPair<SymbolType, SymbolType> >::Iterator it1 = pairs
            .begin(); it1 != pairs.end(); ++it1) {
        qDebug() << it1->first << it1->second << " "
                << (*alg.getPairsNumbers())[*it1];
    }

    for (typename QList<QPair<SymbolType, SymbolType> >::Iterator it1 = pairs
            .begin(); it1 != pairs.end(); ++it1) {
        qDebug() << it1->first << it1->second << " "
                << (*alg.getPairsNumbersNormalized())[*it1];
    }

    QList<SymbolType> symbols = alg.getSymbolProbabilities()->keys();

    qSort(symbols);

    for (typename QList<SymbolType>::Iterator it1 = symbols.begin();
            it1 != symbols.end(); ++it1) {
        qDebug() << *it1 << " " << (*alg.getSymbolProbabilities())[*it1];
    }

    for (typename QList<QPair<SymbolType, SymbolType> >::Iterator it1 = pairs
            .begin(); it1 != pairs.end(); ++it1) {
        qDebug() << it1->first << it1->second << " "
                << (*alg.getBlosum())[*it1];
    }

    return 0;
}
