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

    alg.addSequence(new QByteArray("ARTSCRKSGG"));
    alg.addSequence(new QByteArray("ARTSCHKSGG"));
    alg.addSequence(new QByteArray("IHEQIGQGAL"));

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
