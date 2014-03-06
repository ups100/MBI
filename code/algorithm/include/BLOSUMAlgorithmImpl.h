#include <QObject>

template<class SymbolType, class SequenceType, class IntType, class FloatType>
BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::BLOSUMAlgorithm()
{

}

template<class SymbolType, class SequenceType, class IntType, class FloatType>
BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::~BLOSUMAlgorithm()
{
    foreach(SequenceType* s, m_sequences) {
        delete s;
    }

    m_sequences.clear();
}

template<class SymbolType, class SequenceType, class IntType, class FloatType>
const QHash<QPair<SymbolType, SymbolType>, IntType> *
BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::getPairsNumbers()
{
    return &m_numberOfPairs;
}

template<class SymbolType, class SequenceType, class IntType, class FloatType>
IntType BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::getNmbOfAllPairs()
{
    return m_nmbOfAllPairs;
}

template<class SymbolType, class SequenceType, class IntType, class FloatType>
void BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::addSequence(
        SequenceType* seq)
{
    // All sequences should be same size
    IntType size = seq->size();
    if (m_sequences.empty()) {
        m_sequencesSize = size;
    } else if (m_sequencesSize != size) {
        throw BLOSUMAlgorithmException("Wrong size");
    }

    //Lets update symbol set
    for (IntType i = 0; i < size; ++i) {
        m_symbolSet.insert((*seq)[i]);
    }

    m_sequences.append(seq);
}

template<class SymbolType, class SequenceType, class IntType, class FloatType>
void BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::run()
{
    countPairs();
    countAllPairsNmb();
}

template<class SymbolType, class SequenceType, class IntType, class FloatType>
void BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::countPairs()
{
    for (IntType i = 0; i < m_sequencesSize; ++i) {
        countPairsInColumn(i);
    }
}

template<class SymbolType, class SequenceType, class IntType, class FloatType>
void BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::countPairsInColumn(
        IntType col)
{
    int rows = m_sequences.size();
    QHash<SymbolType, IntType> numberOfSymbols;
    SymbolType s;

    // Count symbols in this column
    for (int row = 0; row < rows; ++row) {
        s = (*m_sequences[row])[col];
        if (numberOfSymbols.contains(s)) {
            numberOfSymbols[s] += 1;
        } else {
            numberOfSymbols[s] = 1;
        }
    }

    QList<SymbolType> keys = numberOfSymbols.keys();

    //count pairs and update the table
    for (typename QList<SymbolType>::Iterator it1 = keys.begin();
            it1 != keys.end(); ++it1)
        for (typename QList<SymbolType>::Iterator it2 = it1; it2 != keys.end();
                ++it2) {
            QPair<SymbolType, SymbolType> pair = qMakePair(*it1, *it2);
            IntType nmbOfPairs;

            if (*it1 == *it2) {
                //We have pair of that same symbols (AA)
                nmbOfPairs = numberOfSymbols[*it1] * (numberOfSymbols[*it1] - 1)
                        / 2;
            } else {
                //We have pair of different symbols
                nmbOfPairs = numberOfSymbols[*it1] * numberOfSymbols[*it2];
            }

            if (m_numberOfPairs.contains(pair)) {
                m_numberOfPairs[pair] += nmbOfPairs;
            } else {
                m_numberOfPairs[pair] = nmbOfPairs;
            }
        }
}

template<class SymbolType, class SequenceType, class IntType, class FloatType>
void BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::countAllPairsNmb()
{
    m_nmbOfAllPairs = m_sequencesSize * m_sequences.size()
            * (m_sequences.size() - 1) / 2;
}
