#ifndef TABLEABSTRACT_H
#define TABLEABSTRACT_H

#include <QWidget>
#include <QHash>
#include <QList>
#include <QVector>

// Types inherited from Blosum algorithm implementation
typedef char SymbolType;
typedef QByteArray SequenceType;
typedef int IntType;
typedef float FloatType;

// Types inherited from Blosum algorithm implementation
typedef QHash<QPair<SymbolType, SymbolType>, IntType> IntMatrix;
typedef QHash<QPair<SymbolType, SymbolType>, FloatType> TMatrix;

/*
 * This type select different view styles
 * View style says how to display matrix data
 */
typedef enum VStyl {None, Table, PlainText} ViewStyle;

/**
 * @brief The TableAbstract class
 * This is abstract class which provide simple interface and some common member to widgets which inhertit from it.
 * It begin widget hierarchy which is related to different views of matrix data (table and plain text views)
 */
class TableAbstract : public QWidget
{
    Q_OBJECT
public:
    explicit TableAbstract(int dimIn, QWidget *parent = 0);

    /**
     * @brief viewMatrix is used to give data into widget object
     * @details Data will be shown in widget's specific style
     * @param m is pointer to data
     */
    virtual void viewMatrix(TMatrix *m) = 0;

    /**
     * @brief setDescription changes description in window
     * @param des new description
     */
    virtual void setDescription(QString &des) = 0;

    /**
     * @brief getRawData returns raw matrix data which is hold in this table widget
     * @return matrix data (in type specific to this class)
     */
    QVector<QVector<double> > getRawData() const;

protected:
    /**
     * @brief transformIntoArray converts matrix from QHash type (which is set behind TMatrix type) into square QVector
     * @param mat given matrix to convert
     */
    void transformIntoArray(TMatrix *mat);

protected:
    /**
     * @brief dim - Dimmension table (square and symetrical matrix - so only one dimmension)
     */
    const int m_dim;

    /**
     * @brief m_symbols is list of symbols which were analysed by Blosum algorithm
     */
    QList<SymbolType> m_symbols;

    /**
     * @brief array - The array (data) which will be displayed.
     */
    QVector<QVector<double> > m_array;
};

#endif // TABLEABSTRACT_H
