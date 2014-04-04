#ifndef TABLEPLAINVIEW_H
#define TABLEPLAINVIEW_H

#include "tableabstract.h"
#include <QTextEdit>
#include <QGridLayout>
#include <QLabel>

/**
 * @brief The TablePlainView class
 * It create widget which display matrix data as simple text.
 * Each data row is insert into different text line.
 * Each data item is separated by specific separator
 * (by default it is space character).
 */
class TablePlainView : public TableAbstract
{
public:
    /**
     * @brief TablePlainView Constructor
     * @param inputDim dimmension of matrix which will be display
     * @param parent of this widget
     */
    explicit TablePlainView(int inputDim, QWidget *parent = 0);

    /**
     * @brief viewMatrix Display matrix in widget.
     * @param m is a pointer to data
     */
    void viewMatrix(TMatrix *m);

    /**
     * @brief setDescription changes description in window
     * @param des new description
     */
    void setDescription(QString &des);

private:
    // Main widget - text field
    QTextEdit *m_tableField;
    // Main layout which is set into parent Widget (in this case it will be Tab widget)
    QGridLayout *m_gridLayout;

    // Separator sign splitting data items
    QString m_sep;

    // Description of result matrix (shown above data)
    QLabel *m_description;
};

#endif // TABLEPLAINVIEW_H
