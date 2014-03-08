#include <QObject>
#include <cmath>

namespace MBI_project {
namespace Algorithm {

template<class SymbolType, class SequenceType, class IntType, class FloatType>
BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::BLOSUMAlgorithm()
        : m_executed(false)
{

}

template<class SymbolType, class SequenceType, class IntType, class FloatType>
BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::~BLOSUMAlgorithm()
{
    clear();
}

template<class SymbolType, class SequenceType, class IntType, class FloatType>
void BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::clear()
{
    foreach(SequenceType* s, m_sequences){
        delete s;
    }

    m_sequences.clear();
    m_symbolSet.clear();
    m_numberOfPairs.clear();
    m_numberOfPairsNormalized.clear();
    m_symbolProbabilities.clear();
    m_expectedFrequency.clear();
    m_logs.clear();
    m_blosum.clear();

    m_executed = false;
}

template<class SymbolType, class SequenceType, class IntType, class FloatType>
const QHash<QPair<SymbolType, SymbolType>, IntType> *
BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::getPairsNumbers() const
{
    return m_executed ? &m_numberOfPairs : NULL;
}

template<class SymbolType, class SequenceType, class IntType, class FloatType>
IntType BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::getNmbOfAllPairs() const
{
    return m_executed ? m_nmbOfAllPairs : -1;
}

template<class SymbolType, class SequenceType, class IntType, class FloatType>
const QHash<QPair<SymbolType, SymbolType>, FloatType> *
BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::getPairsNumbersNormalized() const
{
    return m_executed ? &m_numberOfPairsNormalized : NULL;
}

template<class SymbolType, class SequenceType, class IntType, class FloatType>
const QHash<SymbolType, FloatType> *
BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::getSymbolProbabilities() const
{
    return m_executed ? &m_symbolProbabilities : NULL;
}

template<class SymbolType, class SequenceType, class IntType, class FloatType>
const QHash<QPair<SymbolType, SymbolType>, FloatType> *
BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::getLogs() const
{
    return m_executed ? &m_logs : NULL;
}

template<class SymbolType, class SequenceType, class IntType, class FloatType>
const QHash<QPair<SymbolType, SymbolType>, FloatType> *
BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::getExpectedFreq() const
{
    return m_executed ? &m_expectedFrequency : NULL;
}

template<class SymbolType, class SequenceType, class IntType, class FloatType>
const QHash<QPair<SymbolType, SymbolType>, IntType> *
BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::getBlosum() const
{
    return m_executed ? &m_blosum : NULL;
}

template<class SymbolType, class SequenceType, class IntType, class FloatType>
void BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::addSequence(
        SequenceType* seq)
{
    if (m_executed)
        throw BLOSUMAlgorithmException("Unable to add sequence to executed algorithm");

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
    if (m_executed)
        throw BLOSUMAlgorithmException("Already executed");
    else
        m_executed = true;

    countPairs();
    countAllPairsNmb();
    normalize();
    countProbabilities();
    countExpectedFrequency();
    countLogs();
    countBlosum();
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

    qSort(keys);

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

            if (nmbOfPairs) {
                if (m_numberOfPairs.contains(pair)) {
                    m_numberOfPairs[pair] += nmbOfPairs;
                } else {
                    m_numberOfPairs[pair] = nmbOfPairs;
                }
            }
        }
}

template<class SymbolType, class SequenceType, class IntType, class FloatType>
void BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::countAllPairsNmb()
{
    m_nmbOfAllPairs = m_sequencesSize * m_sequences.size()
            * (m_sequences.size() - 1) / 2;
}

template<class SymbolType, class SequenceType, class IntType, class FloatType>
void BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::normalize()
{
    QList<QPair<SymbolType, SymbolType> > pairs = m_numberOfPairs.keys();
    for (typename QList<QPair<SymbolType, SymbolType> >::Iterator it = pairs
            .begin(); it != pairs.end(); ++it) {
        m_numberOfPairsNormalized[*it] = ((FloatType) m_numberOfPairs[*it])
                / m_nmbOfAllPairs;
    }
}

template<class SymbolType, class SequenceType, class IntType, class FloatType>
void BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::countProbabilities()
{
    QVector<SymbolType> symbols = QVector<SymbolType>::fromList(
            m_symbolSet.values());
    /* Sort the symbols */
    qSort(symbols);

    for (int i = 0; i < symbols.size(); ++i) {
        SymbolType s1 = symbols[i];
        // both symbols the same (Qii)
        QPair<SymbolType, SymbolType> pair = qMakePair(s1, s1);
        m_symbolProbabilities[s1] = m_numberOfPairsNormalized[pair];

        // different symbols (Qij) (j < i)
        for (int j = 0; j < i; ++j) {
            pair = qMakePair(symbols[j], s1);
            m_symbolProbabilities[s1] += m_numberOfPairsNormalized[pair] / 2;
        }

        //different symbols (Qij) (j > i)
        for (int j = i + 1; j < symbols.size(); ++j) {
            pair = qMakePair(s1, symbols[j]);
            m_symbolProbabilities[s1] += m_numberOfPairsNormalized[pair] / 2;
        }
    }

}

template<class SymbolType, class SequenceType, class IntType, class FloatType>
void BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::countExpectedFrequency()
{
    QVector<QPair<SymbolType, SymbolType> > pairs = QVector<
            QPair<SymbolType, SymbolType> >::fromList(m_numberOfPairs.keys());
    for (int i = 0; i < pairs.size(); ++i) {
        QPair<SymbolType, SymbolType> pair = pairs[i];
        m_expectedFrequency[pair] = (pair.first == pair.second ? 1 : 2)
                * m_symbolProbabilities[pair.first]
                * m_symbolProbabilities[pair.second];
    }
}

template<class SymbolType, class SequenceType, class IntType, class FloatType>
void BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::countLogs()
{
    QVector<QPair<SymbolType, SymbolType> > pairs = QVector<
            QPair<SymbolType, SymbolType> >::fromList(
            m_expectedFrequency.keys());
    for (int i = 0; i < pairs.size(); ++i) {
        QPair<SymbolType, SymbolType> pair = pairs[i];
        m_logs[pair] = log2(
                m_numberOfPairsNormalized[pair] / m_expectedFrequency[pair]);
    }
}

template<class SymbolType, class SequenceType, class IntType, class FloatType>
FloatType BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::log2(
        FloatType x)
{
    static FloatType logof2 = log((FloatType) 2.0);

    return log(x) / logof2;
}

template<class SymbolType, class SequenceType, class IntType, class FloatType>
void BLOSUMAlgorithm<SymbolType, SequenceType, IntType, FloatType>::countBlosum()
{
    QVector<QPair<SymbolType, SymbolType> > pairs = QVector<
            QPair<SymbolType, SymbolType> >::fromList(m_logs.keys());
    for (int i = 0; i < pairs.size(); ++i) {
        QPair<SymbolType, SymbolType> pair = pairs[i];
        m_blosum[pair] = (IntType) (2 * m_logs[pair] + 0.5);
    }
}

} // namespace Algorithm
} // namespace MBI_project
