#include "tableabstract.h"
#include <QSet>

TableAbstract::TableAbstract(const int dimIn, QWidget *parent) :
    QWidget(parent), m_dim(dimIn)
{

}

QVector<QVector<double> > TableAbstract::getRawData() const
{
    return m_array;
}

void TableAbstract::transformIntoArray(TMatrix *mat)
{
    QSet<SymbolType> symbols;
    QList<QPair<SymbolType, SymbolType> > pairs = mat->keys();

    for (QList<QPair<SymbolType, SymbolType> >::Iterator it = pairs
            .begin(); it != pairs.end(); ++it) {
        symbols.insert(it->first);
        symbols.insert(it->second);
    }
    m_symbols = symbols.toList();
    qSort(m_symbols);

    int size = m_symbols.size();

    //init two dimmension array
    for (int i = 0; i < size; ++i) {
        m_array.push_back(QVector<double>(size));
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i < j)
                m_array[i][j] = (*mat)[qMakePair(m_symbols[i], m_symbols[j])];
            else
                m_array[i][j] = (*mat)[qMakePair(m_symbols[j], m_symbols[i])];
        }
    }

//    for (int i = 0; i < size; ++i) {
//        for (int j = 0; j < size; ++j) {
//            std::cout << m_array[i][j] << " ";
//            if (j == size - 1) std::cout << std::endl;
//        }
//    }

}
