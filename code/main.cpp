#include "BLOSUMAlgorithm.h"
#include <QByteArray>
#include <QList>
#include <QDebug>

typedef char SymbolType;
typedef QByteArray SequenceType;
typedef int IntType;
typedef float FloatType;

int main(void)
{
    BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType> alg;

    alg.addSequence(new QByteArray("AAI"));
    alg.addSequence(new QByteArray("SAL"));
    alg.addSequence(new QByteArray("TAL"));
    alg.addSequence(new QByteArray("TAV"));
    alg.addSequence(new QByteArray("AAL"));

    alg.run();

    QList<QPair<SymbolType, SymbolType> > pairs = alg.getPairsNumbers()->keys();

    qSort(pairs);

    qDebug()<<alg.getNmbOfAllPairs();
    for (typename QList<QPair<SymbolType, SymbolType> >::Iterator it1 = pairs
            .begin(); it1 != pairs.end(); ++it1) {
        qDebug() << it1->first << it1->second << " " << (*alg.getPairsNumbers())[*it1];
    }

    return 0;
}
