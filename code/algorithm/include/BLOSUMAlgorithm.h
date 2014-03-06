#ifndef __BLOSUM_ALGORITHM_H__
#define __BLOSUM_ALGORITHM_H__

#include <QVector>
#include <QSet>
#include <QPair>
#include <QHash>
#include <stdexcept>

template<class SymbolType, class SequenceType, class IntType, class FloatType>
class BLOSUMAlgorithm
{
public:
    BLOSUMAlgorithm();
    ~BLOSUMAlgorithm();

    void clear();

    /**
     * @brief takes the ownership
     */
    void addSequence(SequenceType* seq);

    void run();

    const QHash<QPair<SymbolType, SymbolType>, IntType> *
    getPairsNumbers();

    IntType getNmbOfAllPairs();

    const QHash<QPair<SymbolType, SymbolType>, FloatType> *
    getPairsNumbersNormalized();

    class BLOSUMAlgorithmException : public std::runtime_error
    {
    public:
        /**
         * @brief Constructor
         * @param[in] arg exception string
         */
        explicit BLOSUMAlgorithmException(const std::string& arg)
                : std::runtime_error(arg)
        {
        }
    };
private:
    // helper functions
    void countPairs();
    void countPairsInColumn(IntType col);
    void countAllPairsNmb();
    void normalize();

    bool m_executed;

    //Input
    QVector<SequenceType*> m_sequences;
    IntType m_sequencesSize;
    QSet<SymbolType> m_symbolSet;
    QVector<SymbolType> m_symbols;

    //Output
    QHash<QPair<SymbolType, SymbolType>, IntType> m_numberOfPairs;
    IntType m_nmbOfAllPairs;
    QHash<QPair<SymbolType, SymbolType>, FloatType> m_numberOfPairsNormalized;
};

#include "BLOSUMAlgorithmImpl.h"

#endif //__BLOSUM_ALGORITHM_H__
