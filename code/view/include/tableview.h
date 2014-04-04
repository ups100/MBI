#ifndef TABLEVIEW_H
#define TABLEVIEW_H

#include "tableabstract.h"
#include <QTableView>
#include <QGridLayout>
#include <QStandardItemModel>
#include <QLabel>

namespace Ui {
class TableView;
}

/**
 * @brief The TableView class
 * Creates widget which present matrix in table widget.
 * It is used inside ResultWindow class.
 */
class TableView : public TableAbstract
{
    Q_OBJECT

public:
    /**
     * @brief TableView Construct class object.
     * @param inputDim is a dimmension of matrix
     * @param parent of this widget
     */
    explicit TableView(int inputDim, QWidget *parent = 0);
    ~TableView();

    /**
     * @brief viewMatrix is used to give data into widget object
     * @param m is pointer to data
     */
    void viewMatrix(TMatrix *m);

    /**
     * @brief setDescription changes description in window
     * @param des new description
     */
    void setDescription(QString &des);

private:
    // Table widget
    QTableView *m_tableView;
    // Main layout which is set into parent Widget (in this case it will be Tab widget)
    QGridLayout *m_gridLayout;

    // QStandardItemModel provides a classic
    // item-based approach to working with the model of table.
    QStandardItemModel *m_model;

    // Description of result matrix (shown above data)
    QLabel *m_description;
};

#endif // TABLEVIEW_H
