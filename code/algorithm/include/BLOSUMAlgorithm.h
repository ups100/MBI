#ifndef __BLOSUM_ALGORITHM_H__
#define __BLOSUM_ALGORITHM_H__

#include <QVector>
#include <QSet>
#include <QPair>
#include <QHash>
#include <stdexcept>

namespace MBI_project {
namespace Algorithm {

template<class SymbolType, class SequenceType, class IntType, class FloatType>
class BLOSUMAlgorithm
{
public:
    /**
     * @brief Constructor
     */
    BLOSUMAlgorithm();

    /**
     * @brief Destructor
     */
    ~BLOSUMAlgorithm();

    /**
     * @brief Clears the content of internal class structures
     * @details This functions removes all seqences and results
     * and allow to reuse this object for other data
     */
    void clear();

    /**
     * @brief Add sequence to set of sequences
     * @details Sequences may not be added if algorithm has been already run
     * @param[in] seq sequence of symbols to be added
     *
     * @throw BLOSUMAlgorithmException if sequences with different lengths has
     * been provided
     */
    void addSequence(SequenceType* seq);

    /**
     * @brief Runs the BLOSUM algorithm and store results in internal structures
     */
    void run();

    /**
     * @brief Gets pair count
     * @return Map in which key is a pair of symbols and value
     * is number of such pairs in given sequences or NULL if algorithm
     * has not been run
     *
     * @note Returned map contains only pairs which were present in given sequences
     * at least once
     *
     * @see run()
     */
    const QHash<QPair<SymbolType, SymbolType>, IntType> *
    getPairsNumbers() const;

    /**
     * @brief Gets the total number of possible pairs in sequences
     * @return Number of possible pairs in sequences or -1 if algorithm
     * has not been run
     *
     * @see run()
     */
    IntType getNmbOfAllPairs() const;

    /**
     * @brief Gets the number of each pair normalized to number
     * of total possible pairs
     * @return Map which contains pair of symbols as a key
     * and value between 0 and 1 which determines the participation
     * of this pair in total number of pairs or NULL if algorithm has
     * not been run
     *
     * @note Returned map contains only pairs which were present in given sequences
     * at least once
     *
     * @see run()
     */
    const QHash<QPair<SymbolType, SymbolType>, FloatType> *
    getPairsNumbersNormalized() const;

    /**
     * @brief Gets the probability of each symbol
     * @return Map which contain symbol as a key and its probability
     * as a value or NULL if algorithm has not been run()
     *
     * @note Returned map contains only pairs which were present in given sequences
     * at least once
     *
     * @see run()
     */
    const QHash<SymbolType, FloatType> *getSymbolProbabilities() const;

    /**
     * @brief Gets the expected frequency of each symbols pair
     * @return Map which contains pairs of symbols as a key and their expected
     * frequency as a value or NULL if algorithm has not been run
     *
     * @note Returned map contains only pairs which were present in given sequences
     * at least once
     *
     * @see run()
     */
    const QHash<QPair<SymbolType, SymbolType>, FloatType> *getExpectedFreq() const;

    /**
     * @brief Gets the binary logarithm counted in algorithm
     * @return Map which contains pairs of symbols as a key and
     * binary logarithm of division of probability and expected frequency
     * of each pair or NULL if algorithm has not been run
     *
     * @note Returned map contains only pairs which were present in given sequences
     * at least once
     *
     * @see run()
     */
    const QHash<QPair<SymbolType, SymbolType>, FloatType> *getLogs() const;

    /**
     * @brief Gets the counted values of substitution matrix
     * @return Map which contains pair of symbols as key
     * and their value in substitution matrix or NULL if algorithm
     * has not been run
     *
     * @note If pair is not present in this map it means that the value
     * is undefined due to not enough sequences provided
     *
     * @see run()
     */
    const QHash<QPair<SymbolType, SymbolType>, IntType> *getBlosum() const;

	/**
	 * @brief Return number of all unique symbols used in all given sequences.
	 */
	int getSymbolsNumber() const;

    /**
     * @brief Exception class for this algorithm
     */
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
    /**
     * @brief Counts number of pairs in each column
     * @details Results are stored in #m_numberOfPairs
     *
     * @see countPairsInColumn()
     */
    void countPairs();

    /**
     * @brief Count number of pairs in selected column
     * @details Results are stored in #m_numberOfPairs
     * @param[in] col index of selected column
     */
    void countPairsInColumn(IntType col);

    /**
     * @brief Calculates number of total pairs in all columns
     * @details Result is stored in #m_nmbOfAllPairs
     */
    void countAllPairsNmb();

    /**
     * @brief Normalize number of pairs to number of all pairs
     * @details Results are stored in #m_numberOfPairsNormalized
     */
    void normalize();

    /**
     * @brief Counts the probability of each symbol
     * @details Results are stored in #m_symbolProbabilities
     */
    void countProbabilities();

    /**
     * @brief Counts the expected frequency of each pair
     * @details Resuts are stored in #m_expectedFrequency
     */
    void countExpectedFrequency();

    /**
     * @brief Counts the binary logarithm of qij/eij
     * @details Results are stored in m_logs
     */
    void countLogs();

    /**
     * @brief Counts the values of BLOSUM matrix
     * @details Results are stored in #m_blosum
     */
    void countBlosum();

    /**
     * @brief Counts the binary logarithm of x
     * @param[in] x number to count logarithm of it
     * @return Binary logarithm of x
     */
    FloatType log2(FloatType x);

    /**
     * @brief Value which determines if algorithm has been already executed
     */
    bool m_executed;

    //Input
    /**
     * @brief Vector of sequences for algorithms
     */
    QVector<SequenceType*> m_sequences;

    /**
     * @brief Length of sequence
     */
    IntType m_sequencesSize;

    /**
     * @brief Set of symbols provided to algorithm
     */
    QSet<SymbolType> m_symbolSet;

    //Output
    /**
     * @brief Map of pairs as a key and their number as value
     * @details If pair is not present in any of input columns
     * it is also not present here (0 values are not stored)
     */
    QHash<QPair<SymbolType, SymbolType>, IntType> m_numberOfPairs;

    /**
     * @brief Total number of all pairs
     */
    IntType m_nmbOfAllPairs;

    /**
     * @brief Number of each pair normalized to total number of pairs
     */
    QHash<QPair<SymbolType, SymbolType>, FloatType> m_numberOfPairsNormalized;

    /**
     * @brief Probabilities of each symbol
     */
    QHash<SymbolType, FloatType> m_symbolProbabilities;

    /**
     * @brief Expected frequency of occurrence of each pair
     */
    QHash<QPair<SymbolType, SymbolType>, FloatType> m_expectedFrequency;

    /**
     * @brief Binary logarithms of result of #m_numberOfPairsNormalized divided
     * by m_expectedFrequency
     */
    QHash<QPair<SymbolType, SymbolType>, FloatType> m_logs;

    /**
     * @brief BLOSUM matrix - final result
     */
    QHash<QPair<SymbolType, SymbolType>, IntType> m_blosum;
};

} // namespace Algorithm
} // namespace MBI_project

// Implementation of template
#include "BLOSUMAlgorithmImpl.h"

#endif //__BLOSUM_ALGORITHM_H__
